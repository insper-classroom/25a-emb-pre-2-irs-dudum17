#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>
int btn1 = 28;
int btn2 = 26;
int led1 = 4;
int led2 = 6;
int red_flag = 0;
int green_flag = 0;
int led1_aceso = 0;
int led2_aceso = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    if (gpio == btn1)
      red_flag = 1;
  }else if(events == 0x8)
     if (gpio == btn2){
          green_flag = 1;
  }
}

int main() {
  stdio_init_all();


  gpio_init(btn1);
  gpio_set_dir(btn1, GPIO_IN);
  gpio_pull_up(btn1);

  gpio_init(btn2);
  gpio_set_dir(btn2, GPIO_IN);
  gpio_pull_up(btn2);

  gpio_init(led1);
  gpio_set_dir(led1, GPIO_OUT);

  gpio_init(led2);
  gpio_set_dir(led2, GPIO_OUT);

  gpio_set_irq_enabled_with_callback(btn1, GPIO_IRQ_EDGE_FALL, true,
                                     &btn_callback);

  // callback led g (nao usar _with_callback)
  gpio_set_irq_enabled(btn2, GPIO_IRQ_EDGE_RISE, true);


  while (true) {
    if(red_flag == 1){
      if(led1_aceso == 0){
        gpio_put(led1, 1);
        led1_aceso = 1;
      } else{
        gpio_put(led1, 0);
        led1_aceso = 0;
      }
      red_flag = 0;
    } else if(green_flag == 1){
      if(led2_aceso == 0){
        gpio_put(led2, 1);
        led2_aceso = 1;
      } else{
        gpio_put(led2, 0);
        led2_aceso = 0;
      }
      green_flag = 0;
    }
  }
}
