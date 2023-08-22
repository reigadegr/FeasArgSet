#!/bin/sh
wait_until_login() {
    # in case of /data encryption is disabled
    while [ "$(getprop sys.boot_completed)" != "1" ]; do
        sleep 1
    done

    # in case of the user unlocked the screen
    while [ ! -d "/sdcard/Android" ]; do
        sleep 1
    done
}
wait_until_login

MODDIR=${0%/*}
FileName="FeasArgSet"

chown 0:0 $MODDIR/$FileName
chmod +x $MODDIR/$FileName

if [ -f $MODDIR/$FileName.log ]; then
    mv -f $MODDIR/$FileName.log $MODDIR/$FileName.log.bak
fi
touch $MODDIR/$FileName.log

killall -15 $FileName
#ELF
nohup $MODDIR/$FileName \
$MODDIR/config/package.conf \
$MODDIR/config/path.conf \
>$MODDIR/$FileName.log 2>&1 &
