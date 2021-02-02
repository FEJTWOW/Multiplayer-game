TEMPLATE = subdirs

SUBDIRS += \
    ServerTest \
    game_main \
    game_test \
    server2 \
    utils


ServerTest.depends = utils
game_main.depends = utils
server2.depends = utils
