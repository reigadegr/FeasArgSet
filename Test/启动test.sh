#!/bin/sh
killall -15 FeasArgSet
chmod +x $(pwd)/FeasArgSet
$(pwd)/FeasArgSet \
$(pwd)/config/package.conf \
$(pwd)/config/path.conf