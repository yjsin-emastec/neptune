#ifndef _OSAL_THREAD_H_
#define _OSAL_THREAD_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <pthread.h>

#define MINIMUM_STACK_SIZE	(1 * 1024 * 1024)

/*******************************************************************************
* Includes
*******************************************************************************/
/*******************************************************************************
* Tasks
*******************************************************************************/

int osal_thread_create(void *(*function)(void *), int stack_size, void *args, char *info);
int osal_thread_alive_check(void);

typedef struct
{
    int     tid;
    char    tname[128];
} osal_thread_info_t;

#define	OSAL_THREAD_MAX	300

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
