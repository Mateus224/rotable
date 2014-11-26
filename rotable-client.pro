TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = shared \
          client

# Dependencies
client.depends = shared
