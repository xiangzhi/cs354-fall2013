/* see what the start is... */
#include <assert.h>
#include <stdlib.h>
#include "mem.h"

int main() {
   assert(Mem_Init(4096) == 0);
   Mem_Dump();
   exit(0);
}
