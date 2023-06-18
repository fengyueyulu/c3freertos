/*
 *user：xhy
 *version：1.2
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
#define button 9

void light_init(void)
{
    gpio_reset_pin(LED_PI_L);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(LED_PI_L, GPIO_MODE_OUTPUT);
    gpio_reset_pin(LED_PI_R);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(LED_PI_R, GPIO_MODE_OUTPUT);
    
}

void button_init(void)
{
    gpio_reset_pin(button);
    gpio_set_direction(button, GPIO_MODE_DEF_INPUT);
}

int button_check(void)
{
    int button_state = 0;
    int prev_button_state = 0;
    while(1)
    {
    button_state = gpio_get_level(button);
    if(button_state!=prev_button_state)
    {
        vTaskDelay(pdMS_TO_TICKS(10));
        button_state= gpio_get_level(button);
    }
    if(button_state==0&&prev_button_state==1)
    {
        return 1;
    }
    prev_button_state=button_state;
    vTaskDelay(pdMS_TO_TICKS(10));
    }

        
}

void light_task(void)
{
    int led_num[2]={LED_PI_L,LED_PI_R};
    light_init();
    button_init();
    int flag=0;
    printf("into while\n");
    while (1)
    {
        flag=button_check();
        printf("get flag is ok\n");
        if (flag==1)
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
    
}

void app_main(void)
{
    xTaskCreate(light_task,"light_task",1024*2,0,NULL,0);
    printf("Hello world!\n");
}
