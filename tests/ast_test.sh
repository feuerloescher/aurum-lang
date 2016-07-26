#!/bin/sh -x

./ast_test.bin a a a a
[ "$?" -eq "121" ]
