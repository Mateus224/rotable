TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = shared \
          waiter

# Dependencies
waiter.depends = shared
