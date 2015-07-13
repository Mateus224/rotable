TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = shared \
          waiter2

# Dependencies
waiter.depends = shared
