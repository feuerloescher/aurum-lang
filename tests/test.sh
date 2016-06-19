#!/bin/sh -x

test_name="$1"

set -e
"./${test_name}" &> "${test_name}.out"
if [ -f "../../tests/${test_name}.out" ]; then
    diff "${test_name}.out" "../../tests/${test_name}.out"
fi
if [ -f "../../tests/${test_name}.bc" ]; then
    diff "${test_name}.bc" "../../tests/${test_name}.bc"
fi
if [ -f "${test_name}.bc" ]; then
    clang "${test_name}.bc" -o "${test_name}.bin"
fi
if [ -x "../../tests/${test_name}.sh" ]; then
    "../../tests/${test_name}.sh"
fi
