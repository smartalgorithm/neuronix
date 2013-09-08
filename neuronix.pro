TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    neuron.cpp \
    libneuron.cpp \
    neuron_conjunction.cpp

HEADERS += \
    neuron.h \
    libneuron.h \
    neuron_conjunction.h

OTHER_FILES += \
    COPYING.txt \
    README.txt

