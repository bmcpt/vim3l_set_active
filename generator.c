#include "bm.h"
#include "crc.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
  FILE* in = fopen("misc.img", "r");
  fseek(in, 0L, SEEK_END);
  int sz = ftell(in);
  fseek(in, 0L, SEEK_SET);
  char data[sz];
  fread(data, 1, sz, in);
  fclose(in);

  char zeros[65536];
  memset(zeros, 0, 65536);

  struct bootloader_control* bc = (struct bootloader_control*) (data + 2048);

  bc->slot_suffix[0] = 'a';
  bc->slot_info[0].priority = 15;
  bc->slot_info[0].tries_remaining = 7;
  bc->slot_info[0].successful_boot = 1;
  bc->slot_info[0].verity_corrupted = 0;
  bc->slot_info[1].priority = 15;
  bc->slot_info[1].tries_remaining = 0;
  bc->slot_info[1].successful_boot = 0;
  bc->slot_info[1].verity_corrupted = 0;
  bc->crc32_le = ab_control_compute_crc(bc);

  FILE* fp = fopen("out.img", "w+");
  fwrite(data, 1, sz, fp);
  fclose(fp);
}
