#script based on fcecagno's script
#!/bin/bash

set -xe

# https://github.com/cisco/openh264/issues/1529

sudo apt-get update && sudo apt-get install -y yasm nasm wget git-core build-essential checkinstall yasm texi2html libvorbis-dev libx11-dev libvpx-dev libxfixes-dev zlib1g-dev pkg-config libxext-dev libv4l-dev netcat librtmp-dev libx264-dev libmp3lame-dev libopus-dev libtheora-dev libwebp-dev libspeex-dev libfreetype6-dev

FFMPEG_VERSION=2.8.2

if [ ! -d "/usr/local/src/ffmpeg-${FFMPEG_VERSION}" ]; then
        echo "Download and unpacking ffmpeg..."
        cd /usr/local/src
        sudo wget "http://ffmpeg.org/releases/ffmpeg-${FFMPEG_VERSION}.tar.bz2" 
        sudo tar -xjf "ffmpeg-${FFMPEG_VERSION}.tar.bz2" 
fi

OPENH264_VERSION=1.4.0
#the following code will compile libopenh264 from the source.
#If you are installing ffmpeg from an existent debian package (compiled with libopenh264),
#you don't need to do this , simply download the binary directly from
#the cisco's page and just link it to the system's lib folder:
#       wget http://ciscobinary.openh264.org/libopenh264-${OPENH264_VERSION}-linux64.so.bz2
#       bunzip2 libopenh264-${OPENH264_VERSION}-linux64.so.bz2
#       take a look at install-libopenh264-bin gist
#Remember that openh264's bynary-only installation doesn't work in the context of this script, once 
#we are compiling ffmpeg with libopenh264 and source files are needed for that.

if [ ! -d /usr/local/src/openh264-${OPENH264_VERSION} ]; then
        echo "Download and unpacking openh264..."
        cd /usr/local/src
        sudo wget https://github.com/cisco/openh264/archive/v${OPENH264_VERSION}.tar.gz
        sudo tar -xvf v${OPENH264_VERSION}.tar.gz
        cd /usr/local/src/openh264-${OPENH264_VERSION}
        echo "Compiling openh264"
        sudo make
        echo "Installing openh264"
        sudo make install
        echo "Making symbolic link"
        #check ldd ("ldd ffmpeg") if couldn't find libopenh264.so when running ffmpeg
        sudo ln -s -f /usr/local/lib/libopenh264.so.0 /usr/lib/x86_64-linux-gnu/
fi

cd /usr/local/src/"ffmpeg-${FFMPEG_VERSION}" 
#add --enable-ffplay if you want ffplay (requires libsdl-dev package)
sudo ./configure --enable-x11grab --enable-gpl --enable-version3 --enable-postproc --enable-libvorbis --enable-libvpx --enable-librtmp --enable-libx264 --enable-libtheora --enable-libvpx --enable-libwebp --enable-lsp --enable-libmp3lame --enable-libopus --enable-libspeex --enable-avresample --enable-libopenh264 --enable-libfreetype
sudo make
echo "Installing ffmpeg..."
sudo checkinstall --pkgname=ffmpeg --pkgversion="5:${FFMPEG_VERSION}" --backup=no --deldoc=yes --default
