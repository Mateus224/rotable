#!/bin/bash -e

CONFCLEAN=0

#-------------------------------------------------------------------------------
#Parse arguments

while test $# -gt 0; do
  case $1 in
    # Normal option processing
    -h | --help)
      # usage and help
      echo "Usage:"
      echo " ./$0.sh [options]"
      echo "options:"
      echo " --qt Specify Qt version"
      echo " --target Specify target directory for compiled sources"
      echo " --img Path to raspbian image file"
      echo " --confclean Reconfigure qt"
      echo " -h, --help Help and usage info"
      exit
      ;;
    --qt)
      shift
      QT5_PACKAGE_VER=$1
      ;;
    --target)
      shift
      QT5_CROSS_COMPILED_BINARIES_TARGET=$1
      ;;
    --img)
      shift
      IMG_FILE=$1
      ;;
    --confclean)
      CONFCLEAN=1
      ;;
    --)
      break
      ;;
    -*)
      split=$1
      shift
      set -- $(echo "$split" | cut -c 2- | sed 's/./-& /g') "$@"
      continue
      ;;
    *)
      break
      ;;
  esac
  shift
done

#-------------------------------------------------------------------------------

QT5_PACKAGE_VER_DEFAULT=5.3.2

if [ -z $QT5_PACKAGE_VER ]; then
  read -p "Qt version [$QT5_PACKAGE_VER_DEFAULT]: " QT5_PACKAGE_VER
  QT5_PACKAGE_VER=${QT5_PACKAGE_VER:-$QT5_PACKAGE_VER_DEFAULT}
fi

QT5_CROSS_COMPILED_BINARIES_TARGET_DEFAULT="/home/$USER/qt/rpi/$QT5_PACKAGE_VER"

if [ -z $QT5_CROSS_COMPILED_BINARIES_TARGET ]; then
  echo "Where do you want to save your cross compiled sources?"
  read -p "Target directory [$QT5_CROSS_COMPILED_BINARIES_TARGET_DEFAULT]: " QT5_CROSS_COMPILED_BINARIES_TARGET
  QT5_CROSS_COMPILED_BINARIES_TARGET=${QT5_CROSS_COMPILED_BINARIES_TARGET:-$QT5_CROSS_COMPILED_BINARIES_TARGET_DEFAULT}
fi

#-------------------------------------------------------------------------------

SCRIPT=$(readlink -f "$0")
BASE_DIR="$(dirname "$SCRIPT")/qt"
MOUNT_DIR="$BASE_DIR/rpi/rasp-pi-rootfs"
ROOTFS_DIR="$BASE_DIR/rpi/rootfs"

echo "Compiling Qt $QT5_PACKAGE_VER in $QT5_CROSS_COMPILED_BINARIES_TARGET"

read -p "Press [ENTER] to continue..."  X

#-------------------------------------------------------------------------------
# Mount img file

if [ ! -d "$MOUNT_DIR/etc" ]; then
  mkdir -p $MOUNT_DIR
  mkdir -p $ROOTFS_DIR

  if [ -z $IMG_FILE ]; then
    read -p "Please enter the path to your img file: " IMG_FILE
  fi

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

REQUIRED="build-essential git gcc-multilib ctorrent unzip libglu1-mesa-dev wget lib32z1-dev"
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
if [ $CONFCLEAN == 1 ]; then
  if [ -d "$BASE_DIR/qt-everywhere-opensource-src-$QT5_PACKAGE_VER" ]; then
    if [ "$(id -u)" != "0" ]; then
      sudo rm -r "$BASE_DIR/qt-everywhere-opensource-src-$QT5_PACKAGE_VER"
    else
      rm -r "$BASE_DIR/qt-everywhere-opensource-src-$QT5_PACKAGE_VER"
    fi
  fi
fi

if [ ! -d "$BASE_DIR/qt-everywhere-opensource-src-$QT5_PACKAGE_VER" ]; then
  cd $BASE_DIR
  if [ ! -f "$BASE_DIR/qt-everywhere-opensource-src-$QT5_PACKAGE_VER.tar.gz" ]; then
    wget http://download.qt-project.org/official_releases/qt/5.3/$QT5_PACKAGE_VER/single/qt-everywhere-opensource-src-$QT5_PACKAGE_VER.tar.gz
  fi
  tar -xf qt-everywhere-opensource-src-$QT5_PACKAGE_VER.tar.gz
  
  # Patch Qt
  cp 0001-Adjusts-to-build-qtbase-with-support-to-openvg.patch qt-everywhere-opensource-src-$QT5_PACKAGE_VER/qtbase
  cd $BASE_DIR/qt-everywhere-opensource-src-$QT5_PACKAGE_VER/qtbase
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

mkdir -p $QT5_CROSS_COMPILED_BINARIES_TARGET

if [ ! -f "$BASE_DIR/qt-everywhere-opensource-src-$QT5_PACKAGE_VER/.CONFIGURED" ]; then
  cd "$BASE_DIR/qt-everywhere-opensource-src-$QT5_PACKAGE_VER"
  ./configure -opengl es2 -device linux-rasp-pi-g++ -device-option CROSS_COMPILE=$BASE_DIR/gcc-4.7-linaro-rpi-gnueabihf/bin/arm-linux-gnueabihf- -sysroot $ROOTFS_DIR -opensource -confirm-license -optimized-qmake -release -prefix $QT5_CROSS_COMPILED_BINARIES_TARGET -no-pch -nomake tests -nomake examples -plugin-sql-sqlite
  touch $BASE_DIR/qt-everywhere-opensource-src-$QT5_PACKAGE_VER/.CONFIGURED
fi

if [ ! -f "$BASE_DIR/qt-everywhere-opensource-src-$QT5_PACKAGE_VER/.COMPILED" ]; then
  #cd "$BASE_DIR/qt-everywhere-opensource-src-$QT5_PACKAGE_VER"
  CORES=`grep -c '^processor' /proc/cpuinfo`
  CORES=`echo $CORES | grep '^[[:digit:]]*$'`
  make -j $CORES
  make install
  touch $BASE_DIR/qt-everywhere-opensource-src-$QT5_PACKAGE_VER/.COMPILED
else 
  echo "Already compiled"
fi
  
