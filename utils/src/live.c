/* ----------------------------------------------------------------------------
 * Standard include files:
 * ---------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <net/route.h>
#include <netinet/in.h>
#include <net/if_arp.h>
#include <arpa/inet.h>

/* ----------------------------------------------------------------------------
 * Project include files:
 * ---------------------------------------------------------------------------- */
#include "utils.h"

/* ----------------------------------------------------------------------------
 * Types and Defines:
 * ---------------------------------------------------------------------------- */
#define EA_VIDEO_BUFF                 5
#define EASEND_LIVE_BYTES             65000
#define EALIVE_NODE_MAXIMUM           96
#define EALIVE_NODE_END               95

#define EALIVEAUDIO_STATUS_EMPTY      0
#define EALIVEAUDIO_STATUS_FILL       1
#define EALIVEAUDIO_STATUS_END        2
#define EALIVEAUDIO_STATUS_GETUSED    3

extern int ver_get_video(void);

typedef struct {
    int               get;
    int               put;
    EaLiveNode        nodes [EALIVE_NODE_MAXIMUM];
    int               keyCount;
    int               bytesMaximum;
    unsigned char    *buffer;
    int               offset;
    int               flagDrop;
    unsigned char    *bufferGet;
    int               flagClear;
    int               seq;
    int               seqGet;
} EaLiveList;

typedef struct m_EaLiveAudioNode EaLiveAudioNode;

struct m_EaLiveAudioNode {
    unsigned char        priority;  // set by argument
    unsigned char        kind;      // set by argument
    unsigned char        channel;   // set by argument
    unsigned char        command;   // set by argument
    unsigned long        bytes;     // set by argument
    unsigned char       *pData;     // set by argument
    EaLiveAudioNode     *pNext;     // internal used
    unsigned char        status;    // internal used
    char                 flag;      // internal used
    unsigned short       sequence;  // internal used
};

typedef struct m_EaLiveAudio{
    int                  countNode;          // set by argument
    int                  remainNodebuffersize;
    int                  usedNodeboundarybuffersize;
    int                  sleepMicroSecond;   // set by argument
    unsigned char       *pPool;
    unsigned char       *pAllocate;
    unsigned char       *pEnd;
    EaLiveAudioNode     *pHead;
    EaLiveAudioNode     *pGet;
    EaLiveAudioNode     *pPut;
    int                  nodecount;
    int                  totalnodebuffersize;
} EaLiveAudio;

/* ----------------------------------------------------------------------------
 * Global Variables:
 * ---------------------------------------------------------------------------- */
int                      gAudioLiveUsePointer;
int                      gIsLiveSendLocal;
unsigned char           *gsAudioStream [32];
static unsigned char     gBufferAudio  [16][1500];
static unsigned char     gBufferVideo  [EA_VIDEO_BUFF][65536];
static unsigned char     gBufferNtp    [EA_VIDEO_BUFF][32];
static EaLiveList        gLiveList     [32][2];
static EaLiveAudio       gLiveAudio    [32];

/* ----------------------------------------------------------------------------
 * Internal function body:
 * ---------------------------------------------------------------------------- */
