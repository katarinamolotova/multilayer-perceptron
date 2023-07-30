QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller/controller.cc \
    main.cc \
    model/model.cc \
    model/neural_net/graph/graph_neural_net.cc \
    model/neural_net/graph/layer.cc \
    model/neural_net/graph/neuron.cc \
    model/neural_net/matrix/helpers/matrix.cc \
    model/neural_net/matrix/matrix_neural_net.cc \
    model/parser/parser_datasets.cc \
    model/parser/parser_weights.cc \
    model/testing/tester.cc \
    model/training/trainer.cc \
    view/mainwindow.cc \
    view/paintscene.cc \
    view/qcustomplot.cc

HEADERS += \
    controller/controller.h \
    model/model.h \
    model/neural_net/factory.h \
    model/neural_net/graph/graph_neural_net.h \
    model/neural_net/graph/layer.h \
    model/neural_net/graph/neuron.h \
    model/neural_net/matrix/helpers/matrix.h \
    model/neural_net/matrix/matrix_neural_net.h \
    model/neural_net/neural_net.h \
    model/parser/parser_datasets.h \
    model/parser/parser_weights.h \
    model/testing/tester.h \
    model/training/trainer.h \
    view/mainwindow.h \
    view/paintscene.h \
    view/qcustomplot.h

FORMS += \
    view/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
