/*free a NULL pointer */
#include <assert.h>
#include <stdlib.h>
#include "mem.h"

int main() {
   assert(Mem_Init(4096) == 0);
   void* ptr = Mem_Alloc(8);
   assert(ptr != NULL);
   ptr = NULL;
   assert(Mem_Free(ptr) == -1);
   exit(0);
}