static void doInitialize()
{
    int    ii;

    for(ii = 0; ii < 16; ii++)
    {
        gBufferAudio[ii][0] = '$';
        gBufferAudio[ii][1] = 2;
        gBufferAudio[ii][4] = 0x80;
        gBufferAudio[ii][5] = 0x80;
    }

    for(ii = 0; ii < EA_VIDEO_BUFF; ii++)
    {
        gBufferVideo[ii][0] = '$';
        gBufferVideo[ii][1] = 0;
        gBufferVideo[ii][4] = 0x80;

        gBufferNtp[ii][0]   = '$';
        gBufferNtp[ii][2]   = 0;
        gBufferNtp[ii][3]   = 28;
        gBufferNtp[ii][4]   = 0x80;
        gBufferNtp[ii][5]   = 200;
        gBufferNtp[ii][6]   = 0;
        gBufferNtp[ii][7]   = 6;
    }
}
static EaLiveAudioNode *doPutAudio2(unsigned char priority, unsigned long bytes, unsigned char *pData, unsigned char kind, unsigned char channel, unsigned char command, unsigned char *head, unsigned char payload0, unsigned char payload1)
{
    int    count              = 0;
    int    remainbuffer       = 0;
    int    remainbufferTmp    = 0;

    count = gLiveAudio[channel].pPut->sequence - gLiveAudio[channel].pGet->sequence;

    // fprintf(stderr, " gLiveAudio[channel].nodecount = %d\n",  gLiveAudio[channel].nodecount);

    if(count < 0)
    {
        gLiveAudio[channel].nodecount = gLiveAudio[channel].countNode + count;
    }
    else if (count == 0)
    {
        if( gLiveAudio[channel].pPut->status == EALIVEAUDIO_STATUS_FILL || gLiveAudio[channel].pPut->status == EALIVEAUDIO_STATUS_GETUSED)
        {
            gLiveAudio[channel].nodecount = gLiveAudio[channel].countNode;
        }
        else
        {
            if( gLiveAudio[channel].nodecount == ( gLiveAudio[channel].countNode - 1))
            {
                gLiveAudio[channel].nodecount = gLiveAudio[channel].countNode;
            }
            else
            {
                gLiveAudio[channel].nodecount = 0;
            }
        }
    }
    else
    {
        gLiveAudio[channel].nodecount = count;
    }

    if(gLiveAudio[channel].nodecount == 0)
    {
        gLiveAudio[channel].remainNodebuffersize = gLiveAudio[channel].totalnodebuffersize;
    }
    else
    {
        remainbuffer = (gLiveAudio[channel].pEnd - gLiveAudio[channel].pPool) + (gLiveAudio[channel].pGet->pData - gLiveAudio[channel].pAllocate);

        if( gLiveAudio[channel].totalnodebuffersize < remainbuffer)
        {
            gLiveAudio[channel].remainNodebuffersize = remainbuffer - gLiveAudio[channel].totalnodebuffersize;
        }
        else if(gLiveAudio[channel].totalnodebuffersize == remainbuffer)
        {
            gLiveAudio[channel].remainNodebuffersize = gLiveAudio[channel].totalnodebuffersize;
        }
        else
        {
            if(gLiveAudio[channel].nodecount == 0)
            {
                gLiveAudio[channel].remainNodebuffersize = gLiveAudio[channel].totalnodebuffersize;
            }
            else
            {
                gLiveAudio[channel].remainNodebuffersize = remainbuffer;
            }
        }
    }

    // fprintf(stderr, " gLiveAudio[channel].remainNodebuffersize=%d  gLiveAudio[channel].usedNodeboundarybuffersize=%d  gLiveAudio[channel].totalnodebuffersize=%d remainbuffer=%d  gLiveAudio[channel].pGet->pData = %d  gLiveAudio[channel].pPool = %d bytes=%d\n",
    // gLiveAudio[channel].remainNodebuffersize,  gLiveAudio[channel].usedNodeboundarybuffersize,  gLiveAudio[channel].totalnodebuffersize, remainbuffer,  gLiveAudio[channel].pGet->pData,  gLiveAudio[channel].pPool, bytes );

    if(gLiveAudio[channel].pPut->status == EALIVEAUDIO_STATUS_EMPTY)
    {
        EaLiveAudioNode    *pNode;
        remainbufferTmp    = gLiveAudio[channel].remainNodebuffersize - gLiveAudio[channel].usedNodeboundarybuffersize;

        if(remainbufferTmp < 0)
        {
            gLiveAudio[channel].usedNodeboundarybuffersize    = gLiveAudio[channel].remainNodebuffersize;
        }
        else if(remainbufferTmp == 0)
        {
            remainbufferTmp                                   = gLiveAudio[channel].usedNodeboundarybuffersize;
            gLiveAudio[channel].usedNodeboundarybuffersize    = 0;
        }

        if(remainbufferTmp < bytes)
        {
            // fprintf(stderr, "remain Buffer size %d count = %d  gLiveAudio[channel].usedNodeboundarybuffersize = %d remainbuffer = %d\n",  gLiveAudio[channel].remainNodebuffersize,  gLiveAudio[channel].nodecount,  gLiveAudio[channel].usedNodeboundarybuffersize, remainbuffer);
            //eaLockEnd(& gLiveAudio[channel].lock);
            return((EaLiveAudioNode *) gLiveAudio[channel].nodecount);
        }

        if((gLiveAudio[channel].pEnd - gLiveAudio[channel].pPool) < bytes)
        {
            // fprintf(stderr, "functionPutLocal : name=%s, seq=%d, bytes=%d\n",  gLiveAudio[channel].name,  gLiveAudio[channel].pPut->sequence, bytes);
            gLiveAudio[channel].usedNodeboundarybuffersize = gLiveAudio[channel].pEnd - gLiveAudio[channel].pPool;

            if(( gLiveAudio[channel].remainNodebuffersize - gLiveAudio[channel].usedNodeboundarybuffersize) < bytes)
            {
                // eaLockEnd(& gLiveAudio[channel].lock);
                // fprintf(stderr, "end buffer remain Buffer size %d count = %d bytes = %d  gLiveAudio[channel].usedNodeboundarybuffersize=%d\n",  gLiveAudio[channel].remainNodebuffersize,  gLiveAudio[channel].nodecount, bytes,  gLiveAudio[channel].usedNodeboundarybuffersize);
                return((EaLiveAudioNode *) gLiveAudio[channel].nodecount);
            }

            //gLiveAudio[channel].pPut->statusi = EALIVEAUDIO_STATUS_END;
            pNode                     = gLiveAudio[channel].pPut;
            //pNode                   = gLiveAudio[channel].pHead;
            gLiveAudio[channel].pPool = gLiveAudio[channel].pAllocate;
        }
        else
        {
            pNode                     = gLiveAudio[channel].pPut;
        }

        gLiveAudio[channel].pPut      = pNode->pNext;
        pNode->priority               = priority;
        pNode->command                = command;
        pNode->channel                = channel;
        pNode->kind                   = kind;
        pNode->bytes                  = bytes;
        pNode->pData                  = gLiveAudio[channel].pPool;
        memcpy(pNode->pData, head, 16);
        pNode->pData[16]              = payload0;
        pNode->pData[17]              = payload1;
        memcpy(pNode->pData + 18, pData, bytes - 18);
        // memcpy(pNode->pData, pData, pNode->bytes);
        gLiveAudio[channel].pPool    += pNode->bytes;

        // eaLockStart(& gLiveAudio[channel].lock);
        // eaLockEnd(& gLiveAudio[channel].lock);
        pNode->status                 = EALIVEAUDIO_STATUS_FILL;

        return((EaLiveAudioNode *) gLiveAudio[channel].nodecount);
    }

    // fprintf(stderr, "remain Buffer count %d\n",  gLiveAudio[channel].nodecount);
    return((EaLiveAudioNode *)(-1));

}
static void setULong(unsigned char *s, unsigned long ul)
{
    s[3] = (unsigned char)(ul & 0xFF);  ul /= 256L;
    s[2] = (unsigned char)(ul & 0xFF);  ul /= 256L;
    s[1] = (unsigned char)(ul & 0xFF);  ul /= 256L;
    s[0] = (unsigned char)ul;
}
static void sendLiveVideo(int channel, unsigned char *payload, int bytes, int mainStream, unsigned char head1, unsigned char payload0, unsigned char payload1, int add, unsigned char *pJpegHeader, int JepgHdeaderSize)
{
    int    size     = bytes      + 12;
    int    index    = mainStream + add;

    if(gIsLiveSendLocal)
    {
        if((head1 & 0x7f) == 96)
        {
            gBufferVideo[index][2]  = (unsigned char)(size / 256);
            gBufferVideo[index][3]  = (unsigned char)(size % 256);
            gBufferVideo[index][5]  = head1;
            gBufferVideo[index][16] = payload0;
            gBufferVideo[index][17] = payload1;
            memcpy(&gBufferVideo[index][18], payload + 2, bytes - 2);
            utils_net_local_live_send(gBufferVideo[mainStream+add], bytes + 16, channel, mainStream);
        }
        else
        {
            gBufferVideo[index][2]  = (unsigned char)((size + JepgHdeaderSize) / 256);
            gBufferVideo[index][3]  = (unsigned char)((size + JepgHdeaderSize) % 256);
            gBufferVideo[index][5]  = head1;
            memcpy(&gBufferVideo[index][16], pJpegHeader, JepgHdeaderSize);
            memcpy(&gBufferVideo[index][16 + JepgHdeaderSize], payload, bytes);
            utils_net_local_live_send(gBufferVideo[mainStream+add], bytes + 16 + JepgHdeaderSize, channel, mainStream);
        }
    }
}
/* ----------------------------------------------------------------------------
 * External function body:
 * ---------------------------------------------------------------------------- */
