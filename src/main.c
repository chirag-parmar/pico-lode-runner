#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bsp/board_api.h"
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "tusb.h"
#include "ds4.h"

#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1

static uint8_t motor_left, motor_right;

int main(void) {

  board_init();
  stdio_uart_init_full (UART_ID, BAUD_RATE, UART_TX_PIN, UART_RX_PIN);

  // Set the TX and RX pins by using the function select on the GPIO
  gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
  gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

  printf("TinyUSB Host CDC MSC HID Example\r\n");

  // init host stack on configured roothub port
  tuh_init(BOARD_TUH_RHPORT);

  while (1) {
    // tinyusb host task
    tuh_task();

    sony_ds4_output_report_t output_report = {0};
    output_report.set_rumble = 1;
    output_report.motor_left = motor_left;
    output_report.motor_right = motor_right;
    ds4_write(&output_report, sizeof(output_report));
  }

  return 0;
}

void ds4_read_cb(sony_ds4_input_report_t* input_report, size_t report_size) {
  const char* dpad_str[] = { "N", "NE", "E", "SE", "S", "SW", "W", "NW", "none" };
  printf("(x, y, z, rz) = (%u, %u, %u, %u)\r\n", input_report->x, input_report->y, input_report->z, input_report->rz);
  printf("DPad = %s ", dpad_str[input_report->dpad]);

  if (input_report->square   ) printf("Square ");
  if (input_report->cross    ) printf("Cross ");
  if (input_report->circle   ) printf("Circle ");
  if (input_report->triangle ) printf("Triangle ");

  if (input_report->l1       ) printf("L1 ");
  if (input_report->r1       ) printf("R1 ");
  if (input_report->l2       ) printf("L2 ");
  if (input_report->r2       ) printf("R2 ");

  if (input_report->share    ) printf("Share ");
  if (input_report->option   ) printf("Option ");
  if (input_report->l3       ) printf("L3 ");
  if (input_report->r3       ) printf("R3 ");

  if (input_report->ps       ) printf("PS ");
  if (input_report->tpad     ) printf("TPad ");

  printf("\r\n");

  motor_left = input_report->l2_trigger;
  motor_right = input_report->r2_trigger;
}