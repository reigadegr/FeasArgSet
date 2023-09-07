#!/bin/sh
rm -rf $(dirname "$0")/*.bak
#通用推送模板
/data/data/com.termux/files/usr/bin/git gc --prune=all

/data/data/com.termux/files/usr/bin/git add .

/data/data/com.termux/files/usr/bin/git commit -m "$1"

/data/data/com.termux/files/usr/bin/git push -f origin main
