#include <stdint.h>
#include "DlmsReader.h"
#include <ArduinoJson.h>
#include <unity.h>

char resultStr[4096] = {0};

unsigned char data1_dat[] = {
  0x7e, 0xa2, 0x43, 0x41, 0x08, 0x83, 0x13, 0x85, 0xeb, 0xe6, 0xe7, 0x00,
  0x0f, 0x40, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1b, 0x02, 0x02, 0x09, 0x06,
  0x00, 0x00, 0x01, 0x00, 0x00, 0xff, 0x09, 0x0c, 0x07, 0xe4, 0x0b, 0x08,
  0x00, 0x0c, 0x18, 0x28, 0xff, 0x80, 0x00, 0xff, 0x02, 0x03, 0x09, 0x06,
  0x01, 0x00, 0x01, 0x07, 0x00, 0xff, 0x06, 0x00, 0x00, 0x05, 0x17, 0x02,
  0x02, 0x0f, 0x00, 0x16, 0x1b, 0x02, 0x03, 0x09, 0x06, 0x01, 0x00, 0x02,
  0x07, 0x00, 0xff, 0x06, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x0f, 0x00,
  0x16, 0x1b, 0x02, 0x03, 0x09, 0x06, 0x01, 0x00, 0x03, 0x07, 0x00, 0xff,
  0x06, 0x00, 0x00, 0x00, 0x92, 0x02, 0x02, 0x0f, 0x00, 0x16, 0x1d, 0x02,
  0x03, 0x09, 0x06, 0x01, 0x00, 0x04, 0x07, 0x00, 0xff, 0x06, 0x00, 0x00,
  0x00, 0x00, 0x02, 0x02, 0x0f, 0x00, 0x16, 0x1d, 0x02, 0x03, 0x09, 0x06,
  0x01, 0x00, 0x1f, 0x07, 0x00, 0xff, 0x10, 0x00, 0x19, 0x02, 0x02, 0x0f,
  0xff, 0x16, 0x21, 0x02, 0x03, 0x09, 0x06, 0x01, 0x00, 0x33, 0x07, 0x00,
  0xff, 0x10, 0x00, 0x19, 0x02, 0x02, 0x0f, 0xff, 0x16, 0x21, 0x02, 0x03,
  0x09, 0x06, 0x01, 0x00, 0x47, 0x07, 0x00, 0xff, 0x10, 0x00, 0x0f, 0x02,
  0x02, 0x0f, 0xff, 0x16, 0x21, 0x02, 0x03, 0x09, 0x06, 0x01, 0x00, 0x20,
  0x07, 0x00, 0xff, 0x12, 0x09, 0x10, 0x02, 0x02, 0x0f, 0xff, 0x16, 0x23,
  0x02, 0x03, 0x09, 0x06, 0x01, 0x00, 0x34, 0x07, 0x00, 0xff, 0x12, 0x09,
  0x28, 0x02, 0x02, 0x0f, 0xff, 0x16, 0x23, 0x02, 0x03, 0x09, 0x06, 0x01,
  0x00, 0x48, 0x07, 0x00, 0xff, 0x12, 0x09, 0x29, 0x02, 0x02, 0x0f, 0xff,
  0x16, 0x23, 0x02, 0x03, 0x09, 0x06, 0x01, 0x00, 0x15, 0x07, 0x00, 0xff,
  0x06, 0x00, 0x00, 0x02, 0x31, 0x02, 0x02, 0x0f, 0x00, 0x16, 0x1b, 0x02,
  0x03, 0x09, 0x06, 0x01, 0x00, 0x16, 0x07, 0x00, 0xff, 0x06, 0x00, 0x00,
  0x00, 0x00, 0x02, 0x02, 0x0f, 0x00, 0x16, 0x1b, 0x02, 0x03, 0x09, 0x06,
  0x01, 0x00, 0x17, 0x07, 0x00, 0xff, 0x06, 0x00, 0x00, 0x00, 0xc3, 0x02,
  0x02, 0x0f, 0x00, 0x16, 0x1d, 0x02, 0x03, 0x09, 0x06, 0x01, 0x00, 0x18,
  0x07, 0x00, 0xff, 0x06, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x0f, 0x00,
  0x16, 0x1d, 0x02, 0x03, 0x09, 0x06, 0x01, 0x00, 0x29, 0x07, 0x00, 0xff,
  0x06, 0x00, 0x00, 0x02, 0x18, 0x02, 0x02, 0x0f, 0x00, 0x16, 0x1b, 0x02,
  0x03, 0x09, 0x06, 0x01, 0x00, 0x2a, 0x07, 0x00, 0xff, 0x06, 0x00, 0x00,
  0x00, 0x00, 0x02, 0x02, 0x0f, 0x00, 0x16, 0x1b, 0x02, 0x03, 0x09, 0x06,
  0x01, 0x00, 0x2b, 0x07, 0x00, 0xff, 0x06, 0x00, 0x00, 0x01, 0x0a, 0x02,
  0x02, 0x0f, 0x00, 0x16, 0x1d, 0x02, 0x03, 0x09, 0x06, 0x01, 0x00, 0x2c,
  0x07, 0x00, 0xff, 0x06, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x0f, 0x00,
  0x16, 0x1d, 0x02, 0x03, 0x09, 0x06, 0x01, 0x00, 0x3d, 0x07, 0x00, 0xff,
  0x06, 0x00, 0x00, 0x00, 0xd1, 0x02, 0x02, 0x0f, 0x00, 0x16, 0x1b, 0x02,
  0x03, 0x09, 0x06, 0x01, 0x00, 0x3e, 0x07, 0x00, 0xff, 0x06, 0x00, 0x00,
  0x00, 0x00, 0x02, 0x02, 0x0f, 0x00, 0x16, 0x1b, 0x02, 0x03, 0x09, 0x06,
  0x01, 0x00, 0x3f, 0x07, 0x00, 0xff, 0x06, 0x00, 0x00, 0x00, 0x00, 0x02,
  0x02, 0x0f, 0x00, 0x16, 0x1d, 0x02, 0x03, 0x09, 0x06, 0x01, 0x00, 0x40,
  0x07, 0x00, 0xff, 0x06, 0x00, 0x00, 0x01, 0x36, 0x02, 0x02, 0x0f, 0x00,
  0x16, 0x1d, 0x02, 0x03, 0x09, 0x06, 0x01, 0x00, 0x01, 0x08, 0x00, 0xff,
  0x06, 0x00, 0x03, 0x38, 0x00, 0x02, 0x02, 0x0f, 0x00, 0x16, 0x1e, 0x02,
  0x03, 0x09, 0x06, 0x01, 0x00, 0x02, 0x08, 0x00, 0xff, 0x06, 0x00, 0x00,
  0x00, 0x00, 0x02, 0x02, 0x0f, 0x00, 0x16, 0x1e, 0x02, 0x03, 0x09, 0x06,
  0x01, 0x00, 0x03, 0x08, 0x00, 0xff, 0x06, 0x00, 0x00, 0x00, 0x0c, 0x02,
  0x02, 0x0f, 0x00, 0x16, 0x20, 0x02, 0x03, 0x09, 0x06, 0x01, 0x00, 0x04,
  0x08, 0x00, 0xff, 0x06, 0x00, 0x01, 0x03, 0x61, 0x02, 0x02, 0x0f, 0x00,
  0x16, 0x20, 0xd9, 0x0b, 0x7e
};

