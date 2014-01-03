#include "sys_manager.h"

xQueueHandle serial_rx_queue = NULL;
xSemaphoreHandle serial_tx_wait_sem = NULL;
