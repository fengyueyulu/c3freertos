/*
 *user：xhy
 *version：1.0
 *function：led
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "driver/gpio.h"

#define LED_PI_L 12

void light_init(void)
{
    gpio_reset_pin(LED_PI_L);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(LED_PI_L, GPIO_MODE_OUTPUT);
    
}
void light_task(void)
{
    light_init();
    while (1)
    {
        gpio_set_level(LED_PI_L,0);
        vTaskDelay(pdMS_TO_TICKS(200));
        gpio_set_level(LED_PI_L,1);
        vTaskDelay(pdMS_TO_TICKS(200));
    }
    
}

void app_main(void)
{
    xTaskCreate(light_task,"light_task",1024*2,0,NULL,0);
    printf("Hello world!\n");
}
