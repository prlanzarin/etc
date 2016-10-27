#!/bin/bash

set -xe

sudo service bbb-freeswitch stop

#sudo add-apt-repository -y ppa:ondrej/php

# git clean -f -x
#sudo apt-get update
#sudo apt-get install -y git-core build-essential autoconf automake libtool libncurses5 libncurses5-dev make libjpeg-dev pkg-config  unixodbc unixodbc-dev zlib1g-dev sqlite3 libsqlite3-dev
#sudo apt-get install -y libcurl4-gnutls-dev libpcre3-dev libspeexdsp-dev libedit-dev
#sudo apt-get install -y libsqlite3-dev libcurl4-openssl-dev libldns-dev liblua5.1-0-dev
#sudo apt-get install -y libssl-dev

#sudo apt-get install -y cmake libvlc-dev libpng-dev libspeex-dev libopus-dev
#sudo apt-get install -y lua5.1 lua5.1-dev libsndfile-dev yasm libswscale-dev

# cd ~/dev
# if [ ! -d libyuv ]; then
# 	git clone https://freeswitch.org/stash/scm/sd/libyuv.git
# fi
# cd libyuv
# if [ -d build ]; then
# 	rm -R build
# fi
# mkdir build
# cd build
# cmake ..
# make
# sudo make install

# cd ~/dev
# if [ ! -d libvpx ]; then
# 	git clone https://freeswitch.org/stash/scm/sd/libvpx.git
# fi
# cd libvpx
# ./configure --enable-shared
# make
# sudo make install

# cd ~/dev
# if [ ! -d libav ]; then
# 	git clone https://freeswitch.org/stash/scm/sd/libav.git
# fi
# cd libav
# ./configure --enable-shared
# make
# sudo make install



cd ~/dev
if [ ! -d freeswitch ]; then
	git clone https://prlanzarin@freeswitch.org/stash/scm/~prlanzarin/freeswitch.git
fi	
cd freeswitch
git fetch origin
git fetch --tags
git checkout v1.6.12
find -name .gitignore -exec rm {} \;
git clean -fd
git checkout -- .
cp ~/dev/scripts/modules.conf .

./bootstrap.sh -j
./configure --prefix=/opt/freeswitch-dev
sudo make
sudo make all install cd-sounds-install cd-moh-install

# sudo rm -rf /opt/freeswitch
#sudo mv /opt/freeswitch /opt/freeswitch-bbb
sudo rm -rf /opt/freeswitch-dev/etc/freeswitch/conf
sudo cp -r /opt/freeswitch-bbb/conf/ /opt/freeswitch-dev/etc/freeswitch/
sudo ln -s -f /opt/freeswitch-dev/ /opt/freeswitch
sudo chown freeswitch:daemon /opt/freeswitch-dev/ -R


