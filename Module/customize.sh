SKIPUNZIP=0
MODDIR=${0%/*}
cat $MODDIR/README.md |
    while read row; do
        echo $row
        sleep 0.15
    done