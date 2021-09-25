#include <app.h>

/**
 * void vPortDefineHeapRegions( const HeapRegion_t * const pxHeapRegions );
 * 
 * typedef struct HeapRegion
 * {
 *     The start address of start of memory
 *     uint8_t *pucStartAddress;
 * 
 *     The size of the block of memory in bytes
 *     size_t   xSizeInByte;
 * }
 * 
 * @brief: Each separate memory areas is described by a structure of type HeapRegion_t. A description of all the available memory 
 *         areas is passed into vPortDefineHeapRegions() as an array of HeapRegion_t structures.
 * 
 * @param: pxHeapRegions
 *         A pointer to the start of an array of HeapRegion_t structures. Each structure in the array describes the start address 
 *         and length of a memory area that will be part of the heap when heap_5 is used.
 *         The HeapRegion_t structures in the array must be ordered by start address; the HeapRegion_t structure that describes the
 *         memory area with the lowest start address must be the first structure in the array, and the HeapRegion_t structure that 
 *         describes the memory area with the highest start address must be the last structure in the array.
 *         The end of the array is marked by a HeapRegion_t structure that has its pucStartAddress member set to NULL.
 **/

/// Below is the example program taken from the reference manual just to understand the concept not to be used in this MCU
#if 0 ///Example1
/* Define the start address and size of the three RAM regions. */
#define RAM1_START_ADDRESS ( ( uint8_t * ) 0x00010000 )
#define RAM1_SIZE ( 65 * 1024 )

#define RAM2_START_ADDRESS ( ( uint8_t * ) 0x00020000 )
#define RAM2_SIZE ( 32 * 1024 )

#define RAM3_START_ADDRESS ( ( uint8_t * ) 0x00030000 )
#define RAM3_SIZE ( 32 * 1024 )

/* Create an array of HeapRegion_t definitions, with an index for each of the three 
RAM regions, and terminating the array with a NULL address. The HeapRegion_t 
structures must appear in start address order, with the structure that contains the 
lowest start address appearing first. */
const HeapRegion_t xHeapRegions[] =
{
 { RAM1_START_ADDRESS, RAM1_SIZE },
 { RAM2_START_ADDRESS, RAM2_SIZE },
 { RAM3_START_ADDRESS, RAM3_SIZE },
 { NULL, 0 } /* Marks the end of the array. */
};


int main( void )
{
 /* Initialize heap_5. */
 vPortDefineHeapRegions( xHeapRegions );
 /* Add application code here. */
}

#endif

#if 0 ///Example2
/**
 *  1. Define the start address and size of the two RAM regions not used by the linker. 
 *  2. If needed we can follow the same method used for RAM1 
 **/
#define RAM2_START_ADDRESS ( ( uint8_t * ) 0x00020000 )
#define RAM2_SIZE ( 32 * 1024 )

#define RAM3_START_ADDRESS ( ( uint8_t * ) 0x00030000 )
#define RAM3_SIZE ( 32 * 1024 )

/* Declare an array that will be part of the heap used by heap_5. The array will be 
placed in RAM1 by the linker. */
#define RAM1_HEAP_SIZE ( 30 * 1024 )
static uint8_t ucHeap[ RAM1_HEAP_SIZE ];

/* Create an array of HeapRegion_t definitions. Whereas in Listing 6 the first entry 
described all of RAM1, so heap_5 will have used all of RAM1, this time the first 
entry only describes the ucHeap array, so heap_5 will only use the part of RAM1 that 
contains the ucHeap array. The HeapRegion_t structures must still appear in start 
address order, with the structure that contains the lowest start address appearing 
first. */
const HeapRegion_t xHeapRegions[] =
{
 { ucHeap, RAM1_HEAP_SIZE },
 { RAM2_START_ADDRESS, RAM2_SIZE },
 { RAM3_START_ADDRESS, RAM3_SIZE },
 { NULL, 0 } /* Marks the end of the array. */
};

#endif

#if 0
void HeapHelpAPI(void)
{
    /**
     * size_t xPortGetFreeHeapSize( void );
     * @brief: It returns the number of free bytes in the heap at the time the function is called. It can be used to optimize the heap 
     *         size. For example, if xPortGetFreeHeapSize() returns 2000 after all the kernel objects have been created, then the 
     *         value of configTOTAL_HEAP_SIZE can be reduced by 2000.
     *         xPortGetFreeHeapSize() is not available when heap_3 is used.
     * @return : The number of bytes that remain unallocated in the heap at the time xPortGetFreeHeapSize() is called.
     * 
     **/

    /**
     * size_t xPortGetMinimumEverFreeHeapSize( void );
     * @brief  : API function returns the minimum number of unallocated bytes that have ever existed in the heap since the FreeRTOS 
     *           application started executing.
     *           The value returned by xPortGetMinimumEverFreeHeapSize() is an indication of how close the application has ever come to 
     *           running out of heap space. For example, if xPortGetMinimumEverFreeHeapSize() returns 200, then, at some time since 
     *           the application started executing, it came within 200 bytes of running out of heap space.
     *           xPortGetMinimumEverFreeHeapSize() is only available when heap_4 or heap_5 is used.
     * @return : The minimum number of unallocated bytes that have existed in the heap since the FreeRTOS application started 
     *           executing
     * 
     * 
     **/
    
}
#endif

typedef struct ThreadMessageType
{
    uint32_t val;
    
}ThreadMessageType;

void Thread(void *parameters)
{
#if 0
    ThreadMessageType message;
#endif
    while (1)
    {
        // message = receiveMessageFromThread();
    }
}
