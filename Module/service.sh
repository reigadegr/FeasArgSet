#!/bin/sh
MODDIR=${0%/*}
FileName="FeasArgSet"
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

chmod +x $MODDIR/$FileName

if [ -f $MODDIR/$FileName.log ]; then
    mv -f $MODDIR/$FileName.log $MODDIR/$FileName.log.bak
else
    touch  $MODDIR/$FileName.log
fi

killall -15 $FileName
#ELF
nohup $MODDIR/$FileName \
$MODDIR/config/package.conf \
$MODDIR/config/path.conf \
>$MODDIR/$FileName.log 2>&1 &