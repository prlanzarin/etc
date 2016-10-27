#!/bin/bash

set -xe

sudo apt-get update
sudo apt-get dist-upgrade

sudo apt-get install software-properties-common wget
sudo add-apt-repository ppa:libreoffice/libreoffice-4-4

sudo add-apt-repository -y ppa:ondrej/php

wget http://ubuntu.bigbluebutton.org/bigbluebutton.asc -O- | sudo apt-key add -

echo "deb http://ubuntu.bigbluebutton.org/trusty-1-0/ bigbluebutton-trusty main" | sudo tee /etc/apt/sources.list.d/bigbluebutton.list

sudo apt-get update

sudo sh install-ffmpeg-openh264.sh

sudo apt-get install bigbluebutton

sudo apt-get install bbb-demo

sudo apt-get install bbb-check

sudo bbb-conf --enablewebrtc

sudo bbb-conf --clean
sudo bbb-conf --check
