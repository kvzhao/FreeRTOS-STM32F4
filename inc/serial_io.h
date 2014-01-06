#ifndef SERIAL_IO_H
#define SERIAL_IO_H

#define PRINT_DEBUG(var1) myprintf("DEBUG PRINT"#var1"\r\n")

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

int putstr(const char *msg);
int getstr(void);

void putch_base(char str);
char getch_base(void);
int myprintf(const char *format, ...);

double atof(const char *s);

#endif
