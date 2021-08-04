#!/bin/bash

touch foo.h
gcc-10 -E -dM foo.h > foo.h.gcc
gcc -E -dM foo.h > foo.h.clang
sort foo.h.gcc > foo.h.gcc.s
sort foo.h.clang > foo.h.clang.s
rm foo.h.gcc foo.h.clang foo.h
diff foo.h.gcc.s foo.h.clang.s