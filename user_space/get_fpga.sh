#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "You must enter the \$OPENWIFI_DIR (the openwifi root directory) as argument"
    exit 1
fi
OPENWIFI_DIR=$1


if [ -f "$OPENWIFI_DIR/LICENSE" ]; then
    echo "\$OPENWIFI_DIR is found!"
else
    echo "\$OPENWIFI_DIR is not correct. Please check!"
    exit 1
fi

home_dir=$(pwd)

set -ex

cd $OPENWIFI_DIR/
git submodule init openwifi-hw
git submodule update openwifi-hw
cd openwifi-hw
git checkout master
git pull

cd $home_dir
