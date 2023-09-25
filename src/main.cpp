/**
* This is a sample program that blinks an LED on the STM32 with RTOS.
* 
*/
#include "FreeRTOS.h"
#include "debugger-breakpoint.h"
#include "queue.h"
#include "task.h"
#include <portable.h>
#include <portmacro.h>
#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_i2c.h>
#include <stm32f4xx_hal_spi.h>

#define LED_PORT GPIOA
#define LED_PIN GPIO_PIN_5

#define BLINK_FREQ (500 / portTICK_RATE_MS)

void initGPIO() {
  GPIO_InitTypeDef GPIO_Config;

  GPIO_Config.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_Config.Pull = GPIO_NOPULL;
  GPIO_Config.Speed = GPIO_SPEED_FREQ_HIGH;

  GPIO_Config.Pin = LED_PIN;

  __HAL_RCC_GPIOA_CLK_ENABLE();
  HAL_GPIO_Init(LED_PORT, &GPIO_Config);
}

static void blinkyTask(void *pvParameters) {
  for (;;) {
    TickType_t next_tick_time = xTaskGetTickCount();
    HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
    xTaskDelayUntil(&next_tick_time, BLINK_FREQ);
  }
}

int main(void) {
  HAL_Init();
  initGPIO();

  xTaskCreate(blinkyTask, "blink", configMINIMAL_STACK_SIZE, NULL,
              tskIDLE_PRIORITY, NULL);

  xPortStartScheduler();

  for (;;) {
  }
}

void vApplicationMallocFailedHook(void) {
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
  taskDISABLE_INTERRUPTS();
  DEBUGGER_BREAKPOINT();
  for (;;)
    ;
}

void vApplicationIdleHook(void) {
  /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
  to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
  task.  It is essential that code added to this hook function never attempts
  to block in any way (for example, call xQueueReceive() with a block time
  specified, or call vTaskDelay()).  If the application makes use of the
  vTaskDelete() API function (as this demo application does) then it is also
  important that vApplicationIdleHook() is permitted to return to its calling
  function, because it is the responsibility of the idle task to clean up
  memory allocated by the kernel to any task that has since been deleted. */
}

void vApplicationStackOverflowHook(xTaskHandle pxTask,
                                   signed char *pcTaskName) {
  (void)pcTaskName;
  (void)pxTask;

  /* Run time stack overflow checking is performed if
  configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
  function is called if a stack overflow is detected. */
  taskDISABLE_INTERRUPTS();
  DEBUGGER_BREAKPOINT();
  for (;;)
    ;
}
/*-----------------------------------------------------------*/

void vApplicationTickHook(void) {
  /* This function will be called by each tick interrupt if
  configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h.  User code can be
  added here, but the tick hook is called from an interrupt context, so
  code must not attempt to block, and only the interrupt safe FreeRTOS API
  functions can be used (those that end in FromISR()). */
}