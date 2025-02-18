#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
bool btn_flag = false;
bool print_flag = false;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    btn_flag  = true;
    print_flag = true;
  } else if (events == 0x8) { // rise edge
    btn_flag = false;
    print_flag = true;
  }
}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_set_irq_enabled_with_callback(
      BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  while (true) {
    if(print_flag == true){
      if(btn_flag == true){
         printf("fall\n");
    } else if(btn_flag == false){
         printf("rise\n");
    }
    print_flag = false;
  }
}

}