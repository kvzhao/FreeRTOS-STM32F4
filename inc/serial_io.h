#ifndef SERIAL_IO_H
#define SERIAL_IO_H

//#include "queue.h"
//#include "semphr.h"

#define MAX_STRLEN 12
extern volatile char received_string[];

typedef struct {
    char ch;
} serial_msg;

typedef struct {
    char (*getch)();
    void (*putch)(char c);
} serial_ops;

extern serial_ops serial;

void Serial_Configuration(void);

//extern xSemaphoreHandle serial_tx_wait_sem;
//extern xQueueHandle serial_rx_queue;

#endif
