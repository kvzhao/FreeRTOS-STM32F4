#ifndef _SYS_MANAGER_H
#define _SYS_MANAGER_H
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "stm32f4xx.h"

/* Manage Global Variables */
enum {
    PWM_CCR_1 = 0,
    PWM_CCR_2
        /*TODO : global struct */
};

extern xQueueHandle serial_rx_queue;
extern xSemaphoreHandle serial_tx_wait_sem;

#endif
