# !/system/bin/sh
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
killall -15 FeasArgSet
nohup $(dirname "$0")/FeasArgSet $(dirname "$0")/config/package.conf $(dirname "$0")/config/path.conf >/dev/null 2>&1 &