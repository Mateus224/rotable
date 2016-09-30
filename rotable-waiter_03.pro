TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = shared \
          waiter3

# Dependencies
waiter.depends = shared
