#include "bm.h"
#include "crc.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
  FILE* in = fopen(argv[1], "r");
  fseek(in, 0L, SEEK_END);
  int sz = ftell(in);
  fseek(in, 0L, SEEK_SET);
  char data[sz];
  fread(data, 1, sz, in);

  struct bootloader_control* bc = (struct bootloader_control*) (data + 2048);
  printf("%s\n", bc->slot_suffix);
  printf("%d\n", bc->magic);
  printf("%d\n", bc->version);
  printf("%d\n", bc->nb_slot);
  printf("%d\n", bc->recovery_tries_remaining);
  for (int i=0; i<bc->nb_slot; i++) {
    struct slot_metadata sm = bc->slot_info[i];
    printf("=======\n");
    printf("%d\n", sm.priority);
    printf("%d\n", sm.tries_remaining);
    printf("%d\n", sm.successful_boot);
    printf("%d\n", sm.verity_corrupted);
  }
  printf("=======\n");
  printf("%d\n", bc->crc32_le);
  printf("%d\n", ab_control_compute_crc(bc));
}
