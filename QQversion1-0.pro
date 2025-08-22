TEMPLATE = subdirs

CONFIG+=ordered

SUBDIRS += \
    Client \
    Server \
    common

Client.depends = common
Server.depends = common
