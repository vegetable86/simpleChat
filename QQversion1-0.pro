TEMPLATE = subdirs

SUBDIRS += \
    common \
    Client \
    Server


Client.depends = common
Server.depends = common
