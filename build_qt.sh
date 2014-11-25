#!/bin/sh -e

SCRIPT=$(readlink -f "$0")
BASE_DIR="$(dirname "$SCRIPT")/qt"
MOUNT_DIR="$BASE_DIR/rpi/rasp-pi-rootfs"
ROOTFS_DIR="$BASE_DIR/rpi/rootfs"

echo "Compiling Qt in $BASE_DIR"

#-------------------------------------------------------------------------------
# Mount img file

if [ ! -d "$MOUNT_DIR/etc" ]; then
  mkdir -p $MOUNT_DIR
  mkdir -p $ROOTFS_DIR

  echo "Please enter the path to your img file:"
  read IMG_FILE

  if [ ! -f "$IMG_FILE" ]; then
    echo "$IMG_FILE does not exists!"
    exit 1
  fi

  if [ "$(id -u)" != "0" ]; then
    sudo mount -o loop,offset=62914560 $IMG_FILE $MOUNT_DIR
  else
    mount -o loop,offset=62914560 $IMG_FILE $MOUNT_DIR
  fi
fi

#-------------------------------------------------------------------------------
# Install required packages

REQUIRED="build-essential git gcc-multilib ctorrent unzip libglu1-mesa-dev wget"
for pkg in $REQUIRED; do
  if ! dpkg --get-selections | grep -q "^$pkg[[:space:]]*install$" >/dev/null; then
    if [ "$(id -u)" != "0" ]; then
      sudo apt-get -qq install $pkg
    else
      apt-get -qq install $pkg
    fi
  fi
done

#-------------------------------------------------------------------------------
# Download tools

cd $BASE_DIR

# gcc-4.7-linaro-rpi-gnueabihf
if [ ! -d "$BASE_DIR/gcc-4.7-linaro-rpi-gnueabihf" ]; then
  if [ ! -f "$BASE_DIR/gcc-4.7-linaro-rpi-gnueabihf.tbz" ]; then
    echo "You have to download gcc-4.7-linaro-rpi-gnueabihf.tbz and put it in $BASE_DIR!"
    exit 1
  fi
  tar -xf gcc-4.7-linaro-rpi-gnueabihf.tbz
fi

# cross-compile-tools
if [ ! -d "$BASE_DIR/cross-compile-tools/.git" ]; then
  git clone git://gitorious.org/cross-compile-tools/cross-compile-tools.git
fi
cd "$BASE_DIR/cross-compile-tools"
git pull origin

# Qt
if [ ! -d "$BASE_DIR/qt-everywhere-opensource-src-5.3.2" ]; then
  cd $BASE_DIR
  wget http://download.qt-project.org/official_releases/qt/5.3/5.3.2/single/qt-everywhere-opensource-src-5.3.2.tar.gz
  tar -xf qt-everywhere-opensource-src-5.3.2.tar.gz
  
  # Patch Qt
  cp 0001-Adjusts-to-build-qtbase-with-support-to-openvg.patch qt-everywhere-opensource-src-5.3.2/qtbase
  cd $BASE_DIR/qt-everywhere-opensource-src-5.3.2/qtbase
  patch -p1 < 0001-Adjusts-to-build-qtbase-with-support-to-openvg.patch
fi

#-------------------------------------------------------------------------------

#Dump rootfs from raspberry image
if [ ! -d "$ROOTFS_DIR/usr" ]; then
  cd $MOUNT_DIR
  tar --preserve-permissions -c usr/include usr/lib usr/share lib opt/vc | tar -x -C $ROOTFS_DIR
  $BASE_DIR/cross-compile-tools/fixQualifiedLibraryPaths $ROOTFS_DIR $BASE_DIR/gcc-4.7-linaro-rpi-gnueabihf/bin/arm-linux-gnueabihf-gcc
  
  cd $ROOTFS_DIR
  ln -s arm-linux-gnueabihf/jconfig.h usr/include/
  ln -s ../../../lib/arm-linux-gnueabihf/liblzma.so.5.0.0 usr/lib/arm-linux-gnueabihf/liblzma.so.5
  ln -s ../../../lib/arm-linux-gnueabihf/libexpat.so.1.6.0 usr/lib/arm-linux-gnueabihf/libexpat.so.1
  ln -s ../../../lib/arm-linux-gnueabihf/libz.so.1.2.7 usr/lib/arm-linux-gnueabihf/libz.so.1
fi

#-------------------------------------------------------------------------------
# Compile Qt

cd $BASE_DIR/qt-everywhere-opensource-src-5.3.2/qtbase

if [ ! -f "$BASE_DIR/qt-everywhere-opensource-src-5.3.2/.CONFIGURED" ]; then
  ./configure -opengl es2 -device linux-rasp-pi-g++ -device-option CROSS_COMPILE=$BASE_DIR/gcc-4.7-linaro-rpi-gnueabihf/bin/arm-linux-gnueabihf- -sysroot $ROOTFS_DIR -opensource -confirm-license -optimized-qmake -release -prefix /usr/local/qt5pi -no-pch -nomake tests -nomake examples -plugin-sql-sqlite -reduce-exports
  touch $BASE_DIR/qt-everywhere-opensource-src-5.3.2/.CONFIGURED
fi

if [ ! -f "$BASE_DIR/qt-everywhere-opensource-src-5.3.2/.COMPILED" ]; then
  CORES=`grep -c '^processor' /proc/cpuinfo`
  CORES=`echo $CORES | grep '^[[:digit:]]*$'`
  make -j $CORES
  touch $BASE_DIR/qt-everywhere-opensource-src-5.3.2/.COMPILED
else 
  echo "Already compiled"
fi
  
