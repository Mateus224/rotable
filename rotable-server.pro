TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = shared \
          server

# Dependencies
server.depends = shared
