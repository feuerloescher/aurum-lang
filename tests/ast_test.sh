#!/bin/sh -x

./ast_test.bin
[ "$?" -eq "247" ]
