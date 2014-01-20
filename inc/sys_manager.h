#ifndef _SYS_MANAGER_H
#define _SYS_MANAGER_H
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "stm32f4xx.h"

#define TRUE 1
#define FALSE 0

/* Manage Global Variables */
enum {
    PWM_CCR_1 = 0,
    PWM_CCR_2
        /*TODO : global struct */
};

void Delay(__IO uint32_t nCount);

// Queue and Semaphore for USART3 serial_io (used in shell)
extern xQueueHandle serial_rx_queue;
extern xSemaphoreHandle serial_tx_wait_sem;
// Queue and Semaphore for USART1 usart_com (used in robot arm communication)
extern xQueueHandle com_rx_queue;
extern xSemaphoreHandle com_tx_wait_sem;

#endif
