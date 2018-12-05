#!/bin/bash

# Install ---------------------------------------------------------------------#
# development tools
sudo apt install build-essential libtool autoconf

# gcc-arm-none-eabi
sudo add-apt-repository ppa:team-gcc-arm-embedded/ppa
sudo apt update
sudo apt remove gcc-arm-embedded
sudo apt install gcc-arm-embedded -y

# cmake
sudo apt install cmake -y
