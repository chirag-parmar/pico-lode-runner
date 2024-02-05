/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2021, Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "bsp/board_api.h"
#include "tusb.h"
#include "ds4.h"

static sony_ds4_input_report_t input_report;
static bool ds4_mounted = false;
static uint8_t ds4_dev_addr = 0;
static uint8_t ds4_instance = 0;

// check if device is Sony DualShock 4
static inline bool is_sony_ds4(uint8_t dev_addr)
{
  uint16_t vid, pid;
  tuh_vid_pid_get(dev_addr, &vid, &pid);

  return ( (vid == 0x054c && (pid == 0x09cc || pid == 0x05c4)) // Sony DualShock4
           || (vid == 0x0f0d && pid == 0x005e)                 // Hori FC4
           || (vid == 0x0f0d && pid == 0x00ee)                 // Hori PS4 Mini (PS4-099U)
           || (vid == 0x1f4f && pid == 0x1002)                 // ASW GG xrd controller
         );
}

//--------------------------------------------------------------------+
// MACRO TYPEDEF CONSTANT ENUM DECLARATION
//--------------------------------------------------------------------+

void ds4_write(sony_ds4_output_report_t* output_report, size_t report_size) {

  if (ds4_mounted) {
    const uint32_t interval_ms = 6;
    static uint32_t start_ms = 0;

    uint32_t current_time_ms = board_millis();

    if ( current_time_ms - start_ms >= interval_ms) {
      start_ms = current_time_ms;
      tuh_hid_send_report(ds4_dev_addr, ds4_instance, 5, output_report, report_size);
    }
  }
}

//--------------------------------------------------------------------+
// TinyUSB Callbacks
//--------------------------------------------------------------------+

// Invoked when device with hid interface is mounted
// Report descriptor is also available for use. tuh_hid_parse_report_descriptor()
// can be used to parse common/simple enough descriptor.
// Note: if report descriptor length > CFG_TUH_ENUMERATION_BUFSIZE, it will be skipped
// therefore report_desc = NULL, desc_len = 0
void tuh_hid_mount_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* desc_report, uint16_t desc_len) {
  
  (void)desc_report;
  (void)desc_len;
  uint16_t vid, pid;
  tuh_vid_pid_get(dev_addr, &vid, &pid);

  printf("HID device address = %d, instance = %d is mounted\r\n", dev_addr, instance);
  printf("VID = %04x, PID = %04x\r\n", vid, pid);

  // Sony DualShock 4 [CUH-ZCT2x]
  if ( is_sony_ds4(dev_addr) ) {
    if (!ds4_mounted) {
      ds4_dev_addr = dev_addr;
      ds4_instance = instance;
      ds4_mounted = true;
    }
    // request to receive report
    // tuh_hid_report_received_cb() will be invoked when report is available
    if ( !tuh_hid_receive_report(dev_addr, instance) ) {
      printf("Error: cannot request to receive report\r\n");
    }
  }
}

// Invoked when device with hid interface is un-mounted
void tuh_hid_umount_cb(uint8_t dev_addr, uint8_t instance) {
  
  printf("HID device address = %d, instance = %d is unmounted\r\n", dev_addr, instance);
  if (ds4_mounted && ds4_dev_addr == dev_addr && ds4_instance == instance) {
    ds4_mounted = false;
  }
}

// Invoked when received report from device via interrupt endpoint
void tuh_hid_report_received_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* report, uint16_t len)
{
  if ( is_sony_ds4(dev_addr) ) {
    // all buttons state is stored in ID 1
    if (report[0] == 1) {
        memcpy(&input_report, &report[1], sizeof(input_report));
        ds4_read_cb(&input_report, sizeof(input_report));
    }
  }

  // continue to request to receive report
  if ( !tuh_hid_receive_report(dev_addr, instance) ) {
    printf("Error: cannot request to receive report\r\n");
  }
}