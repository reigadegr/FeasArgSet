SKIPUNZIP=0
MODDIR=${0%/*}

if [ -d /data/adb/modules/FeasArgSetHelper ]; then
    cp -rf /data/adb/modules/FeasArgSetHelper/config/* $MODPATH/config
    cat $MODPATH/Update.md |
        while read row; do
            echo "$row"
            sleep 0.1
        done
else
    cat $MODPATH/README.md |
        while read row; do
            echo "$row"
            sleep 0.1
        done
        
        cat $MODPATH/Update.md |
        while read row; do
            echo "$row"
            sleep 0.1
        done
fi

rm $MODPATH/Update.md