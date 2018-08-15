


#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "emulated_disk.h"

#ifdef SECTOR_SIZE
#error "Sector size already defined."
#endif

#define SECTOR_SIZE 512

static const uint8_t sector0[] = { 0xFA, 0xBE, 0x00, 0x7C, 0xBF, 0x00, 0x7A, 0xB9, 0x00, 0x01, 0xFC, 0x0E, 0x1F, 0x0E, 0x07, 0xF3, 0xA5, 0xEA, 0x16, 0x7A, 0x00, 0x00, 0xBB, 0xBE, 0x7B, 0x33, 0xC9, 0x80, 0x3F, 0x80, 0x75, 0x06, 0xFE, 0xC5, 0x8B, 0xF3, 0xEB, 0x07, 0x80, 0x3F, 0x00, 0x75, 0x02, 0xFE, 0xC1, 0x83, 0xC3, 0x10, 0x81, 0xFB, 0xFE, 0x7B, 0x72, 0xE5, 0x83, 0xF9, 0x04, 0x74, 0x0B, 0x81, 0xF9, 0x03, 0x01, 0x74, 0x0A, 0xBB, 0xA5, 0x7A, 0xEB, 0x2C, 0xBB, 0x87, 0x7A, 0xEB, 0x27, 0x8B, 0x4C, 0x02, 0x8B, 0x14, 0xB8, 0x01, 0x02, 0xBB, 0x00, 0x7C, 0xCD, 0x13, 0x73, 0x05, 0xBB, 0xBC, 0x7A, 0xEB, 0x13, 0x2E, 0xA1, 0xFE, 0x7D, 0x3D, 0x55, 0xAA, 0x74, 0x05, 0xBB, 0xBC, 0x7A, 0xEB, 0x05, 0xEA, 0x00, 0x7C, 0x00, 0x00, 0x2E, 0x8A, 0x07, 0x3C, 0x00, 0x74, 0x0C, 0x53, 0xBB, 0x07, 0x00, 0xB4, 0x0E, 0xCD, 0x10, 0x5B, 0x43, 0xEB, 0xED, 0xEB, 0xFE, 0x4E, 0x6F, 0x20, 0x62, 0x6F, 0x6F, 0x74, 0x61, 0x62, 0x6C, 0x65, 0x20, 0x70, 0x61, 0x72, 0x74, 0x69, 0x74, 0x6F, 0x6E, 0x20, 0x69, 0x6E, 0x20, 0x74, 0x61, 0x62, 0x6C, 0x65, 0x00, 0x49, 0x6E, 0x76, 0x61, 0x6C, 0x69, 0x64, 0x20, 0x50, 0x61, 0x72, 0x74, 0x69, 0x74, 0x6F, 0x6E, 0x20, 0x74, 0x61, 0x62, 0x6C, 0x65, 0x00, 0x49, 0x6E, 0x76, 0x61, 0x6C, 0x69, 0x64, 0x20, 0x6F, 0x72, 0x20, 0x64, 0x61, 0x6D, 0x61, 0x67, 0x65, 0x64, 0x20, 0x42, 0x6F, 0x6F, 0x74, 0x61, 0x62, 0x6C, 0x65, 0x20, 0x70, 0x61, 0x72, 0x74, 0x69, 0x74, 0x69, 0x6F, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3A, 0x93, 0xFA, 0xC3, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x0C, 0x14, 0xD5, 0xC9, 0x80, 0x1F, 0x00, 0x00, 0x80, 0x40, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA, };
static const uint8_t sector16384[] = { 0x61, 0x73, 0x64, 0x66, 0x6A, 0x6B, 0x6C, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
static const uint8_t sector14400[] = { 0xF8, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
static const uint8_t sector8064[] = { 0xEB, 0x58, 0x90, 0x4D, 0x53, 0x57, 0x49, 0x4E, 0x34, 0x2E, 0x31, 0x00, 0x02, 0x40, 0xC0, 0x18, 0x02, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x3F, 0x00, 0x80, 0x00, 0x80, 0x1F, 0x00, 0x00, 0x80, 0x40, 0x77, 0x00, 0xC0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x29, 0xFE, 0x89, 0x6C, 0x9A, 0x50, 0x41, 0x54, 0x52, 0x49, 0x4F, 0x54, 0x20, 0x20, 0x20, 0x20, 0x46, 0x41, 0x54, 0x33, 0x32, 0x20, 0x20, 0x20, 0xFA, 0x33, 0xC9, 0x8E, 0xD1, 0xBC, 0xF8, 0x7B, 0x8E, 0xC1, 0xBD, 0x78, 0x00, 0xC5, 0x76, 0x00, 0x1E, 0x56, 0x16, 0x55, 0xBF, 0x22, 0x05, 0x89, 0x7E, 0x00, 0x89, 0x4E, 0x02, 0xB1, 0x0B, 0xFC, 0xF3, 0xA4, 0x8E, 0xD9, 0xBD, 0x00, 0x7C, 0xC6, 0x45, 0xFE, 0x0F, 0x8B, 0x46, 0x18, 0x88, 0x45, 0xF9, 0x38, 0x4E, 0x40, 0x7D, 0x25, 0x8B, 0xC1, 0x99, 0xBB, 0x00, 0x07, 0xE8, 0x97, 0x00, 0x72, 0x1A, 0x83, 0xEB, 0x3A, 0x66, 0xA1, 0x1C, 0x7C, 0x66, 0x3B, 0x07, 0x8A, 0x57, 0xFC, 0x75, 0x06, 0x80, 0xCA, 0x02, 0x88, 0x56, 0x02, 0x80, 0xC3, 0x10, 0x73, 0xED, 0xBF, 0x02, 0x00, 0x83, 0x7E, 0x16, 0x00, 0x75, 0x45, 0x8B, 0x46, 0x1C, 0x8B, 0x56, 0x1E, 0xB9, 0x03, 0x00, 0x49, 0x40, 0x75, 0x01, 0x42, 0xBB, 0x00, 0x7E, 0xE8, 0x5F, 0x00, 0x73, 0x26, 0xB0, 0xF8, 0x4F, 0x74, 0x1D, 0x8B, 0x46, 0x32, 0x33, 0xD2, 0xB9, 0x03, 0x00, 0x3B, 0xC8, 0x77, 0x1E, 0x8B, 0x76, 0x0E, 0x3B, 0xCE, 0x73, 0x17, 0x2B, 0xF1, 0x03, 0x46, 0x1C, 0x13, 0x56, 0x1E, 0xEB, 0xD1, 0x73, 0x0B, 0xEB, 0x27, 0x83, 0x7E, 0x2A, 0x00, 0x77, 0x03, 0xE9, 0xFD, 0x02, 0xBE, 0x7E, 0x7D, 0xAC, 0x98, 0x03, 0xF0, 0xAC, 0x84, 0xC0, 0x74, 0x17, 0x3C, 0xFF, 0x74, 0x09, 0xB4, 0x0E, 0xBB, 0x07, 0x00, 0xCD, 0x10, 0xEB, 0xEE, 0xBE, 0x81, 0x7D, 0xEB, 0xE5, 0xBE, 0x7F, 0x7D, 0xEB, 0xE0, 0x98, 0xCD, 0x16, 0x5E, 0x1F, 0x66, 0x8F, 0x04, 0xCD, 0x19, 0x41, 0x56, 0x66, 0x6A, 0x00, 0x52, 0x50, 0x06, 0x53, 0x6A, 0x01, 0x6A, 0x10, 0x8B, 0xF4, 0x60, 0x80, 0x7E, 0x02, 0x0E, 0x75, 0x04, 0xB4, 0x42, 0xEB, 0x1D, 0x91, 0x92, 0x33, 0xD2, 0xF7, 0x76, 0x18, 0x91, 0xF7, 0x76, 0x18, 0x42, 0x87, 0xCA, 0xF7, 0x76, 0x1A, 0x8A, 0xF2, 0x8A, 0xE8, 0xC0, 0xCC, 0x02, 0x0A, 0xCC, 0xB8, 0x01, 0x02, 0x8A, 0x56, 0x40, 0xCD, 0x13, 0x61, 0x8D, 0x64, 0x10, 0x5E, 0x72, 0x0A, 0x40, 0x75, 0x01, 0x42, 0x03, 0x5E, 0x0B, 0x49, 0x75, 0xB4, 0xC3, 0x03, 0x18, 0x01, 0x27, 0x0D, 0x0A, 0x49, 0x6E, 0x76, 0x61, 0x6C, 0x69, 0x64, 0x20, 0x73, 0x79, 0x73, 0x74, 0x65, 0x6D, 0x20, 0x64, 0x69, 0x73, 0x6B, 0xFF, 0x0D, 0x0A, 0x44, 0x69, 0x73, 0x6B, 0x20, 0x49, 0x2F, 0x4F, 0x20, 0x65, 0x72, 0x72, 0x6F, 0x72, 0xFF, 0x0D, 0x0A, 0x52, 0x65, 0x70, 0x6C, 0x61, 0x63, 0x65, 0x20, 0x74, 0x68, 0x65, 0x20, 0x64, 0x69, 0x73, 0x6B, 0x2C, 0x20, 0x61, 0x6E, 0x64, 0x20, 0x74, 0x68, 0x65, 0x6E, 0x20, 0x70, 0x72, 0x65, 0x73, 0x73, 0x20, 0x61, 0x6E, 0x79, 0x20, 0x6B, 0x65, 0x79, 0x0D, 0x0A, 0x00, 0x00, 0x00, 0x49, 0x4F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x53, 0x59, 0x53, 0x4D, 0x53, 0x44, 0x4F, 0x53, 0x20, 0x20, 0x20, 0x53, 0x59, 0x53, 0x7E, 0x01, 0x00, 0x57, 0x49, 0x4E, 0x42, 0x4F, 0x4F, 0x54, 0x20, 0x53, 0x59, 0x53, 0x00, 0x00, 0x55, 0xAA, };
static const uint8_t sector8065[] = { 0x52, 0x52, 0x61, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x72, 0x72, 0x41, 0x61, 0x7F, 0xDC, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA, };
static const uint8_t sector8066[] = { 0xFA, 0x66, 0x0F, 0xB6, 0x46, 0x10, 0x66, 0x8B, 0x4E, 0x24, 0x66, 0xF7, 0xE1, 0x66, 0x03, 0x46, 0x1C, 0x66, 0x0F, 0xB7, 0x56, 0x0E, 0x66, 0x03, 0xC2, 0x33, 0xC9, 0x66, 0x89, 0x46, 0xFC, 0x66, 0xC7, 0x46, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFA, 0x66, 0x8B, 0x46, 0x2C, 0x66, 0x83, 0xF8, 0x02, 0x0F, 0x82, 0xCF, 0xFC, 0x66, 0x3D, 0xF8, 0xFF, 0xFF, 0x0F, 0x0F, 0x83, 0xC5, 0xFC, 0x66, 0x0F, 0xA4, 0xC2, 0x10, 0xFB, 0x52, 0x50, 0xFA, 0x66, 0xC1, 0xE0, 0x10, 0x66, 0x0F, 0xAC, 0xD0, 0x10, 0x66, 0x83, 0xE8, 0x02, 0x66, 0x0F, 0xB6, 0x5E, 0x0D, 0x8B, 0xF3, 0x66, 0xF7, 0xE3, 0x66, 0x03, 0x46, 0xFC, 0x66, 0x0F, 0xA4, 0xC2, 0x10, 0xFB, 0xBB, 0x00, 0x07, 0x8B, 0xFB, 0xB9, 0x01, 0x00, 0xE8, 0xBE, 0xFC, 0x0F, 0x82, 0xAA, 0xFC, 0x38, 0x2D, 0x74, 0x1E, 0xB1, 0x0B, 0x56, 0xBE, 0xD8, 0x7D, 0xF3, 0xA6, 0x5E, 0x74, 0x19, 0x03, 0xF9, 0x83, 0xC7, 0x15, 0x3B, 0xFB, 0x72, 0xE8, 0x4E, 0x75, 0xD6, 0x58, 0x5A, 0xE8, 0x66, 0x00, 0x72, 0xAB, 0x83, 0xC4, 0x04, 0xE9, 0x64, 0xFC, 0x83, 0xC4, 0x04, 0x8B, 0x75, 0x09, 0x8B, 0x7D, 0x0F, 0x8B, 0xC6, 0xFA, 0x66, 0xC1, 0xE0, 0x10, 0x8B, 0xC7, 0x66, 0x83, 0xF8, 0x02, 0x72, 0x3B, 0x66, 0x3D, 0xF8, 0xFF, 0xFF, 0x0F, 0x73, 0x33, 0x66, 0x48, 0x66, 0x48, 0x66, 0x0F, 0xB6, 0x4E, 0x0D, 0x66, 0xF7, 0xE1, 0x66, 0x03, 0x46, 0xFC, 0x66, 0x0F, 0xA4, 0xC2, 0x10, 0xFB, 0xBB, 0x00, 0x07, 0x53, 0xB9, 0x04, 0x00, 0xE8, 0x52, 0xFC, 0x5B, 0x0F, 0x82, 0x3D, 0xFC, 0x81, 0x3F, 0x4D, 0x5A, 0x75, 0x08, 0x81, 0xBF, 0x00, 0x02, 0x42, 0x4A, 0x74, 0x06, 0xBE, 0x80, 0x7D, 0xE9, 0x0E, 0xFC, 0xEA, 0x00, 0x02, 0x70, 0x00, 0x03, 0xC0, 0x13, 0xD2, 0x03, 0xC0, 0x13, 0xD2, 0xE8, 0x18, 0x00, 0xFA, 0x26, 0x66, 0x8B, 0x01, 0x66, 0x25, 0xFF, 0xFF, 0xFF, 0x0F, 0x66, 0x0F, 0xA4, 0xC2, 0x10, 0x66, 0x3D, 0xF8, 0xFF, 0xFF, 0x0F, 0xFB, 0xC3, 0xBF, 0x00, 0x7E, 0xFA, 0x66, 0xC1, 0xE0, 0x10, 0x66, 0x0F, 0xAC, 0xD0, 0x10, 0x66, 0x0F, 0xB7, 0x4E, 0x0B, 0x66, 0x33, 0xD2, 0x66, 0xF7, 0xF1, 0x66, 0x3B, 0x46, 0xF8, 0x74, 0x44, 0x66, 0x89, 0x46, 0xF8, 0x66, 0x03, 0x46, 0x1C, 0x66, 0x0F, 0xB7, 0x4E, 0x0E, 0x66, 0x03, 0xC1, 0x66, 0x0F, 0xB7, 0x5E, 0x28, 0x83, 0xE3, 0x0F, 0x74, 0x16, 0x3A, 0x5E, 0x10, 0x0F, 0x83, 0xA4, 0xFB, 0x52, 0x66, 0x8B, 0xC8, 0x66, 0x8B, 0x46, 0x24, 0x66, 0xF7, 0xE3, 0x66, 0x03, 0xC1, 0x5A, 0x52, 0x66, 0x0F, 0xA4, 0xC2, 0x10, 0xFB, 0x8B, 0xDF, 0xB9, 0x01, 0x00, 0xE8, 0xB4, 0xFB, 0x5A, 0x0F, 0x82, 0x9F, 0xFB, 0xFB, 0x8B, 0xDA, 0xC3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA, };
static const uint8_t sector8072[] = { 0xEB, 0x58, 0x90, 0x4D, 0x53, 0x57, 0x49, 0x4E, 0x34, 0x2E, 0x31, 0x00, 0x02, 0x40, 0xC0, 0x18, 0x02, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x3F, 0x00, 0x80, 0x00, 0x80, 0x1F, 0x00, 0x00, 0x80, 0x40, 0x77, 0x00, 0xC0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x29, 0xFE, 0x89, 0x6C, 0x9A, 0x50, 0x41, 0x54, 0x52, 0x49, 0x4F, 0x54, 0x20, 0x20, 0x20, 0x20, 0x46, 0x41, 0x54, 0x33, 0x32, 0x20, 0x20, 0x20, 0xFA, 0x33, 0xC9, 0x8E, 0xD1, 0xBC, 0xF8, 0x7B, 0x8E, 0xC1, 0xBD, 0x78, 0x00, 0xC5, 0x76, 0x00, 0x1E, 0x56, 0x16, 0x55, 0xBF, 0x22, 0x05, 0x89, 0x7E, 0x00, 0x89, 0x4E, 0x02, 0xB1, 0x0B, 0xFC, 0xF3, 0xA4, 0x8E, 0xD9, 0xBD, 0x00, 0x7C, 0xC6, 0x45, 0xFE, 0x0F, 0x8B, 0x46, 0x18, 0x88, 0x45, 0xF9, 0x38, 0x4E, 0x40, 0x7D, 0x25, 0x8B, 0xC1, 0x99, 0xBB, 0x00, 0x07, 0xE8, 0x97, 0x00, 0x72, 0x1A, 0x83, 0xEB, 0x3A, 0x66, 0xA1, 0x1C, 0x7C, 0x66, 0x3B, 0x07, 0x8A, 0x57, 0xFC, 0x75, 0x06, 0x80, 0xCA, 0x02, 0x88, 0x56, 0x02, 0x80, 0xC3, 0x10, 0x73, 0xED, 0xBF, 0x02, 0x00, 0x83, 0x7E, 0x16, 0x00, 0x75, 0x45, 0x8B, 0x46, 0x1C, 0x8B, 0x56, 0x1E, 0xB9, 0x03, 0x00, 0x49, 0x40, 0x75, 0x01, 0x42, 0xBB, 0x00, 0x7E, 0xE8, 0x5F, 0x00, 0x73, 0x26, 0xB0, 0xF8, 0x4F, 0x74, 0x1D, 0x8B, 0x46, 0x32, 0x33, 0xD2, 0xB9, 0x03, 0x00, 0x3B, 0xC8, 0x77, 0x1E, 0x8B, 0x76, 0x0E, 0x3B, 0xCE, 0x73, 0x17, 0x2B, 0xF1, 0x03, 0x46, 0x1C, 0x13, 0x56, 0x1E, 0xEB, 0xD1, 0x73, 0x0B, 0xEB, 0x27, 0x83, 0x7E, 0x2A, 0x00, 0x77, 0x03, 0xE9, 0xFD, 0x02, 0xBE, 0x7E, 0x7D, 0xAC, 0x98, 0x03, 0xF0, 0xAC, 0x84, 0xC0, 0x74, 0x17, 0x3C, 0xFF, 0x74, 0x09, 0xB4, 0x0E, 0xBB, 0x07, 0x00, 0xCD, 0x10, 0xEB, 0xEE, 0xBE, 0x81, 0x7D, 0xEB, 0xE5, 0xBE, 0x7F, 0x7D, 0xEB, 0xE0, 0x98, 0xCD, 0x16, 0x5E, 0x1F, 0x66, 0x8F, 0x04, 0xCD, 0x19, 0x41, 0x56, 0x66, 0x6A, 0x00, 0x52, 0x50, 0x06, 0x53, 0x6A, 0x01, 0x6A, 0x10, 0x8B, 0xF4, 0x60, 0x80, 0x7E, 0x02, 0x0E, 0x75, 0x04, 0xB4, 0x42, 0xEB, 0x1D, 0x91, 0x92, 0x33, 0xD2, 0xF7, 0x76, 0x18, 0x91, 0xF7, 0x76, 0x18, 0x42, 0x87, 0xCA, 0xF7, 0x76, 0x1A, 0x8A, 0xF2, 0x8A, 0xE8, 0xC0, 0xCC, 0x02, 0x0A, 0xCC, 0xB8, 0x01, 0x02, 0x8A, 0x56, 0x40, 0xCD, 0x13, 0x61, 0x8D, 0x64, 0x10, 0x5E, 0x72, 0x0A, 0x40, 0x75, 0x01, 0x42, 0x03, 0x5E, 0x0B, 0x49, 0x75, 0xB4, 0xC3, 0x03, 0x18, 0x01, 0x27, 0x0D, 0x0A, 0x49, 0x6E, 0x76, 0x61, 0x6C, 0x69, 0x64, 0x20, 0x73, 0x79, 0x73, 0x74, 0x65, 0x6D, 0x20, 0x64, 0x69, 0x73, 0x6B, 0xFF, 0x0D, 0x0A, 0x44, 0x69, 0x73, 0x6B, 0x20, 0x49, 0x2F, 0x4F, 0x20, 0x65, 0x72, 0x72, 0x6F, 0x72, 0xFF, 0x0D, 0x0A, 0x52, 0x65, 0x70, 0x6C, 0x61, 0x63, 0x65, 0x20, 0x74, 0x68, 0x65, 0x20, 0x64, 0x69, 0x73, 0x6B, 0x2C, 0x20, 0x61, 0x6E, 0x64, 0x20, 0x74, 0x68, 0x65, 0x6E, 0x20, 0x70, 0x72, 0x65, 0x73, 0x73, 0x20, 0x61, 0x6E, 0x79, 0x20, 0x6B, 0x65, 0x79, 0x0D, 0x0A, 0x00, 0x00, 0x00, 0x49, 0x4F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x53, 0x59, 0x53, 0x4D, 0x53, 0x44, 0x4F, 0x53, 0x20, 0x20, 0x20, 0x53, 0x59, 0x53, 0x7E, 0x01, 0x00, 0x57, 0x49, 0x4E, 0x42, 0x4F, 0x4F, 0x54, 0x20, 0x53, 0x59, 0x53, 0x00, 0x00, 0x55, 0xAA, };
static const uint8_t sector8073[] = { 0x52, 0x52, 0x61, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x72, 0x72, 0x41, 0x61, 0xFF, 0xFF, 0xFF, 0xFF, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA, };
static const uint8_t sector8074[] = { 0xFA, 0x66, 0x0F, 0xB6, 0x46, 0x10, 0x66, 0x8B, 0x4E, 0x24, 0x66, 0xF7, 0xE1, 0x66, 0x03, 0x46, 0x1C, 0x66, 0x0F, 0xB7, 0x56, 0x0E, 0x66, 0x03, 0xC2, 0x33, 0xC9, 0x66, 0x89, 0x46, 0xFC, 0x66, 0xC7, 0x46, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFA, 0x66, 0x8B, 0x46, 0x2C, 0x66, 0x83, 0xF8, 0x02, 0x0F, 0x82, 0xCF, 0xFC, 0x66, 0x3D, 0xF8, 0xFF, 0xFF, 0x0F, 0x0F, 0x83, 0xC5, 0xFC, 0x66, 0x0F, 0xA4, 0xC2, 0x10, 0xFB, 0x52, 0x50, 0xFA, 0x66, 0xC1, 0xE0, 0x10, 0x66, 0x0F, 0xAC, 0xD0, 0x10, 0x66, 0x83, 0xE8, 0x02, 0x66, 0x0F, 0xB6, 0x5E, 0x0D, 0x8B, 0xF3, 0x66, 0xF7, 0xE3, 0x66, 0x03, 0x46, 0xFC, 0x66, 0x0F, 0xA4, 0xC2, 0x10, 0xFB, 0xBB, 0x00, 0x07, 0x8B, 0xFB, 0xB9, 0x01, 0x00, 0xE8, 0xBE, 0xFC, 0x0F, 0x82, 0xAA, 0xFC, 0x38, 0x2D, 0x74, 0x1E, 0xB1, 0x0B, 0x56, 0xBE, 0xD8, 0x7D, 0xF3, 0xA6, 0x5E, 0x74, 0x19, 0x03, 0xF9, 0x83, 0xC7, 0x15, 0x3B, 0xFB, 0x72, 0xE8, 0x4E, 0x75, 0xD6, 0x58, 0x5A, 0xE8, 0x66, 0x00, 0x72, 0xAB, 0x83, 0xC4, 0x04, 0xE9, 0x64, 0xFC, 0x83, 0xC4, 0x04, 0x8B, 0x75, 0x09, 0x8B, 0x7D, 0x0F, 0x8B, 0xC6, 0xFA, 0x66, 0xC1, 0xE0, 0x10, 0x8B, 0xC7, 0x66, 0x83, 0xF8, 0x02, 0x72, 0x3B, 0x66, 0x3D, 0xF8, 0xFF, 0xFF, 0x0F, 0x73, 0x33, 0x66, 0x48, 0x66, 0x48, 0x66, 0x0F, 0xB6, 0x4E, 0x0D, 0x66, 0xF7, 0xE1, 0x66, 0x03, 0x46, 0xFC, 0x66, 0x0F, 0xA4, 0xC2, 0x10, 0xFB, 0xBB, 0x00, 0x07, 0x53, 0xB9, 0x04, 0x00, 0xE8, 0x52, 0xFC, 0x5B, 0x0F, 0x82, 0x3D, 0xFC, 0x81, 0x3F, 0x4D, 0x5A, 0x75, 0x08, 0x81, 0xBF, 0x00, 0x02, 0x42, 0x4A, 0x74, 0x06, 0xBE, 0x80, 0x7D, 0xE9, 0x0E, 0xFC, 0xEA, 0x00, 0x02, 0x70, 0x00, 0x03, 0xC0, 0x13, 0xD2, 0x03, 0xC0, 0x13, 0xD2, 0xE8, 0x18, 0x00, 0xFA, 0x26, 0x66, 0x8B, 0x01, 0x66, 0x25, 0xFF, 0xFF, 0xFF, 0x0F, 0x66, 0x0F, 0xA4, 0xC2, 0x10, 0x66, 0x3D, 0xF8, 0xFF, 0xFF, 0x0F, 0xFB, 0xC3, 0xBF, 0x00, 0x7E, 0xFA, 0x66, 0xC1, 0xE0, 0x10, 0x66, 0x0F, 0xAC, 0xD0, 0x10, 0x66, 0x0F, 0xB7, 0x4E, 0x0B, 0x66, 0x33, 0xD2, 0x66, 0xF7, 0xF1, 0x66, 0x3B, 0x46, 0xF8, 0x74, 0x44, 0x66, 0x89, 0x46, 0xF8, 0x66, 0x03, 0x46, 0x1C, 0x66, 0x0F, 0xB7, 0x4E, 0x0E, 0x66, 0x03, 0xC1, 0x66, 0x0F, 0xB7, 0x5E, 0x28, 0x83, 0xE3, 0x0F, 0x74, 0x16, 0x3A, 0x5E, 0x10, 0x0F, 0x83, 0xA4, 0xFB, 0x52, 0x66, 0x8B, 0xC8, 0x66, 0x8B, 0x46, 0x24, 0x66, 0xF7, 0xE3, 0x66, 0x03, 0xC1, 0x5A, 0x52, 0x66, 0x0F, 0xA4, 0xC2, 0x10, 0xFB, 0x8B, 0xDF, 0xB9, 0x01, 0x00, 0xE8, 0xB4, 0xFB, 0x5A, 0x0F, 0x82, 0x9F, 0xFB, 0xFB, 0x8B, 0xDA, 0xC3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA, };
static const uint8_t sector16320[] = { 0x44, 0x52, 0x56, 0x30, 0x38, 0x30, 0x20, 0x20, 0x20, 0x20, 0x20, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x58, 0x88, 0x4B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE5, 0x52, 0x49, 0x54, 0x45, 0x20, 0x20, 0x20, 0x54, 0x58, 0x54, 0x20, 0x00, 0x00, 0x00, 0x00, 0xAE, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAE, 0x4A, 0x05, 0x00, 0x09, 0x00, 0x00, 0x00, 0xE5, 0x6E, 0x00, 0x65, 0x00, 0x6F, 0x00, 0x78, 0x00, 0x5F, 0x00, 0x0F, 0x00, 0x17, 0x65, 0x00, 0x6D, 0x00, 0x62, 0x00, 0x65, 0x00, 0x64, 0x00, 0x64, 0x00, 0x00, 0x00, 0x5F, 0x00, 0x32, 0x00, 0xE5, 0x45, 0x4F, 0x58, 0x5F, 0x45, 0x7E, 0x31, 0x47, 0x4C, 0x46, 0x20, 0x00, 0x09, 0x20, 0x84, 0x3B, 0x43, 0x3B, 0x43, 0x00, 0x00, 0x6F, 0x6C, 0x39, 0x43, 0x03, 0x00, 0xA0, 0x06, 0x60, 0x02, 0xE5, 0x30, 0x00, 0x31, 0x00, 0x33, 0x00, 0x30, 0x00, 0x34, 0x00, 0x0F, 0x00, 0xCD, 0x31, 0x00, 0x30, 0x00, 0x2E, 0x00, 0x62, 0x00, 0x69, 0x00, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xE5, 0x6E, 0x00, 0x65, 0x00, 0x6F, 0x00, 0x78, 0x00, 0x5F, 0x00, 0x0F, 0x00, 0xCD, 0x73, 0x00, 0x65, 0x00, 0x63, 0x00, 0x74, 0x00, 0x35, 0x00, 0x31, 0x00, 0x00, 0x00, 0x5F, 0x00, 0x32, 0x00, 0xE5, 0x45, 0x4F, 0x58, 0x5F, 0x53, 0x7E, 0x31, 0x42, 0x49, 0x4E, 0x20, 0x00, 0x13, 0x22, 0x84, 0x3B, 0x43, 0x3B, 0x43, 0x00, 0x00, 0x6F, 0x6C, 0x39, 0x43, 0xC4, 0x04, 0x1A, 0x00, 0x00, 0x00, 0xE5, 0x2E, 0x00, 0x5F, 0x00, 0x2E, 0x00, 0x54, 0x00, 0x72, 0x00, 0x0F, 0x00, 0x0C, 0x61, 0x00, 0x73, 0x00, 0x68, 0x00, 0x65, 0x00, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xE5, 0x7E, 0x31, 0x20, 0x20, 0x20, 0x20, 0x20, 0x54, 0x52, 0x41, 0x22, 0x00, 0x7D, 0x45, 0x84, 0x3B, 0x43, 0x3B, 0x43, 0x00, 0x00, 0x45, 0x84, 0x3B, 0x43, 0xC6, 0x04, 0x00, 0x10, 0x00, 0x00, 0xE5, 0x52, 0x41, 0x53, 0x48, 0x45, 0x7E, 0x31, 0x52, 0x41, 0x34, 0x12, 0x00, 0x7D, 0x45, 0x84, 0x3B, 0x43, 0x3B, 0x43, 0x00, 0x00, 0x45, 0x84, 0x3B, 0x43, 0xC5, 0x04, 0x00, 0x00, 0x00, 0x00, 0xE5, 0x2E, 0x00, 0x54, 0x00, 0x72, 0x00, 0x61, 0x00, 0x73, 0x00, 0x0F, 0x00, 0x25, 0x68, 0x00, 0x65, 0x00, 0x73, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xE5, 0x52, 0x41, 0x53, 0x48, 0x45, 0x7E, 0x31, 0x20, 0x20, 0x20, 0x12, 0x00, 0x7D, 0x45, 0x84, 0x3B, 0x43, 0x3B, 0x43, 0x00, 0x00, 0x45, 0x84, 0x3B, 0x43, 0xC5, 0x04, 0x00, 0x80, 0x00, 0x00, 0xE5, 0x30, 0x00, 0x30, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0x21, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xE5, 0x2E, 0x00, 0x53, 0x00, 0x70, 0x00, 0x6F, 0x00, 0x74, 0x00, 0x0F, 0x00, 0x21, 0x6C, 0x00, 0x69, 0x00, 0x67, 0x00, 0x68, 0x00, 0x74, 0x00, 0x2D, 0x00, 0x00, 0x00, 0x56, 0x00, 0x31, 0x00, 0xE5, 0x50, 0x4F, 0x54, 0x4C, 0x49, 0x7E, 0x31, 0x20, 0x20, 0x20, 0x12, 0x00, 0x80, 0x45, 0x84, 0x3B, 0x43, 0x3B, 0x43, 0x00, 0x00, 0x45, 0x84, 0x3B, 0x43, 0xC7, 0x04, 0x00, 0x80, 0x00, 0x00, 0xE5, 0x2E, 0x00, 0x66, 0x00, 0x73, 0x00, 0x65, 0x00, 0x76, 0x00, 0x0F, 0x00, 0xDA, 0x65, 0x00, 0x6E, 0x00, 0x74, 0x00, 0x73, 0x00, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, };
static const uint8_t sector16321[] = { 0xE5, 0x53, 0x45, 0x56, 0x45, 0x4E, 0x7E, 0x31, 0x20, 0x20, 0x20, 0x12, 0x00, 0x82, 0x45, 0x84, 0x3B, 0x43, 0x3B, 0x43, 0x00, 0x00, 0x45, 0x84, 0x3B, 0x43, 0xD0, 0x04, 0x00, 0x80, 0x00, 0x00, 0x52, 0x45, 0x41, 0x44, 0x20, 0x20, 0x20, 0x20, 0x54, 0x58, 0x54, 0x20, 0x00, 0x00, 0x82, 0x58, 0x88, 0x4B, 0x93, 0x4B, 0x00, 0x00, 0xD0, 0x80, 0x87, 0x4B, 0x03, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };

static struct EMULATED_DISK disk = {0, NULL};

void DRV080_writeSector(	
    const uint8_t *buff,	
    uint32_t lba,		
    size_t count			
)
{
    size_t i;
    
    for(i=0; i<count; i++)
    {
        EmulatedDiskSectorWrite(&disk, (uint32_t)(lba + i), (uint8_t*)&buff[SECTOR_SIZE*i], true);
    }
    
    
}

void DRV080_readSector(	
    uint8_t *buff,	
    uint32_t lba,		
    size_t count			
)
{
    size_t i;
    
    for(i=0; i<count; i++)
    {
        EmulatedDiskSectorRead(&disk, (uint32_t)(lba + i), (uint8_t*)&buff[SECTOR_SIZE*i]);
    }
    
    
}

void DRV080_initialize(void)
{    
    EmulatedDiskCreate(&disk, SECTOR_SIZE);
    
    DRV080_writeSector((const uint8_t*)sector0, 0, 1);
    DRV080_writeSector((const uint8_t*)sector16384, 16384, 1);
    DRV080_writeSector((const uint8_t*)sector14400, 14400, 1);
    DRV080_writeSector((const uint8_t*)sector8064, 8064, 1);
    DRV080_writeSector((const uint8_t*)sector8065, 8065, 1);
    DRV080_writeSector((const uint8_t*)sector8066, 8066, 1);
    DRV080_writeSector((const uint8_t*)sector8072, 8072, 1);
    DRV080_writeSector((const uint8_t*)sector8073, 8073, 1);
    DRV080_writeSector((const uint8_t*)sector8074, 8074, 1);
    DRV080_writeSector((const uint8_t*)sector16320, 16320, 1);
    DRV080_writeSector((const uint8_t*)sector16321, 16321, 1);

}

void DRV080_print(void)
{
    EmulatedDiskPrint(&disk);
}

static const char id[] = "DRV080";
const char* DRV080_id(void)
{
    return id;
}

struct EMULATED_DRIVE DRV080 = { &DRV080_initialize, &DRV080_print, &DRV080_id};

