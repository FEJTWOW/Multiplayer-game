TEMPLATE = subdirs

SUBDIRS += \
    clientUtils \
    game_main \
    server2 \
    serverUtils \
    tests \
    utils


game_main.depends = clientUtils
server2.depends = serverUtils
serverUtils.depends = utils
clientUtils.depends = utils
tests.depends = serverUtils
