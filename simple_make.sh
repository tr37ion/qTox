#! /bin/bash

if which apt-get; then
    sudo apt-get install build-essential qt5-qmake qt5-default libopenal-dev libopencv-dev \
                         libtool autotools-dev automake checkinstall check libopus-dev libvpx-dev qttools5-dev-tools qtchooser libxss-dev
elif which pacman; then
    sudo pacman -S --needed base-devel qt5 opencv openal opus libvpx libxss
elif which yum; then
    yum groupinstall "Development Tools"
    yum install qt-devel qt-doc qt-creator opencv-devel openal-soft-devel libtool autoconf automake check check-devel libXScrnSaver-devel
else
    echo "Unknown package manager, attempting to compile anyways"
fi

./bootstrap.sh
qmake
make
