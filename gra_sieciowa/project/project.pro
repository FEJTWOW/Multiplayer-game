TEMPLATE = subdirs

SUBDIRS += \
    clientUtils \
    game_main \
    server2 \
    serverUtils \
    tests \
    utils


ServerTest.depends = utils
game_main.depends = utils
server2.depends = utils
