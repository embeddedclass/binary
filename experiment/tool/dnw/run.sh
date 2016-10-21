#!/bin/sh

sudo apt-get install libusb-dev
gcc dnw_new.c -o dnw -lusb
sudo cp -a ./dnw /usr/bin
