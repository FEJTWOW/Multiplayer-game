TEMPLATE = subdirs

SUBDIRS += \
    clientUtils \
    game_main \
    server2 \
    serverUtils \
    tests \
    utils


game_main.depends = utils
server2.depends = utils
serverUtils.depends = utils
clientUtils.depends = utils
