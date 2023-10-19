#!/bin/sh
rm $(pwd)/*.txt $(pwd)/*.bak 2>/dev/null

for i in $(pwd)/*.ko; do
    modinfo $i | grep "parmtype" > $(basename $i)_dump.txt
done
