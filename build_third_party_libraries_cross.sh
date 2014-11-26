#!/bin/sh -e

CORES=`grep -c '^processor' /proc/cpuinfo`
CORES=`echo $CORES | grep '^[[:digit:]]*$'`

SCRIPT=$(readlink -f "$0")
BASE_DIR="$(dirname "$SCRIPT")/third-party"

COMPILER="$BASE_DIR/../qt/gcc-4.7-linaro-rpi-gnueabihf/bin"

#------------------------------------------------------------------------------
# google-breakpad

if [ ! -f "$BASE_DIR/google-breakpad-read-only-rpi/.COMPILED" ]; then
  if [ ! -d "$BASE_DIR/google-breakpad-read-only-rpi/.svn" ]; then
    svn checkout http://google-breakpad.googlecode.com/svn/trunk/ "$BASE_DIR/google-breakpad-read-only-rpi"
    cd "$BASE_DIR/google-breakpad-read-only-rpi"
  else
    cd "$BASE_DIR/google-breakpad-read-only-rpi"
    svn update
  fi
  
  if [ ! -f "$BASE_DIR/../qt/gcc-4.7-linaro-rpi-gnueabihf/bin/arm-linux-gnueabihf-g++" ]; then
    echo "ERROR: compiler not found."
    exit 1
  fi
  
  ./configure --host=rpi --disable-processor \
    --disable-tools CXX=$COMPILER/arm-linux-gnueabihf-g++
  make -j $CORES
  touch .COMPILED
fi

#------------------------------------------------------------------------------
# wiringPi

if [ ! -f "$BASE_DIR/wiringPi/.COMPILED" ]; then
  if [ ! -d "$BASE_DIR/wiringPi/.git" ]; then
    cd $BASE_DIR
    git clone git://git.drogon.net/wiringPi
  fi
  
  cd "$BASE_DIR/wiringPi"
  git pull origin
  cd "$BASE_DIR/wiringPi/wiringPi"
  
  sed -i '/gcc/c\$COMPILER/arm-linux-gnueabihf-g++' Makefile
  make static -j $CORES
  touch "$BASE_DIR/wiringPi/.COMPILED"
fi