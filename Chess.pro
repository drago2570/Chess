TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        board.cpp \
        chess.cpp \
        figure.cpp \
        main.cpp \
        player.cpp

HEADERS += \
    board.h \
    cell.h \
    chess.h \
    coordinate.h \
    figure.h \
    info.h \
    player.h \
    utils.h
