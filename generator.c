#include "bm.h"
#include "crc.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SIZE 524288
#define OFF 2048

int main(int argc, char** argv) {
  char data[SIZE];
  memset(data, 0, SIZE);

  struct bootloader_control* bc = (struct bootloader_control*) (data + OFF);
  char slot = argv[1][0];
  int active_index = slot - 'a';
  int inactive_index = 1 - active_index;

  bc->slot_suffix[0] = slot;
  bc->magic = BOOT_CTRL_MAGIC;
  bc->version = BOOT_CTRL_VERSION;
  bc->nb_slot = 2;
  bc->recovery_tries_remaining = 0;
  bc->slot_info[active_index].priority = 15;
  bc->slot_info[active_index].tries_remaining = 7;
  bc->slot_info[active_index].successful_boot = 1;
  bc->slot_info[active_index].verity_corrupted = 0;
  bc->slot_info[inactive_index].priority = 15;
  bc->slot_info[inactive_index].tries_remaining = 0;
  bc->slot_info[inactive_index].successful_boot = 0;
  bc->slot_info[inactive_index].verity_corrupted = 0;
  bc->crc32_le = ab_control_compute_crc(bc);

  FILE* fp = fopen("out.img", "w+");
  fwrite(data, 1, SIZE, fp);
  fclose(fp);
}