unsigned char p1_example_5_0_txt[] = {
  0x2f, 0x49, 0x53, 0x6b, 0x35, 0x5c, 0x32, 0x4d, 0x54, 0x33, 0x38, 0x32,
  0x2d, 0x31, 0x30, 0x30, 0x30, 0x0d, 0x0a, 0x0d, 0x0a, 0x31, 0x2d, 0x33,
  0x3a, 0x30, 0x2e, 0x32, 0x2e, 0x38, 0x28, 0x35, 0x30, 0x29, 0x0d, 0x0a,
  0x30, 0x2d, 0x30, 0x3a, 0x31, 0x2e, 0x30, 0x2e, 0x30, 0x28, 0x31, 0x30,
  0x31, 0x32, 0x30, 0x39, 0x31, 0x31, 0x33, 0x30, 0x32, 0x30, 0x57, 0x29,
  0x0d, 0x0a, 0x30, 0x2d, 0x30, 0x3a, 0x39, 0x36, 0x2e, 0x31, 0x2e, 0x31,
  0x28, 0x34, 0x42, 0x33, 0x38, 0x34, 0x35, 0x34, 0x37, 0x33, 0x30, 0x33,
  0x30, 0x33, 0x34, 0x33, 0x30, 0x33, 0x34, 0x33, 0x36, 0x33, 0x33, 0x33,
  0x39, 0x33, 0x35, 0x33, 0x35, 0x33, 0x30, 0x33, 0x37, 0x29, 0x0d, 0x0a,
  0x31, 0x2d, 0x30, 0x3a, 0x31, 0x2e, 0x38, 0x2e, 0x31, 0x28, 0x31, 0x32,
  0x33, 0x34, 0x35, 0x36, 0x2e, 0x37, 0x38, 0x39, 0x2a, 0x6b, 0x57, 0x68,
  0x29, 0x0d, 0x0a, 0x31, 0x2d, 0x30, 0x3a, 0x31, 0x2e, 0x38, 0x2e, 0x32,
  0x28, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x2e, 0x37, 0x38, 0x39, 0x2a,
  0x6b, 0x57, 0x68, 0x29, 0x0d, 0x0a, 0x31, 0x2d, 0x30, 0x3a, 0x32, 0x2e,
  0x38, 0x2e, 0x31, 0x28, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x2e, 0x37,
  0x38, 0x39, 0x2a, 0x6b, 0x57, 0x68, 0x29, 0x0d, 0x0a, 0x31, 0x2d, 0x30,
  0x3a, 0x32, 0x2e, 0x38, 0x2e, 0x32, 0x28, 0x31, 0x32, 0x33, 0x34, 0x35,
  0x36, 0x2e, 0x37, 0x38, 0x39, 0x2a, 0x6b, 0x57, 0x68, 0x29, 0x0d, 0x0a,
  0x30, 0x2d, 0x30, 0x3a, 0x39, 0x36, 0x2e, 0x31, 0x34, 0x2e, 0x30, 0x28,
  0x30, 0x30, 0x30, 0x32, 0x29, 0x0d, 0x0a, 0x31, 0x2d, 0x30, 0x3a, 0x31,
  0x2e, 0x37, 0x2e, 0x30, 0x28, 0x30, 0x31, 0x2e, 0x31, 0x39, 0x33, 0x2a,
  0x6b, 0x57, 0x29, 0x0d, 0x0a, 0x31, 0x2d, 0x30, 0x3a, 0x32, 0x2e, 0x37,
  0x2e, 0x30, 0x28, 0x30, 0x30, 0x2e, 0x30, 0x30, 0x30, 0x2a, 0x6b, 0x57,
  0x29, 0x0d, 0x0a, 0x30, 0x2d, 0x30, 0x3a, 0x39, 0x36, 0x2e, 0x37, 0x2e,
  0x32, 0x31, 0x28, 0x30, 0x30, 0x30, 0x30, 0x34, 0x29, 0x0d, 0x0a, 0x30,
  0x2d, 0x30, 0x3a, 0x39, 0x36, 0x2e, 0x37, 0x2e, 0x39, 0x28, 0x30, 0x30,
  0x30, 0x30, 0x32, 0x29, 0x0d, 0x0a, 0x31, 0x2d, 0x30, 0x3a, 0x39, 0x39,
  0x2e, 0x39, 0x37, 0x2e, 0x30, 0x28, 0x32, 0x29, 0x28, 0x30, 0x2d, 0x30,
  0x3a, 0x39, 0x36, 0x2e, 0x37, 0x2e, 0x31, 0x39, 0x29, 0x28, 0x31, 0x30,
  0x31, 0x32, 0x30, 0x38, 0x31, 0x35, 0x32, 0x34, 0x31, 0x35, 0x57, 0x29,
  0x28, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x32, 0x34, 0x30, 0x2a,
  0x73, 0x29, 0x28, 0x31, 0x30, 0x31, 0x32, 0x30, 0x38, 0x31, 0x35, 0x31,
  0x30, 0x30, 0x34, 0x57, 0x29, 0x28, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
  0x30, 0x33, 0x30, 0x31, 0x2a, 0x73, 0x29, 0x0d, 0x0a, 0x31, 0x2d, 0x30,
  0x3a, 0x33, 0x32, 0x2e, 0x33, 0x32, 0x2e, 0x30, 0x28, 0x30, 0x30, 0x30,
  0x30, 0x32, 0x29, 0x0d, 0x0a, 0x31, 0x2d, 0x30, 0x3a, 0x35, 0x32, 0x2e,
  0x33, 0x32, 0x2e, 0x30, 0x28, 0x30, 0x30, 0x30, 0x30, 0x31, 0x29, 0x0d,
  0x0a, 0x31, 0x2d, 0x30, 0x3a, 0x37, 0x32, 0x2e, 0x33, 0x32, 0x2e, 0x30,
  0x28, 0x30, 0x30, 0x30, 0x30, 0x30, 0x29, 0x0d, 0x0a, 0x31, 0x2d, 0x30,
  0x3a, 0x33, 0x32, 0x2e, 0x33, 0x36, 0x2e, 0x30, 0x28, 0x30, 0x30, 0x30,
  0x30, 0x30, 0x29, 0x0d, 0x0a, 0x31, 0x2d, 0x30, 0x3a, 0x35, 0x32, 0x2e,
  0x33, 0x36, 0x2e, 0x30, 0x28, 0x30, 0x30, 0x30, 0x30, 0x33, 0x29, 0x0d,
  0x0a, 0x31, 0x2d, 0x30, 0x3a, 0x37, 0x32, 0x2e, 0x33, 0x36, 0x2e, 0x30,
  0x28, 0x30, 0x30, 0x30, 0x30, 0x30, 0x29, 0x0d, 0x0a, 0x30, 0x2d, 0x30,
  0x3a, 0x39, 0x36, 0x2e, 0x31, 0x33, 0x2e, 0x30, 0x28, 0x33, 0x30, 0x33,
  0x31, 0x33, 0x32, 0x33, 0x33, 0x33, 0x34, 0x33, 0x35, 0x33, 0x36, 0x33,
  0x37, 0x33, 0x38, 0x33, 0x39, 0x33, 0x41, 0x33, 0x42, 0x33, 0x43, 0x33,
  0x44, 0x33, 0x45, 0x33, 0x46, 0x33, 0x30, 0x33, 0x31, 0x33, 0x32, 0x33,
  0x33, 0x33, 0x34, 0x33, 0x35, 0x33, 0x36, 0x33, 0x37, 0x33, 0x38, 0x33,
  0x39, 0x33, 0x41, 0x33, 0x42, 0x33, 0x43, 0x33, 0x44, 0x33, 0x45, 0x33,
  0x46, 0x33, 0x30, 0x33, 0x31, 0x33, 0x32, 0x33, 0x33, 0x33, 0x34, 0x33,
  0x35, 0x33, 0x36, 0x33, 0x37, 0x33, 0x38, 0x33, 0x39, 0x33, 0x41, 0x33,
  0x42, 0x33, 0x43, 0x33, 0x44, 0x33, 0x45, 0x33, 0x46, 0x33, 0x30, 0x33,
  0x31, 0x33, 0x32, 0x33, 0x33, 0x33, 0x34, 0x33, 0x35, 0x33, 0x36, 0x33,
  0x37, 0x33, 0x38, 0x33, 0x39, 0x33, 0x41, 0x33, 0x42, 0x33, 0x43, 0x33,
  0x44, 0x33, 0x45, 0x33, 0x46, 0x33, 0x30, 0x33, 0x31, 0x33, 0x32, 0x33,
  0x33, 0x33, 0x34, 0x33, 0x35, 0x33, 0x36, 0x33, 0x37, 0x33, 0x38, 0x33,
  0x39, 0x33, 0x41, 0x33, 0x42, 0x33, 0x43, 0x33, 0x44, 0x33, 0x45, 0x33,
  0x46, 0x29, 0x0d, 0x0a, 0x31, 0x2d, 0x30, 0x3a, 0x33, 0x32, 0x2e, 0x37,
  0x2e, 0x30, 0x28, 0x32, 0x32, 0x30, 0x2e, 0x31, 0x2a, 0x56, 0x29, 0x0d,
  0x0a, 0x31, 0x2d, 0x30, 0x3a, 0x35, 0x32, 0x2e, 0x37, 0x2e, 0x30, 0x28,
  0x32, 0x32, 0x30, 0x2e, 0x32, 0x2a, 0x56, 0x29, 0x0d, 0x0a, 0x31, 0x2d,
  0x30, 0x3a, 0x37, 0x32, 0x2e, 0x37, 0x2e, 0x30, 0x28, 0x32, 0x32, 0x30,
  0x2e, 0x33, 0x2a, 0x56, 0x29, 0x0d, 0x0a, 0x31, 0x2d, 0x30, 0x3a, 0x33,
  0x31, 0x2e, 0x37, 0x2e, 0x30, 0x28, 0x30, 0x30, 0x31, 0x2a, 0x41, 0x29,
  0x0d, 0x0a, 0x31, 0x2d, 0x30, 0x3a, 0x35, 0x31, 0x2e, 0x37, 0x2e, 0x30,
  0x28, 0x30, 0x30, 0x32, 0x2a, 0x41, 0x29, 0x0d, 0x0a, 0x31, 0x2d, 0x30,
  0x3a, 0x37, 0x31, 0x2e, 0x37, 0x2e, 0x30, 0x28, 0x30, 0x30, 0x33, 0x2a,
  0x41, 0x29, 0x0d, 0x0a, 0x31, 0x2d, 0x30, 0x3a, 0x32, 0x31, 0x2e, 0x37,
  0x2e, 0x30, 0x28, 0x30, 0x31, 0x2e, 0x31, 0x31, 0x31, 0x2a, 0x6b, 0x57,
  0x29, 0x0d, 0x0a, 0x31, 0x2d, 0x30, 0x3a, 0x34, 0x31, 0x2e, 0x37, 0x2e,
  0x30, 0x28, 0x30, 0x32, 0x2e, 0x32, 0x32, 0x32, 0x2a, 0x6b, 0x57, 0x29,
  0x0d, 0x0a, 0x31, 0x2d, 0x30, 0x3a, 0x36, 0x31, 0x2e, 0x37, 0x2e, 0x30,
  0x28, 0x30, 0x33, 0x2e, 0x33, 0x33, 0x33, 0x2a, 0x6b, 0x57, 0x29, 0x0d,
  0x0a, 0x31, 0x2d, 0x30, 0x3a, 0x32, 0x32, 0x2e, 0x37, 0x2e, 0x30, 0x28,
  0x30, 0x34, 0x2e, 0x34, 0x34, 0x34, 0x2a, 0x6b, 0x57, 0x29, 0x0d, 0x0a,
  0x31, 0x2d, 0x30, 0x3a, 0x34, 0x32, 0x2e, 0x37, 0x2e, 0x30, 0x28, 0x30,
  0x35, 0x2e, 0x35, 0x35, 0x35, 0x2a, 0x6b, 0x57, 0x29, 0x0d, 0x0a, 0x31,
  0x2d, 0x30, 0x3a, 0x36, 0x32, 0x2e, 0x37, 0x2e, 0x30, 0x28, 0x30, 0x36,
  0x2e, 0x36, 0x36, 0x36, 0x2a, 0x6b, 0x57, 0x29, 0x0d, 0x0a, 0x30, 0x2d,
  0x31, 0x3a, 0x32, 0x34, 0x2e, 0x31, 0x2e, 0x30, 0x28, 0x30, 0x30, 0x33,
  0x29, 0x0d, 0x0a, 0x30, 0x2d, 0x31, 0x3a, 0x39, 0x36, 0x2e, 0x31, 0x2e,
  0x30, 0x28, 0x33, 0x32, 0x33, 0x32, 0x33, 0x32, 0x33, 0x32, 0x34, 0x31,
  0x34, 0x32, 0x34, 0x33, 0x34, 0x34, 0x33, 0x31, 0x33, 0x32, 0x33, 0x33,
  0x33, 0x34, 0x33, 0x35, 0x33, 0x36, 0x33, 0x37, 0x33, 0x38, 0x33, 0x39,
  0x29, 0x0d, 0x0a, 0x30, 0x2d, 0x31, 0x3a, 0x32, 0x34, 0x2e, 0x32, 0x2e,
  0x31, 0x28, 0x31, 0x30, 0x31, 0x32, 0x30, 0x39, 0x31, 0x31, 0x32, 0x35,
  0x30, 0x30, 0x57, 0x29, 0x28, 0x31, 0x32, 0x37, 0x38, 0x35, 0x2e, 0x31,
  0x32, 0x33, 0x2a, 0x6d, 0x33, 0x29, 0x0d, 0x0a, 0x21, 0x45, 0x46, 0x32,
  0x46, 0x0d, 0x0a
};

void test_function_calculator_division(void) {
    StaticJsonDocument<8192> jsonData;
    DlmsReader dmr;
    dmr.setJson(&jsonData); 
    dmr.ParseData(data1_dat, 581);
    serializeJson(jsonData, resultStr, 4096);
    printf(resultStr);
    TEST_ASSERT_EQUAL(1,1);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_function_calculator_division);
    UNITY_END();

    return 0;
}
