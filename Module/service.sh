#!/bin/sh
MODDIR=${0%/*}

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

chmod +x $MODDIR/FeasArgSet
true > $MODDIR/FeasArgSet.log
killall -15 FeasArgSet
nohup $MODDIR/FeasArgSet $MODDIR/config/package.conf $MODDIR/config/path.conf >$MODDIR/FeasArgSet.log 2>&1 &