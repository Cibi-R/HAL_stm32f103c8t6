#ifndef __OSAL_THREAD_ATTRIBUTES_H__
#define __OSAL_THREAD_ATTRIBUTES_H__

#include "osal_types.h"

/******************************************************************************************************************************
 *												           Typedefs
 ******************************************************************************************************************************/

typedef struct Osal_Global_Thread_Attributes_T
{
    Osal_Thread_Id threadId;
    char threadName[Osal_THREAD_NAME_SIZE];
}Osal_Global_Thread_Attributes;

#endif //__OSL_THREAD_ATTRIBUTES_H__