#!/bin/sh
killall -15 FeasArgSet
chmod +x $(pwd)/FeasArgSet

if [ -f "/data/adb/modules/FeasArgSetHelper/config/package.conf" ]; then
    $(pwd)/FeasArgSet \
    /data/adb/modules/FeasArgSetHelper/config/package.conf \
    $(pwd)/config/PandoraFeasPath.conf
else
    $(pwd)/FeasArgSet \
    $(pwd)/config/package.conf \
    $(pwd)/config/PandoraFeasPath.conf
fi
