#!/bin/sh
termuxUid="$(dumpsys package com.termux | grep userId | awk 'NR==1{print $1}' | cut -d '=' -f2)"
nohup chown -R $termuxUid:$termuxUid $(pwd) >/dev/null 2>&1 &
chmod -R 0700 $(pwd)
