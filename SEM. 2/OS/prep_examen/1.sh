#!/bin/bash
if [[ -e . && ( -r . || -w . || -x . ) ]]; then

echo "Exist"
   else echo "not"
fi
