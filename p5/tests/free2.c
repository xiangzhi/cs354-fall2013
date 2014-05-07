/* a few allocations in multiples of 4 bytes followed by frees */
#include <assert.h>
#include <stdlib.h>
#include "mem.h"

int main() {
   assert(Mem_Init(4096) == 0);
   void* ptr[4];

   ptr[0] = Mem_Alloc(4);
   Mem_Dump();
   ptr[1] = Mem_Alloc(8);
   Mem_Dump();
   printf("\nBEFORE\n");
   assert(Mem_Free(ptr[0]) == 0);
   Mem_Dump();
   assert(Mem_Free(ptr[1]) == 0);
   Mem_Dump();
   printf("\nPASSSSSS\n");
   ptr[2] = Mem_Alloc(16);
   ptr[3] = Mem_Alloc(4);
   Mem_Dump();
   printf("\nBEFORE\n");
   assert(Mem_Free(ptr[2]) == 0);
   assert(Mem_Free(ptr[3]) == 0);
   Mem_Dump();
   exit(0);
}
