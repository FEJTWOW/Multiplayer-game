TEMPLATE = subdirs

SUBDIRS += \
    game_main \
    server2 \
    tests \
    utils


ServerTest.depends = utils
game_main.depends = utils
server2.depends = utils
