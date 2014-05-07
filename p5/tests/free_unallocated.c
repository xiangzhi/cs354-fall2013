/* free a pointer which does not point to beginning of a block */
#include <assert.h>
#include <stdlib.h>
#include "mem.h"

int main() {
   assert(Mem_Init(4096) == 0);
   int* ptr = (int*) Mem_Alloc(2 * sizeof(int));
   assert(ptr != NULL);
   ptr = ptr + 1;
   assert(Mem_Free(ptr) == -1);
   exit(0);
}
