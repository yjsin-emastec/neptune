#ifndef __IPCD_H__
#define __IPCD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/ipc.h>
#include <sys/msg.h>

#define IPC_GLOBAL_MTYPE  (0x01)

#define IPC_KEY_MAIN  		(0x1)
#define IPC_KEY_DAEMON_SEND_DVD  	(IPC_KEY_MAIN + 1)
#define IPC_KEY_DAEMON_RECV_DVD  	(IPC_KEY_MAIN + 2)
#define IPC_KEY_DAEMON_SEND_TST  	(IPC_KEY_MAIN + 3)
#define IPC_KEY_DAEMON_RECV_TST  	(IPC_KEY_MAIN + 4)

#define IPC_MAX_REQ_TYPE_NUM	(2)
#define IPC_REQ_TYPE_DVD	(0)
#define IPC_REQ_TYPE_TEST	(1)

#define	IPC_REQ_LIST_BASE 			(0x00)	
#define IPC_DVD_BURN_THREAD_READY 	(IPC_REQ_LIST_BASE + 1) 	 
#define IPC_DVD_BURN_START 			(IPC_REQ_LIST_BASE + 2) 	 
#define IPC_DVD_BURN_PROGRESS 		(IPC_REQ_LIST_BASE + 3) 	 
#define	IPC_DVD_BURN_FULL_CAPACITY  	(IPC_REQ_LIST_BASE + 4)
#define	IPC_DVD_BURN_DONE  			(IPC_REQ_LIST_BASE + 5)
#define	IPC_DVD_BURN_TEST  			(IPC_REQ_LIST_BASE + 6)

#define IPC_MSG_RECV					(0)
#define IPC_MSG_SEND					(1)

// Named Pipe
#define IPC_NAMED_PIPE_NAME			"/tmp/ipc_fifo"

typedef struct _IpcHandle IpcHandle;
struct _IpcHandle {
	char name[32];
	key_t key;	// set by caller
	key_t id;
};
typedef struct _IpcNpipeHandle IpcNpipeHandle;
struct _IpcNpipeHandle {
	char name[32];
	FILE *fp;
};
typedef struct _IpcMsgBuffer IpcMsgBuffer;
struct _IpcMsgBuffer {
	long mtype;	// This field is used to system call. you must subtract sizeof(long) on sending.
	int  request_type;
	int  body_size;
	char body[1024];
};
typedef struct _IpcContext IpcContext;
struct _IpcContext {
	IpcHandle main_que;
	IpcHandle send_que;
	IpcHandle recv_que;

	IpcMsgBuffer main_buf;
	IpcMsgBuffer send_buf;
	IpcMsgBuffer recv_buf;
};
	
// Message Queue
int ipcCreate(IpcHandle *pHandle);
int ipcGetMessage(IpcHandle *pHandle, void *msgp, int size);
int ipcSendMessage(IpcHandle *pHandle, const void *msgp, int size);
int ipcPrepareMessage(IpcMsgBuffer *msgp, int flag_send, long mtype, int request_type, int body_size, void *psrc);

// Named Pipe
int ipcNamePipeCreate(IpcNpipeHandle *pHandle);
#ifdef __cplusplus
}
#endif
#endif
