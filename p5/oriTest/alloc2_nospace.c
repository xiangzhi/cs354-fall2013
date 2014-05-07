/* second allocation is too big to fit */
#include <assert.h>
#include <stdlib.h>
#include "mem.h"

int main() {
   assert(Mem_Init(4096) == 0);
   assert(Mem_Alloc(2048) != NULL);
   assert(Mem_Alloc(2047) == NULL);

   exit(0);
}
