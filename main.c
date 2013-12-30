#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "math.h"
#include "stdio.h"
#include "stm32f4xx_usart.h"

#include "servo.h"

#define MAX_STRLEN 12
volatile char received_string[MAX_STRLEN+1]; // this will hold the recieved string

void USART3_Configuration(void);
void test_FPU_test(void* p);
void test_servo_task(void* p);

int main(void) {
  uint8_t ret;

  SystemInit();
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  USART3_Configuration();
  Servo_Configuration();

  // ret = xTaskCreate(test_FPU_test, "FPU", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  ret = xTaskCreate(test_servo_task, "SERVO", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

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

/*
 * Configure USART3(PB10, PB11) to redirect printf data to host PC.
 */
void USART3_Configuration(void) {
  GPIO_InitTypeDef GPIO_InitStruct;
  USART_InitTypeDef USART_InitStruct;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);

  USART_InitStruct.USART_BaudRate = 115200;
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
  USART_InitStruct.USART_StopBits = USART_StopBits_1;
  USART_InitStruct.USART_Parity = USART_Parity_No;
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
  USART_Init(USART3, &USART_InitStruct);

  /* USART for receiving data */
  NVIC_InitTypeDef NVIC_InitStructure;
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;       // we want to configure the USART3 interrupts
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;// this sets the priority group of the USART3 interrupts
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;      // this sets the subpriority inside the group
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         // the USART3 interrupts are globally enabled
    NVIC_Init(&NVIC_InitStructure); // the properties are passed to the NVIC_Init function which takes care of the low level stuff

    USART_Cmd(USART3, ENABLE);
}


// this is the interrupt request handler (IRQ) for ALL USART1 interrupts
void USART3_IRQHandler(void) {

    // check if the USART3 receive interrupt flag was set
    if( USART_GetITStatus(USART3, USART_IT_RXNE) ){

    static uint8_t cnt = 0; // this counter is used to determine the string length
    char t = USART3->DR; // the character from the USART3 data register is saved in t

    /* check if the received character is not the LF character (used to determine end of string)
    * or the if the maximum string length has been been reached
    */
        if( (t != 'n') && (cnt < MAX_STRLEN) ) {
            received_string[cnt] = t;
            cnt++;
         }
        else{ // otherwise reset the character counter and print the received string
            cnt = 0;
            printf("%s\r\n", received_string);
        }
    }
}
