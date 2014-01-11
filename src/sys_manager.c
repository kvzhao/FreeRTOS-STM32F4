#include "sys_manager.h"

xQueueHandle serial_rx_queue = NULL;
xSemaphoreHandle serial_tx_wait_sem = NULL;

xQueueHandle com_rx_queue = NULL;
xSemaphoreHandle com_tx_wait_sem = NULL;

xQueueHandle arm_op_queue = NULL ;

