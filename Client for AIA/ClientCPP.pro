TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        exec_commands.cpp \
        main.cpp \
        terminal.cpp

HEADERS += \
    exec_commands.h \
    structures.h \
    terminal.h
