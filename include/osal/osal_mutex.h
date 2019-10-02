#ifndef _OSAL_MUTEX_H_
#define _OSAL_MUTEX_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <pthread.h>

/*******************************************************************************
* Includes
*******************************************************************************/


/*******************************************************************************
* Tasks
*******************************************************************************/

/*
 * prototype for the task function
*/

int osal_mutex_lock(int index, int timeout);
int osal_mutex_unlock(int index);

#define MUTEX_MAX	128
// Add number which desired.
#define I2C_MUTEX	0
#define GPIO_MUTEX	1

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
