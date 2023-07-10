SKIPUNZIP=0
MODDIR=${0%/*}
cat $MODPATH/README.md |
    while read row; do
        echo $row
        sleep 0.15
    done
    
if [ -d /data/adb/modules/FeasArgSetHelper ]; then
    cp -rf /data/adb/modules/FeasArgSetHelper/config/* $MODPATH/config
fi

