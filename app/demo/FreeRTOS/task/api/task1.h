#ifndef __TASK1_H__
#define __TASK1_H__

/******************************************************************************************************************************
 *										       Test application for task creation
 ******************************************************************************************************************************/

/******************************************************************************************************************************
 *										              Task creation APIs
 ******************************************************************************************************************************/

/*< Below is the structure of a task created in the memory */

/*++++++++++++++++++++++
  +       TCP          +
  +(task control block)+
  ++++++++++++++++++++++
  +   Stack of a Task  +   
  ++++++++++++++++++++++*/

/**
 * @brief   :  This api will create a TCB (task control block) for a task and associated stack space in the memory
 * @param   :  
 *  pvTaskCode   :  Pointer to a task function, That should take void pointer and return void
 *  pcName       :  A descriptive name to a task
 *  usStackDepth :  Stack size used for that particular task, usStackDepth is a number of words, ex. usStackDepth = 1, stack size is 4bytes
 *  pvParameters :  Pointer of the data, which we want to pass to any task when it is scheduled.
 *  pxCreatedTask:  Handle of a task, It is a pointer to the TCB created in the memory for that task.
 * @return  : BaseType_t (typedef long) 
 */ 
#if 0
BaseType_t xTaskCreate (
    TaskFunction_t pvTaskCode,      /*< typedef void (* TaskFunction_t)( void * ) */
    const char* const pcName,       /*< Const char pointer to const character */
    unsigned short usStackDepth,    /*< Stack size allocated for that particular task */
    void *pvParameters,             /*< void pointer */
    UBaseType_t uxPriority,         /*< unsigned long */
    TaskHandle_t *pxcreatedTask     /*< struct tskTaskControlBlock */
);
#endif

/******************************************************************************************************************************
 *												     Function Declaration
 ******************************************************************************************************************************/

extern void FreeRTOS_Task_Demo(void);

#endif //__TASK1_H__
