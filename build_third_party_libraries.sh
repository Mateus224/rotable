#!/bin/sh -e

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
if [ ! -d "third-party" ]; then
  mkdir third-party
fi
cd third-party

# wiringPi
if [ ! -f "wiringPi/.COMPILED" ]; then
  if [ ! -d "wiringPi/.git" ]; then
    git clone git://git.drogon.net/wiringPi
  fi
  
  cd wiringPi
  git pull origin
  ./build
  touch .COMPILED
  cd ..
fi

# google-breakpad
if [ ! -f "google-breakpad-read-only/.COMPILED" ]; then
  if [ ! -d "google-breakpad-read-only/.svn" ]; then
    svn checkout http://google-breakpad.googlecode.com/svn/trunk/ google-breakpad-read-only
    cd google-breakpad-read-only
  else
    cd google-breakpad-read-only
    svn update
  fi
  
  ./configure
  make
  touch .COMPILED
fi


