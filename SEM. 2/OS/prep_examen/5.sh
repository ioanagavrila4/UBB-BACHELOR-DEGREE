#!/bin/bash
while read source dest; do
    cp "$source" "$dest"
done<a.txt
