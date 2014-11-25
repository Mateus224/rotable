TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = shared \
          admin

# Dependencies
admin.depends = shared
