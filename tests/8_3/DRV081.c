


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

static const uint8_t sector0[] = { 0xFA, 0x33, 0xC0, 0x8E, 0xD0, 0xBC, 0x00, 0x7C, 0x8B, 0xF4, 0x50, 0x07, 0x50, 0x1F, 0xFB, 0xFC, 0xBF, 0x00, 0x06, 0xB9, 0x00, 0x01, 0xF2, 0xA5, 0xEA, 0x1D, 0x06, 0x00, 0x00, 0xBE, 0xBE, 0x07, 0xB3, 0x04, 0x80, 0x3C, 0x80, 0x74, 0x0E, 0x80, 0x3C, 0x00, 0x75, 0x1C, 0x83, 0xC6, 0x10, 0xFE, 0xCB, 0x75, 0xEF, 0xCD, 0x18, 0x8B, 0x14, 0x8B, 0x4C, 0x02, 0x8B, 0xEE, 0x83, 0xC6, 0x10, 0xFE, 0xCB, 0x74, 0x1A, 0x80, 0x3C, 0x00, 0x74, 0xF4, 0xBE, 0x8B, 0x06, 0xAC, 0x3C, 0x00, 0x74, 0x0B, 0x56, 0xBB, 0x07, 0x00, 0xB4, 0x0E, 0xCD, 0x10, 0x5E, 0xEB, 0xF0, 0xEB, 0xFE, 0xBF, 0x05, 0x00, 0xBB, 0x00, 0x7C, 0xB8, 0x01, 0x02, 0x57, 0xCD, 0x13, 0x5F, 0x73, 0x0C, 0x33, 0xC0, 0xCD, 0x13, 0x4F, 0x75, 0xED, 0xBE, 0xA3, 0x06, 0xEB, 0xD3, 0xBE, 0xC2, 0x06, 0xBF, 0xFE, 0x7D, 0x81, 0x3D, 0x55, 0xAA, 0x75, 0xC7, 0x8B, 0xF5, 0xEA, 0x00, 0x7C, 0x00, 0x00, 0x49, 0x6E, 0x76, 0x61, 0x6C, 0x69, 0x64, 0x20, 0x70, 0x61, 0x72, 0x74, 0x69, 0x74, 0x69, 0x6F, 0x6E, 0x20, 0x74, 0x61, 0x62, 0x6C, 0x65, 0x00, 0x45, 0x72, 0x72, 0x6F, 0x72, 0x20, 0x6C, 0x6F, 0x61, 0x64, 0x69, 0x6E, 0x67, 0x20, 0x6F, 0x70, 0x65, 0x72, 0x61, 0x74, 0x69, 0x6E, 0x67, 0x20, 0x73, 0x79, 0x73, 0x74, 0x65, 0x6D, 0x00, 0x4D, 0x69, 0x73, 0x73, 0x69, 0x6E, 0x67, 0x20, 0x6F, 0x70, 0x65, 0x72, 0x61, 0x74, 0x69, 0x6E, 0x67, 0x20, 0x73, 0x79, 0x73, 0x74, 0x65, 0x6D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x2D, 0xF7, 0x91, 0x00, 0x00, 0x80, 0x01, 0x01, 0x00, 0x06, 0x0F, 0xE0, 0xC6, 0x20, 0x00, 0x00, 0x00, 0xE0, 0x8F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA, };
static const uint8_t sector520[] = { 0xE5, 0x52, 0x49, 0x54, 0x45, 0x20, 0x20, 0x20, 0x54, 0x58, 0x54, 0x20, 0x00, 0x00, 0x00, 0x00, 0xAE, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAE, 0x4A, 0x03, 0x00, 0x09, 0x00, 0x00, 0x00, 0xE5, 0x20, 0x00, 0x41, 0x00, 0x6C, 0x00, 0x6C, 0x00, 0x20, 0x00, 0x0F, 0x00, 0xC1, 0x74, 0x00, 0x68, 0x00, 0x65, 0x00, 0x20, 0x00, 0x52, 0x00, 0x65, 0x00, 0x00, 0x00, 0x73, 0x00, 0x74, 0x00, 0xE5, 0x32, 0x00, 0x35, 0x00, 0x36, 0x00, 0x20, 0x00, 0x4C, 0x00, 0x0F, 0x00, 0xC1, 0x65, 0x00, 0x61, 0x00, 0x76, 0x00, 0x65, 0x00, 0x20, 0x00, 0x4F, 0x00, 0x00, 0x00, 0x75, 0x00, 0x74, 0x00, 0xE5, 0x35, 0x36, 0x4C, 0x45, 0x41, 0x7E, 0x31, 0x4F, 0x47, 0x47, 0x20, 0x00, 0x5D, 0xC6, 0x5D, 0xF4, 0x3A, 0xF4, 0x3A, 0x00, 0x00, 0xB5, 0x6E, 0xD2, 0x3A, 0x02, 0x00, 0x9C, 0x23, 0x61, 0x00, 0xE5, 0x6E, 0x00, 0x6B, 0x00, 0x2E, 0x00, 0x6F, 0x00, 0x67, 0x00, 0x0F, 0x00, 0x35, 0x67, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xE5, 0x32, 0x00, 0x35, 0x00, 0x36, 0x00, 0x20, 0x00, 0x4E, 0x00, 0x0F, 0x00, 0x35, 0x65, 0x00, 0x76, 0x00, 0x65, 0x00, 0x72, 0x00, 0x20, 0x00, 0x54, 0x00, 0x00, 0x00, 0x68, 0x00, 0x69, 0x00, 0xE5, 0x35, 0x36, 0x4E, 0x45, 0x56, 0x7E, 0x31, 0x4F, 0x47, 0x47, 0x20, 0x00, 0x6E, 0xC7, 0x5D, 0xF4, 0x3A, 0xF4, 0x3A, 0x00, 0x00, 0x79, 0x6C, 0xD2, 0x3A, 0x15, 0x06, 0x53, 0x9A, 0x84, 0x00, 0xE5, 0x2E, 0x00, 0x6F, 0x00, 0x67, 0x00, 0x67, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x39, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xE5, 0x32, 0x00, 0x35, 0x00, 0x36, 0x00, 0x20, 0x00, 0x53, 0x00, 0x0F, 0x00, 0x39, 0x70, 0x00, 0x6F, 0x00, 0x74, 0x00, 0x6C, 0x00, 0x69, 0x00, 0x67, 0x00, 0x00, 0x00, 0x68, 0x00, 0x74, 0x00, 0xE5, 0x35, 0x36, 0x53, 0x50, 0x4F, 0x7E, 0x31, 0x4F, 0x47, 0x47, 0x20, 0x00, 0xAF, 0xC8, 0x5D, 0xF4, 0x3A, 0xF4, 0x3A, 0x00, 0x00, 0x6C, 0x6E, 0xD2, 0x3A, 0x5F, 0x0E, 0x73, 0x6D, 0x62, 0x00, 0xE5, 0x65, 0x00, 0x2E, 0x00, 0x6F, 0x00, 0x67, 0x00, 0x67, 0x00, 0x0F, 0x00, 0x9E, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xE5, 0x69, 0x00, 0x76, 0x00, 0x65, 0x00, 0x20, 0x00, 0x42, 0x00, 0x0F, 0x00, 0x9E, 0x6C, 0x00, 0x61, 0x00, 0x63, 0x00, 0x6B, 0x00, 0x20, 0x00, 0x48, 0x00, 0x00, 0x00, 0x6F, 0x00, 0x6C, 0x00, 0xE5, 0x32, 0x00, 0x35, 0x00, 0x36, 0x00, 0x20, 0x00, 0x53, 0x00, 0x0F, 0x00, 0x9E, 0x75, 0x00, 0x70, 0x00, 0x65, 0x00, 0x72, 0x00, 0x6D, 0x00, 0x61, 0x00, 0x00, 0x00, 0x73, 0x00, 0x73, 0x00, 0xE5, 0x35, 0x36, 0x53, 0x55, 0x50, 0x7E, 0x31, 0x4F, 0x47, 0x47, 0x20, 0x00, 0x07, 0xCA, 0x5D, 0xF4, 0x3A, 0xF4, 0x3A, 0x00, 0x00, 0x4C, 0x70, 0xD2, 0x3A, 0x86, 0x14, 0x4F, 0xAC, 0x66, 0x00, 0xE5, 0x2E, 0x00, 0x6F, 0x00, 0x67, 0x00, 0x67, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x23, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xE5, 0x6F, 0x00, 0x72, 0x00, 0x20, 0x00, 0x6D, 0x00, 0x79, 0x00, 0x0F, 0x00, 0x23, 0x20, 0x00, 0x42, 0x00, 0x65, 0x00, 0x6C, 0x00, 0x6F, 0x00, 0x76, 0x00, 0x00, 0x00, 0x65, 0x00, 0x64, 0x00, };
static const uint8_t sector521[] = { 0xE5, 0x32, 0x00, 0x35, 0x00, 0x36, 0x00, 0x20, 0x00, 0x54, 0x00, 0x0F, 0x00, 0x23, 0x72, 0x00, 0x65, 0x00, 0x6D, 0x00, 0x62, 0x00, 0x6C, 0x00, 0x65, 0x00, 0x00, 0x00, 0x20, 0x00, 0x66, 0x00, 0xE5, 0x35, 0x36, 0x54, 0x52, 0x45, 0x7E, 0x31, 0x4F, 0x47, 0x47, 0x20, 0x00, 0x11, 0xCB, 0x5D, 0xF4, 0x3A, 0xF4, 0x3A, 0x00, 0x00, 0x90, 0x6D, 0xD2, 0x3A, 0xF1, 0x1A, 0xC6, 0x6E, 0x70, 0x00, 0xE5, 0x75, 0x00, 0x6C, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x62, 0x00, 0x0F, 0x00, 0x73, 0x79, 0x00, 0x2E, 0x00, 0x6D, 0x00, 0x70, 0x00, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xE5, 0x30, 0x00, 0x39, 0x00, 0x36, 0x00, 0x20, 0x00, 0x42, 0x00, 0x0F, 0x00, 0x73, 0x65, 0x00, 0x6C, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x27, 0x00, 0x73, 0x00, 0x00, 0x00, 0x20, 0x00, 0x4C, 0x00, 0xE5, 0x39, 0x36, 0x42, 0x45, 0x4C, 0x7E, 0x31, 0x4D, 0x50, 0x33, 0x20, 0x00, 0x4D, 0xCC, 0x5D, 0xF4, 0x3A, 0x88, 0x4B, 0x00, 0x00, 0x4C, 0x5C, 0xD2, 0x3A, 0xF8, 0x21, 0xB9, 0x91, 0x19, 0x00, 0xE5, 0x75, 0x00, 0x6C, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x62, 0x00, 0x0F, 0x00, 0x0D, 0x79, 0x00, 0x2E, 0x00, 0x6D, 0x00, 0x70, 0x00, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xE5, 0x32, 0x00, 0x35, 0x00, 0x36, 0x00, 0x20, 0x00, 0x42, 0x00, 0x0F, 0x00, 0x0D, 0x65, 0x00, 0x6C, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x27, 0x00, 0x73, 0x00, 0x00, 0x00, 0x20, 0x00, 0x4C, 0x00, 0xE5, 0x35, 0x36, 0x42, 0x45, 0x4C, 0x7E, 0x31, 0x4D, 0x50, 0x33, 0x20, 0x00, 0x88, 0xCC, 0x5D, 0xF4, 0x3A, 0x88, 0x4B, 0x00, 0x00, 0x97, 0x5D, 0xD2, 0x3A, 0x92, 0x23, 0xC4, 0x27, 0x44, 0x00, 0xE5, 0x75, 0x00, 0x6C, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x62, 0x00, 0x0F, 0x00, 0x83, 0x79, 0x00, 0x2E, 0x00, 0x6F, 0x00, 0x67, 0x00, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xE5, 0x30, 0x00, 0x39, 0x00, 0x36, 0x00, 0x20, 0x00, 0x42, 0x00, 0x0F, 0x00, 0x83, 0x65, 0x00, 0x6C, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x27, 0x00, 0x73, 0x00, 0x00, 0x00, 0x20, 0x00, 0x4C, 0x00, 0xE5, 0x39, 0x36, 0x42, 0x45, 0x4C, 0x7E, 0x31, 0x4F, 0x47, 0x47, 0x20, 0x00, 0x7E, 0xCD, 0x5D, 0xF4, 0x3A, 0xF4, 0x3A, 0x00, 0x00, 0x3C, 0x65, 0xD2, 0x3A, 0xD5, 0x27, 0x54, 0x31, 0x19, 0x00, 0xE5, 0x75, 0x00, 0x6C, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x62, 0x00, 0x0F, 0x00, 0x1D, 0x79, 0x00, 0x2E, 0x00, 0x6F, 0x00, 0x67, 0x00, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xE5, 0x32, 0x00, 0x35, 0x00, 0x36, 0x00, 0x20, 0x00, 0x42, 0x00, 0x0F, 0x00, 0x1D, 0x65, 0x00, 0x6C, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x27, 0x00, 0x73, 0x00, 0x00, 0x00, 0x20, 0x00, 0x4C, 0x00, 0xE5, 0x35, 0x36, 0x42, 0x45, 0x4C, 0x7E, 0x31, 0x4F, 0x47, 0x47, 0x20, 0x00, 0xB5, 0xCD, 0x5D, 0xF4, 0x3A, 0xF4, 0x3A, 0x00, 0x00, 0x23, 0x6B, 0xD2, 0x3A, 0x69, 0x29, 0xB4, 0x28, 0x44, 0x00, 0xE5, 0x67, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0xC1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xE5, 0x32, 0x00, 0x35, 0x00, 0x36, 0x00, 0x20, 0x00, 0x44, 0x00, 0x0F, 0x00, 0xC1, 0x65, 0x00, 0x63, 0x00, 0x6F, 0x00, 0x64, 0x00, 0x65, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x6F, 0x00, 0x67, 0x00, };
static const uint8_t sector522[] = { 0xE5, 0x35, 0x36, 0x44, 0x45, 0x43, 0x7E, 0x31, 0x4F, 0x47, 0x47, 0x20, 0x00, 0x98, 0xCE, 0x5D, 0xF4, 0x3A, 0xF4, 0x3A, 0x00, 0x00, 0x01, 0x70, 0xD2, 0x3A, 0xAC, 0x2D, 0x80, 0xD2, 0x81, 0x00, 0xE5, 0x69, 0x00, 0x72, 0x00, 0x65, 0x00, 0x2E, 0x00, 0x6F, 0x00, 0x0F, 0x00, 0x1F, 0x67, 0x00, 0x67, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xE5, 0x32, 0x00, 0x35, 0x00, 0x36, 0x00, 0x20, 0x00, 0x45, 0x00, 0x0F, 0x00, 0x1F, 0x79, 0x00, 0x65, 0x00, 0x73, 0x00, 0x20, 0x00, 0x4F, 0x00, 0x6E, 0x00, 0x00, 0x00, 0x20, 0x00, 0x46, 0x00, 0xE5, 0x35, 0x36, 0x45, 0x59, 0x45, 0x7E, 0x31, 0x4F, 0x47, 0x47, 0x20, 0x00, 0x36, 0xD0, 0x5D, 0xF4, 0x3A, 0xF4, 0x3A, 0x00, 0x00, 0xDC, 0x6C, 0xD2, 0x3A, 0xCA, 0x35, 0x12, 0x8A, 0x94, 0x00, 0xE5, 0x63, 0x00, 0x61, 0x00, 0x6E, 0x00, 0x20, 0x00, 0x4D, 0x00, 0x0F, 0x00, 0xF1, 0x6F, 0x00, 0x75, 0x00, 0x74, 0x00, 0x68, 0x00, 0x2E, 0x00, 0x6F, 0x00, 0x00, 0x00, 0x67, 0x00, 0x67, 0x00, 0xE5, 0x73, 0x00, 0x20, 0x00, 0x42, 0x00, 0x69, 0x00, 0x72, 0x00, 0x0F, 0x00, 0xF1, 0x64, 0x00, 0x2C, 0x00, 0x20, 0x00, 0x41, 0x00, 0x6D, 0x00, 0x65, 0x00, 0x00, 0x00, 0x72, 0x00, 0x69, 0x00, 0xE5, 0x32, 0x00, 0x35, 0x00, 0x36, 0x00, 0x20, 0x00, 0x46, 0x00, 0x0F, 0x00, 0xF1, 0x6C, 0x00, 0x69, 0x00, 0x67, 0x00, 0x68, 0x00, 0x74, 0x00, 0x6C, 0x00, 0x00, 0x00, 0x65, 0x00, 0x73, 0x00, 0xE5, 0x35, 0x36, 0x46, 0x4C, 0x49, 0x7E, 0x31, 0x4F, 0x47, 0x47, 0x20, 0x00, 0x91, 0xD1, 0x5D, 0xF4, 0x3A, 0xF4, 0x3A, 0x00, 0x00, 0x78, 0x6B, 0xD2, 0x3A, 0x13, 0x3F, 0xCB, 0xA7, 0x75, 0x00, 0xE5, 0x2E, 0x00, 0x6F, 0x00, 0x67, 0x00, 0x67, 0x00, 0x00, 0x00, 0x0F, 0x00, 0xD5, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xE5, 0x32, 0x00, 0x35, 0x00, 0x36, 0x00, 0x20, 0x00, 0x46, 0x00, 0x0F, 0x00, 0xD5, 0x75, 0x00, 0x6C, 0x00, 0x6C, 0x00, 0x20, 0x00, 0x4D, 0x00, 0x6F, 0x00, 0x00, 0x00, 0x6F, 0x00, 0x6E, 0x00, 0xE5, 0x35, 0x36, 0x46, 0x55, 0x4C, 0x7E, 0x31, 0x4F, 0x47, 0x47, 0x20, 0x00, 0x1E, 0xD3, 0x5D, 0xF4, 0x3A, 0xF4, 0x3A, 0x00, 0x00, 0x1B, 0x6F, 0xD2, 0x3A, 0x6E, 0x46, 0xB2, 0x11, 0x71, 0x00, 0xE5, 0x65, 0x00, 0x20, 0x00, 0x57, 0x00, 0x61, 0x00, 0x79, 0x00, 0x0F, 0x00, 0xAB, 0x2E, 0x00, 0x6F, 0x00, 0x67, 0x00, 0x67, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xE5, 0x32, 0x00, 0x35, 0x00, 0x36, 0x00, 0x20, 0x00, 0x47, 0x00, 0x0F, 0x00, 0xAB, 0x6F, 0x00, 0x20, 0x00, 0x41, 0x00, 0x6C, 0x00, 0x6C, 0x00, 0x20, 0x00, 0x00, 0x00, 0x54, 0x00, 0x68, 0x00, 0xE5, 0x35, 0x36, 0x47, 0x4F, 0x41, 0x7E, 0x31, 0x4F, 0x47, 0x47, 0x20, 0x00, 0x5E, 0xD4, 0x5D, 0xF4, 0x3A, 0xF4, 0x3A, 0x00, 0x00, 0xD8, 0x6D, 0xD2, 0x3A, 0x80, 0x4D, 0xDF, 0xC3, 0x65, 0x00, 0xE5, 0x4D, 0x00, 0x79, 0x00, 0x73, 0x00, 0x65, 0x00, 0x6C, 0x00, 0x0F, 0x00, 0x4F, 0x66, 0x00, 0x2E, 0x00, 0x6F, 0x00, 0x67, 0x00, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xE5, 0x32, 0x00, 0x35, 0x00, 0x36, 0x00, 0x20, 0x00, 0x49, 0x00, 0x0F, 0x00, 0x4F, 0x20, 0x00, 0x43, 0x00, 0x61, 0x00, 0x75, 0x00, 0x67, 0x00, 0x68, 0x00, 0x00, 0x00, 0x74, 0x00, 0x20, 0x00, };
static const uint8_t sector523[] = { 0xE5, 0x35, 0x36, 0x49, 0x43, 0x41, 0x7E, 0x31, 0x4F, 0x47, 0x47, 0x20, 0x00, 0x64, 0xD5, 0x5D, 0xF4, 0x3A, 0xF4, 0x3A, 0x00, 0x00, 0x3B, 0x6D, 0xD2, 0x3A, 0xDD, 0x53, 0x5C, 0xDA, 0x73, 0x00, 0x44, 0x52, 0x56, 0x30, 0x38, 0x31, 0x20, 0x20, 0x20, 0x20, 0x20, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA6, 0x58, 0x88, 0x4B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x52, 0x45, 0x41, 0x44, 0x20, 0x20, 0x20, 0x20, 0x54, 0x58, 0x54, 0x20, 0x00, 0xB5, 0xA6, 0x58, 0x88, 0x4B, 0x93, 0x4B, 0x00, 0x00, 0xD0, 0x80, 0x87, 0x4B, 0x02, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
static const uint8_t sector32[] = { 0xEB, 0x3C, 0x90, 0x4D, 0x53, 0x44, 0x4F, 0x53, 0x35, 0x2E, 0x30, 0x00, 0x02, 0x08, 0x04, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0xF8, 0xF2, 0x00, 0x3F, 0x00, 0xFF, 0x00, 0x20, 0x00, 0x00, 0x00, 0xE0, 0x8F, 0x07, 0x00, 0x00, 0x00, 0x29, 0xB6, 0x0F, 0x1D, 0xB4, 0x4E, 0x4F, 0x20, 0x4E, 0x41, 0x4D, 0x45, 0x20, 0x20, 0x20, 0x20, 0x46, 0x41, 0x54, 0x31, 0x36, 0x20, 0x20, 0x20, 0x33, 0xC9, 0x8E, 0xD1, 0xBC, 0xF0, 0x7B, 0x8E, 0xD9, 0xB8, 0x00, 0x20, 0x8E, 0xC0, 0xFC, 0xBD, 0x00, 0x7C, 0x38, 0x4E, 0x24, 0x7D, 0x24, 0x8B, 0xC1, 0x99, 0xE8, 0x3C, 0x01, 0x72, 0x1C, 0x83, 0xEB, 0x3A, 0x66, 0xA1, 0x1C, 0x7C, 0x26, 0x66, 0x3B, 0x07, 0x26, 0x8A, 0x57, 0xFC, 0x75, 0x06, 0x80, 0xCA, 0x02, 0x88, 0x56, 0x02, 0x80, 0xC3, 0x10, 0x73, 0xEB, 0x33, 0xC9, 0x8A, 0x46, 0x10, 0x98, 0xF7, 0x66, 0x16, 0x03, 0x46, 0x1C, 0x13, 0x56, 0x1E, 0x03, 0x46, 0x0E, 0x13, 0xD1, 0x8B, 0x76, 0x11, 0x60, 0x89, 0x46, 0xFC, 0x89, 0x56, 0xFE, 0xB8, 0x20, 0x00, 0xF7, 0xE6, 0x8B, 0x5E, 0x0B, 0x03, 0xC3, 0x48, 0xF7, 0xF3, 0x01, 0x46, 0xFC, 0x11, 0x4E, 0xFE, 0x61, 0xBF, 0x00, 0x00, 0xE8, 0xE6, 0x00, 0x72, 0x39, 0x26, 0x38, 0x2D, 0x74, 0x17, 0x60, 0xB1, 0x0B, 0xBE, 0xA1, 0x7D, 0xF3, 0xA6, 0x61, 0x74, 0x32, 0x4E, 0x74, 0x09, 0x83, 0xC7, 0x20, 0x3B, 0xFB, 0x72, 0xE6, 0xEB, 0xDC, 0xA0, 0xFB, 0x7D, 0xB4, 0x7D, 0x8B, 0xF0, 0xAC, 0x98, 0x40, 0x74, 0x0C, 0x48, 0x74, 0x13, 0xB4, 0x0E, 0xBB, 0x07, 0x00, 0xCD, 0x10, 0xEB, 0xEF, 0xA0, 0xFD, 0x7D, 0xEB, 0xE6, 0xA0, 0xFC, 0x7D, 0xEB, 0xE1, 0xCD, 0x16, 0xCD, 0x19, 0x26, 0x8B, 0x55, 0x1A, 0x52, 0xB0, 0x01, 0xBB, 0x00, 0x00, 0xE8, 0x3B, 0x00, 0x72, 0xE8, 0x5B, 0x8A, 0x56, 0x24, 0xBE, 0x0B, 0x7C, 0x8B, 0xFC, 0xC7, 0x46, 0xF0, 0x3D, 0x7D, 0xC7, 0x46, 0xF4, 0x29, 0x7D, 0x8C, 0xD9, 0x89, 0x4E, 0xF2, 0x89, 0x4E, 0xF6, 0xC6, 0x06, 0x96, 0x7D, 0xCB, 0xEA, 0x03, 0x00, 0x00, 0x20, 0x0F, 0xB6, 0xC8, 0x66, 0x8B, 0x46, 0xF8, 0x66, 0x03, 0x46, 0x1C, 0x66, 0x8B, 0xD0, 0x66, 0xC1, 0xEA, 0x10, 0xEB, 0x5E, 0x0F, 0xB6, 0xC8, 0x4A, 0x4A, 0x8A, 0x46, 0x0D, 0x32, 0xE4, 0xF7, 0xE2, 0x03, 0x46, 0xFC, 0x13, 0x56, 0xFE, 0xEB, 0x4A, 0x52, 0x50, 0x06, 0x53, 0x6A, 0x01, 0x6A, 0x10, 0x91, 0x8B, 0x46, 0x18, 0x96, 0x92, 0x33, 0xD2, 0xF7, 0xF6, 0x91, 0xF7, 0xF6, 0x42, 0x87, 0xCA, 0xF7, 0x76, 0x1A, 0x8A, 0xF2, 0x8A, 0xE8, 0xC0, 0xCC, 0x02, 0x0A, 0xCC, 0xB8, 0x01, 0x02, 0x80, 0x7E, 0x02, 0x0E, 0x75, 0x04, 0xB4, 0x42, 0x8B, 0xF4, 0x8A, 0x56, 0x24, 0xCD, 0x13, 0x61, 0x61, 0x72, 0x0B, 0x40, 0x75, 0x01, 0x42, 0x03, 0x5E, 0x0B, 0x49, 0x75, 0x06, 0xF8, 0xC3, 0x41, 0xBB, 0x00, 0x00, 0x60, 0x66, 0x6A, 0x00, 0xEB, 0xB0, 0x4E, 0x54, 0x4C, 0x44, 0x52, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x0D, 0x0A, 0x52, 0x65, 0x6D, 0x6F, 0x76, 0x65, 0x20, 0x64, 0x69, 0x73, 0x6B, 0x73, 0x20, 0x6F, 0x72, 0x20, 0x6F, 0x74, 0x68, 0x65, 0x72, 0x20, 0x6D, 0x65, 0x64, 0x69, 0x61, 0x2E, 0xFF, 0x0D, 0x0A, 0x44, 0x69, 0x73, 0x6B, 0x20, 0x65, 0x72, 0x72, 0x6F, 0x72, 0xFF, 0x0D, 0x0A, 0x50, 0x72, 0x65, 0x73, 0x73, 0x20, 0x61, 0x6E, 0x79, 0x20, 0x6B, 0x65, 0x79, 0x20, 0x74, 0x6F, 0x20, 0x72, 0x65, 0x73, 0x74, 0x61, 0x72, 0x74, 0x0D, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAC, 0xCB, 0xD8, 0x55, 0xAA, };
static const uint8_t sector36[] = { 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
static const uint8_t sector552[] = { 0x61, 0x73, 0x64, 0x66, 0x6A, 0x6B, 0x6C, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
static const uint8_t sector278[] = { 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };

static struct EMULATED_DISK disk = {0, NULL};

void DRV081_writeSector(	
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

void DRV081_readSector(	
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

void DRV081_initialize(void)
{    
    EmulatedDiskCreate(&disk, SECTOR_SIZE);
    
    DRV081_writeSector((const uint8_t*)sector0, 0, 1);
    DRV081_writeSector((const uint8_t*)sector520, 520, 1);
    DRV081_writeSector((const uint8_t*)sector521, 521, 1);
    DRV081_writeSector((const uint8_t*)sector522, 522, 1);
    DRV081_writeSector((const uint8_t*)sector523, 523, 1);
    DRV081_writeSector((const uint8_t*)sector32, 32, 1);
    DRV081_writeSector((const uint8_t*)sector36, 36, 1);
    DRV081_writeSector((const uint8_t*)sector552, 552, 1);
    DRV081_writeSector((const uint8_t*)sector278, 278, 1);

}

void DRV081_print(void)
{
    EmulatedDiskPrint(&disk);
}

static const char id[] = "DRV081";
const char* DRV081_id(void)
{
    return id;
}

struct EMULATED_DRIVE DRV081 = { &DRV081_initialize, &DRV081_print, &DRV081_id};

