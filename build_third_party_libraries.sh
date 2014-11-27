#!/bin/sh -e

CORES=`grep -c '^processor' /proc/cpuinfo`
CORES=`echo $CORES | grep '^[[:digit:]]*$'`

SCRIPT=$(readlink -f "$0")
BASE_DIR="$(dirname "$SCRIPT")/third-party"

#------------------------------------------------------------------------------
# Install required packages

REQUIRED="subversion git"
for pkg in $REQUIRED; do
  if ! dpkg --get-selections | grep -q "^$pkg[[:space:]]*install$" >/dev/null; then
    if [ "$(id -u)" != "0" ]; then
      sudo apt-get -qq install $pkg
    else
      apt-get -qq install $pkg
    fi
  fi
done

# Create directory:
if [ ! -d $BASE_DIR ]; then
  mkdir -p $BASE_DIR
fi

#------------------------------------------------------------------------------
# google-breakpad

if [ ! -f "$BASE_DIR/google-breakpad-read-only/.COMPILED" ]; then
  if [ ! -d "$BASE_DIR/google-breakpad-read-only/.svn" ]; then
    svn checkout http://google-breakpad.googlecode.com/svn/trunk/ "$BASE_DIR/google-breakpad-read-only"
    cd "$BASE_DIR/google-breakpad-read-only"
  else
    cd "$BASE_DIR/google-breakpad-read-only"
    svn update
  fi
  
  ./configure
  make -j $CORES
  touch .COMPILED
fi

#------------------------------------------------------------------------------
# qwt

QWT_VERSION=6.1.1

if [ ! -d "$BASE_DIR/qwt/src" ]; then
  if [ ! -f "$BASE_DIR/qwt-$QWT_VERSION.tar.bz2" ]; then
    wget -nc -c -O "$BASE_DIR/qwt-$QWT_VERSION.tar.bz2" http://downloads.sourceforge.net/project/qwt/qwt/$QWT_VERSION/qwt-$QWT_VERSION.tar.bz2?r=&ts=1417009396
  fi
  tar -xf "$BASE_DIR/qwt-$QWT_VERSION.tar.bz2" -C $BASE_DIR
  mv "$BASE_DIR/qwt-$QWT_VERSION" "$BASE_DIR/qwt"

  QMAKE_DEFAULT="/home/$USER/qt/Qt5.3.2/5.3/gcc_64/bin/qmake"
  read -p "qmake [$QMAKE_DEFAULT]: " QMAKE_PATH
  QMAKE_PATH=${QMAKE_PATH:-$QMAKE_DEFAULT}
  
  # build as static library:
  sed -i '/QWT_CONFIG           += QwtDll/c\#QWT_CONFIG           += QwtDll' "$BASE_DIR/qwt/qwtconfig.pri"

  cd "$BASE_DIR/qwt"
  $QMAKE_PATH qwt.pro 
  make -j $CORES
fi

