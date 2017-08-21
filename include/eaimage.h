#ifndef	__EAIMAGE_H__
#define	__EAIMAGE_H__

#ifdef __cplusplus
extern "C"{
#endif

#define	EA_IMAGE_VERSION            1
#define	EA_IMAGE_MAGIC              0x6573746e
#define	EA_UPFILE_MAX               5
#define	EA_UPFILE_NAME_MAX          64

#define	EA_UPGRADE_DIR              "/mnt/upgrade"

enum fuRcode
{
    FU_SUCCESS = 0,
    FU_FAIL_GET_MODEL_TYPE,
    FU_FILE_NOT_FOUND,
    FU_FILE_NOT_OPEN,
    FU_FILE_INVALID,
    FU_IMAGE_INVALID,
    FU_IMAGE_CKSUM_MISMATCH,
    FU_BOOTBANK_INVALID,
    FU_TIMEOUT,
    FU_FAIL_ERASE,
    FU_FAIL_WRITE,
    FU_FAIL_READ,
};

static const char *fu_get_message(int msg)
{
    switch (msg)
    {
        case FU_SUCCESS:              return "success.";
        case FU_FAIL_GET_MODEL_TYPE:  return "fail to get model type.";
        case FU_FILE_NOT_FOUND:       return "file not found.";
        case FU_FILE_NOT_OPEN:        return "fail to open file.";
        case FU_FILE_INVALID:         return "invalid file.";
        case FU_IMAGE_INVALID:        return "invalid image.";
        case FU_IMAGE_CKSUM_MISMATCH: return "checksum mismatch.";
        case FU_BOOTBANK_INVALID:     return "invalid bootbank.";
        case FU_TIMEOUT:              return "timeout.";
        case FU_FAIL_ERASE:           return "flash erase fail.";
        case FU_FAIL_WRITE:           return "flash write fail.";
        case FU_FAIL_READ:            return "flash read fail.";
    }
    return NULL;
}

typedef struct
{
    unsigned long    magic;         // magic number
    unsigned long    cksum;         // crc-32
    unsigned long    fsize;         // file size

    unsigned long    model:8;       // model number
    unsigned long    itype:8;       // image type
    unsigned long    version:4;     // image version
    unsigned long    resvd:12;      // for future use

} ea_image_header_t;

typedef struct
{
    const char    *name;
    const char    *mtdblock;
    unsigned long type;

} ea_image_info_t;

#ifdef __cplusplus
}
#endif

#endif
