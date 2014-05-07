#!/bin/bash

export LD_LIBRARY_PATH=..

make

./alloc
./alloc2
./alloc3
./align
./align2
./align3
./free2
./free3
./alloc_nospace
./alloc2_nospace
./free_simple
./free_null
./free_unallocated
./firstfit
./coalesce1
./coalesce2
./coalesce3
./coalesce4
./coalesce5
./coalesce6
./writeable

echo Success