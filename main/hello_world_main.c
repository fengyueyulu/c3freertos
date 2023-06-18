/*
 *user：xhy
 *version：1.1
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
#define LED_PI_R 13

void light_init(void)
{
    gpio_reset_pin(LED_PI_L|LED_PI_R);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(LED_PI_L|LED_PI_R, GPIO_MODE_OUTPUT);
    // gpio_reset_pin(LED_PI_R);
    // /* Set the GPIO as a push/pull output */
    // gpio_set_direction(LED_PI_R, GPIO_MODE_OUTPUT);

    
}
void light_task(void)
{
    int led_num[2]={LED_PI_L,LED_PI_R};
    light_init();
   
    while (1)
    {
        for (int i = 0; i < 2; i++)
        {
        gpio_set_level(led_num[i],1);
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_set_level(led_num[i],0);
        vTaskDelay(pdMS_TO_TICKS(500));
        printf("light is %d\n",led_num[i]);
        }
    }
    
}

void app_main(void)
{
    xTaskCreate(light_task,"light_task",1024*2,0,NULL,0);
    printf("Hello world!\n");
}
