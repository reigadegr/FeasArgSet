SKIPUNZIP=0
MODDIR=${0%/*}
cat $MODDIR/ReadMe.md |
    while read row; do
        echo $row
        sleep 0.15
    done