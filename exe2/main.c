#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

int btn = 28;
int led = 4;
volatile bool btn_flag = true;

void btn_callback(uint gpio, uint32_t events) {
  if (events == GPIO_IRQ_EDGE_FALL) { // fall edge
    btn_flag  = true;
  } else if (events == GPIO_IRQ_EDGE_RISE) { // rise edge
    btn_flag = false;
  }
}

int main() {
  stdio_init_all();


   gpio_init(led);
  gpio_set_dir(led, GPIO_OUT);

  gpio_init(btn);
  gpio_set_dir(btn, GPIO_IN);
  gpio_pull_up(btn);

 
  gpio_set_irq_enabled_with_callback(
      btn, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  while (true) {
    if(btn_flag == true){
      gpio_put(led, 1);
    } else{
       gpio_put(led, 0);
    }
  }
}
