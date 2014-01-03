#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "math.h"
#include "stdio.h"
#include "stm32f4xx_usart.h"

#include "servo.h"
#include "serial_io.h"
#include "sys_manager.h"

void USART3_Configuration(void);
void null_task(void *p);
void test_FPU_test(void* p);
void test_servo_task(void* p);

int main(void) {
  uint8_t ret;

  SystemInit();
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

  Serial_Configuration();
  Servo_Configuration();

  vSemaphoreCreateBinary(serial_tx_wait_sem);
  serial_rx_queue = xQueueCreate(1, sizeof(serial_msg));

  // ret = xTaskCreate(test_FPU_test, "FPU", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  // ret = xTaskCreate(test_servo_task, "SERVO", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  ret = xTaskCreate(null_task, "Null Task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);


  if (ret == pdTRUE) {
    printf("System Started!\n\r");
    vTaskStartScheduler();  // should never return
  } else {
    printf("System Error!\n");
    // --TODO blink some LEDs to indicate fatal system error
  }

  for (;;);
}

void vApplicationTickHook(void) {
}

/* vApplicationMallocFailedHook() will only be called if
   configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
   function that will get called if a call to pvPortMalloc() fails.
   pvPortMalloc() is called internally by the kernel whenever a task, queue,
   timer or semaphore is created.  It is also called by various parts of the
   demo application.  If heap_1.c or heap_2.c are used, then the size of the
   heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
   FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
   to query the size of free heap space that remains (although it does not
   provide information on how the remaining heap might be fragmented). */
void vApplicationMallocFailedHook(void) {
  taskDISABLE_INTERRUPTS();
  for(;;);
}

/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
   to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
   task.  It is essential that code added to this hook function never attempts
   to block in any way (for example, call xQueueReceive() with a block time
   specified, or call vTaskDelay()).  If the application makes use of the
   vTaskDelete() API function (as this demo application does) then it is also
   important that vApplicationIdleHook() is permitted to return to its calling
   function, because it is the responsibility of the idle task to clean up
   memory allocated by the kernel to any task that has since been deleted. */
void vApplicationIdleHook(void) {
}

void vApplicationStackOverflowHook(xTaskHandle pxTask, signed char *pcTaskName) {
  (void) pcTaskName;
  (void) pxTask;
  /* Run time stack overflow checking is performed if
     configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
     function is called if a stack overflow is detected. */
  taskDISABLE_INTERRUPTS();
  for(;;);
}

void null_task(void *pvTaskParameters)
{
    printf("Enter Null task\r\n");
    for(;;) {}
    vTaskDelete(NULL);
}

void test_FPU_test(void* p) {
  float ff = 1.0f;
  printf("Start FPU test task.\n");
  for (;;) {
    float s = sinf(ff);
    ff += s;
    // TODO some other test
    vTaskDelay(1000);
  }
  vTaskDelete(NULL);
}

void test_servo_task(void *pvTaskParameters)
{
    printf("Start Servo test task.\n\t");
    while(1) {
        Servo_set_pos(60,0);
        printf("TIM4->ARR = %u, TIM4->CCR1 = %u\r\n",TIM4->ARR,TIM4->CCR1);
        vTaskDelay(500);

        Servo_set_pos(120,0);
        printf("TIM4->ARR = %u, TIM4->CCR1 = %u\r\n",TIM4->ARR,TIM4->CCR1);
        vTaskDelay(500);

        Servo_set_pos(60,0);
        printf("TIM4->ARR = %u, TIM4->CCR1 = %u\r\n",TIM4->ARR,TIM4->CCR1);
        vTaskDelay(500);

        Servo_set_pos(180,0);
        printf("TIM4->ARR = %u, TIM4->CCR1 = %u\r\n",TIM4->ARR,TIM4->CCR1);
        vTaskDelay(500);
    }
}