void utils_live_audio_initialize(void)
{
    int    ii;

    for(ii = 0; ii < 16; ii++)
    {
        gBufferAudio[ii][0] = '$';
        gBufferAudio[ii][1] = 2;
        gBufferAudio[ii][4] = 0x80;
        gBufferAudio[ii][5] = 0x80;
    }
}
void utils_live_initialize(int count, int keyCount, int bytesMain, int bytesSub)
{
    int    ii, jj;

    if(gIsLiveSendLocal == 0)
    {
        for(ii = 0; ii < count; ii++)
        {
            for(jj = 0; jj < 2; jj++)
            {
                memset(&gLiveList[ii][jj], 0, sizeof(EaLiveList));
                gLiveList[ii][jj].keyCount = keyCount;

                if(jj)
                {
                    gLiveList[ii][jj].bytesMaximum  = bytesMain;
                    gLiveList[ii][jj].buffer        = (unsigned char *)malloc(bytesMain);
                }
                else
                {
                    gLiveList[ii][jj].bytesMaximum  = bytesSub;
                    gLiveList[ii][jj].buffer        = (unsigned char *)malloc(bytesSub);
                }

                printf("bytesMain[%d][%d] : %d, %p\n", ii, jj, gLiveList[ii][jj].bytesMaximum, gLiveList[ii][jj].buffer);
            }
        }
    }

    doInitialize();
}
void *utils_live_get_audio(unsigned char channel)
{
    EaLiveAudioNode    *pNode;

    pNode = gLiveAudio[channel].pGet;

    if(pNode->status == EALIVEAUDIO_STATUS_GETUSED)
    {
        pNode->status            = EALIVEAUDIO_STATUS_EMPTY;
        gLiveAudio[channel].pGet = pNode->pNext;
        pNode                    = gLiveAudio[channel].pGet;
    }

    if(pNode->status == EALIVEAUDIO_STATUS_END)
    {
        // pNode = gLiveAudio[channel].pGet;
        pNode->status            = EALIVEAUDIO_STATUS_EMPTY;
        gLiveAudio[channel].pGet = gLiveAudio[channel].pHead;
    }

    if(pNode->status == EALIVEAUDIO_STATUS_FILL)
    {
        // pNode = gLiveAudio[channel].pGet;
        // fprintf(stderr, "%s: name.%s, seq.%d, bytes.%lu\n", __func__, gLiveAudio[channel].name, pNode->sequence, pNode->bytes);
        pNode->status = EALIVEAUDIO_STATUS_GETUSED;
        // fprintf(stderr, "%02x %02x %02x %02x %02x ... %10d bytes.\n",
        // pNode->pData[0], pNode->pData[1], pNode->pData[2], pNode->pData[3], pNode->pData[4], pNode->bytes);
        return pNode;
    }

    return 0;
}
void utils_live_put_audio(int channel, unsigned char *payload, int bytes, unsigned long long pts, int mainStream, int add)
{
    int    size    = bytes + 12;

    if(gAudioLiveUsePointer)
    {
        gsAudioStream[channel] = payload;
        return;
    }

    gBufferAudio[add][2] = (unsigned char)(size / 256);
    gBufferAudio[add][3] = (unsigned char)(size % 256);
    setULong(&gBufferAudio[add][8], (unsigned long)((pts / 125LL) & 0xFFFFFFFF));

    if(gIsLiveSendLocal)
    {
        memcpy(&gBufferAudio[add][16], payload, bytes);
        utils_net_local_live_send(gBufferAudio[add], bytes + 16, channel, mainStream);
    }
}
void utils_live_put_audio2(int channel, unsigned char *payload, int bytes, unsigned long long pts, int mainStream, int add)
{
    int    size             = bytes + 12;
    int    mainStreamtmp    = mainStream; //warning remove

    gBufferAudio[add][2] = (unsigned char)(size / 256);
    gBufferAudio[add][3] = (unsigned char)(size % 256);
    setULong(&gBufferAudio[add][8], (unsigned long)((pts / 125LL) & 0xFFFFFFFF));
    doPutAudio2(0, bytes + 16, &payload[2], 0, channel, 1, &gBufferAudio[add][0], payload[0], payload[1]);
}
void utils_live_put_ntp(int channel, unsigned long timestamp, int interleaved, int mainStream, int add)
{
    struct timeval    ntv;

    (void)gettimeofday(&ntv, NULL);

    int    index    = mainStream + add;

    gBufferNtp[index][1] = interleaved;
    setULong(&gBufferNtp[index][12], (unsigned long)ntv.tv_sec + 2208988800UL);
    setULong(&gBufferNtp[index][16], (unsigned long)ntv.tv_usec);
    setULong(&gBufferNtp[index][20], timestamp);

    if(gIsLiveSendLocal)
    {
        utils_net_local_live_send(gBufferNtp[index], 32, channel, mainStream);
    }
}
static void utils_live_rtpJpegPaylodHeader(unsigned char *pPayload, unsigned char *payloadJpeg, unsigned int offset)
{
    pPayload[0]   = 0x0;
    pPayload[1]   = offset / 65536;
    offset       %= 65536;
    pPayload[2]   = offset / 256;
    pPayload[3]   = offset % 256;
    pPayload[4]   = 0x01; //TYPE
    pPayload[5]   = 0x80; //Q
    pPayload[6]   = ((payloadJpeg[226] << 8 ) | (payloadJpeg[227]))>>3;
    pPayload[7]   = ((payloadJpeg[224] << 8 ) | (payloadJpeg[225]))>>3;
    pPayload[8]   = 0x00;  // MBZ
    pPayload[9]   = 0x00;  // Precision
    pPayload[10]  = 0x00;  // Length
    pPayload[11]  = 0x80;  // length
    memcpy(pPayload + 12, payloadJpeg + 25, 64);
    memcpy(pPayload + 76, payloadJpeg + 90, 64);
    // memcpy(pPayload + 144, payloadJpeg + 155, 64);
}
void utils_live_put_video(int channel, unsigned char *payload, int bytes, unsigned long pts, int mainStream, int add, int codectype)
{
    int    send_bytes    = EASEND_LIVE_BYTES;

    if(mainStream == 0)
    {
        send_bytes = 6000;
    }

    setULong(&gBufferVideo[mainStream+add][8], pts);

    if(codectype == 0) // H.264
    {
        if(bytes > send_bytes)
        {
            int              kk;
            int              count        = bytes / send_bytes;
            int              bytesUnit    = (bytes - 1) / (count + 1);
            int              offset       = -1;
            int              bytesEnd     = bytes - count * bytesUnit;
            //if(channel == 0) {printf("%02x bytes=%d bytesUnit=%d bytesEnd=%d\n", payload[0] & 0xFF, bytes, bytesUnit, bytesEnd); }
            unsigned char    nri          = payload[0] & 0xE0;
            unsigned char    nal          = payload[0] & 0x1F;

            for(kk = 0; ; kk++)
            {
                if(kk == 0)
                {
                    //if(channel == 0) {printf("[%d] bytes=%d offset=%d\n", kk, bytesUnit + 1, offset); }
                    sendLiveVideo(channel, payload + offset, bytesUnit + 1, mainStream, 96, nri | 28, 0x80 | nal, add, NULL, 0);
                    offset += (bytesUnit - 1);
                }
                else if(kk == count)
                {
                    //if(channel == 0) {printf("[%d] bytes=%d offset=%d\n", kk, bytesEnd + 2, offset); }
                    sendLiveVideo(channel, payload + offset, bytesEnd + 2, mainStream, 0x80 | 96, nri | 28, 0x40 | nal, add, NULL, 0);
                    break;
                }
                else
                {
                    //if(channel == 0) {printf("[%d] bytes=%d offset=%d\n", kk, bytesUnit + 2, offset); }
                    sendLiveVideo(channel, payload + offset, bytesUnit + 2, mainStream, 96, nri | 28, nal, add, NULL, 0);
                    offset += bytesUnit;
                }
            }
        }
        else
        {
            sendLiveVideo(channel, payload, bytes, mainStream, 0x80 | 96, payload[0], payload[1], add, NULL, 0);
        }
    }
    else if(codectype == 1) // MJPEG
    {
        unsigned char      PayloadJpegHeader [144];
        unsigned char     *pData            = payload;
        int                offsetsize       = 0;
        int                offsetsizetmp    = 0;
        int                count            = (int)((bytes - 678) / send_bytes);
        int                bytessize        = (bytes - 678) / (count + 1);
        int                bytesEnd         = (bytes - 678) - count * bytessize;
        int                kk;

        utils_live_rtpJpegPaylodHeader(PayloadJpegHeader, payload, 0);

        pData = payload + 678;

        for(kk = 0; kk < (count + 1); kk++)
        {
            int size;

            if(kk == 0)
            {
                // size = bytes + 144 - 678 +12;
                size = bytessize + 140 + 12;
            }
            else if(kk == count)
            {
                size = bytesEnd + 8 + 12;
            }
            else
            {
                size = bytessize + 8 + 12;
            }

            offsetsizetmp         = offsetsize;
            PayloadJpegHeader[1]  = offsetsizetmp / 65536;
            offsetsizetmp        %= 65536;
            PayloadJpegHeader[2]  = offsetsizetmp / 256;
            PayloadJpegHeader[3]  = offsetsizetmp % 256;

            if(kk == 0)
            {
                sendLiveVideo(channel, pData, bytessize, mainStream, 26, 0, 0, add, PayloadJpegHeader, 140);
            }
            else if(kk == count)
            {
                sendLiveVideo(channel, pData + (count * bytessize), bytesEnd, mainStream, 0x80 | 26, 0, 0, add, PayloadJpegHeader, 8);
            }
            else
            {
                sendLiveVideo(channel, pData + (kk * bytessize), bytessize, mainStream, 26, 0, 0, add, PayloadJpegHeader, 8);
            }

            if(kk == 0)
            {
                offsetsize = bytessize;
            }
            else if(kk == count)
            {
                offsetsize = offsetsize + bytesEnd;
            }
            else
            {
                offsetsize = offsetsize + bytessize;
            }
        }

    }
}
EaLiveNode *utils_live_get(int channel, int mainStream)
{
    int    ii;

    EaLiveList *pList = &gLiveList[channel][mainStream];

    if(pList->flagClear)
    {
        printf("c%d.%d.g=%d.p=%d\n", channel, mainStream, pList->get, pList->put);

        for(ii = 0; ii < EALIVE_NODE_MAXIMUM; ii++)
        {
            pList->nodes[ii].bytes = 0;
        }

        pList->get       = 0;
        pList->bufferGet = pList->buffer;
        pList->flagClear = 0;

        return 0;
    }

    if(pList->nodes[pList->get].bytes < 0)
    {
        pList->nodes[pList->get].bytes = 0;
        pList->get                     = 0;
    }

    EaLiveNode    *pNode    = &pList->nodes[pList->get];

    if(pNode->bytes)
    {
        //if(channel==0) printf("gg%d.%d=%d,%d,%d", channel, mainStream, pList->get, pNode->bytes, pNode->seq);

        if(pList->get == EALIVE_NODE_END)
        {
            pList->get = 0;
        }
        else
        {
            pList->get++;
        }

        pList->bufferGet = pNode->stream;
        pList->seqGet    = pNode->seq;
        //if(channel==0) printf("g\n");
        return pNode;
    }
    else
    {
        return 0;
    }
}
