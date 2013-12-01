# -------------------------------------------------
# Project created by QtCreator 2010-05-28T23:52:57
# -------------------------------------------------
QT += network \
    svg
TARGET = qtfileman
TEMPLATE = app
INCLUDEPATH += ../plugins/qtsvgz_plugin
LIBS += -L../plugins/qtsvgz_plugin \
    -lsvgz
SOURCES += main.cpp \
    mainwindow.cpp \
    qextfilesystemmodel.cpp \
    qextfilesystemcontroller.cpp \
    qextdireditor.cpp \
    previewwidget.cpp \
    imagerenderer.cpp \
    qtfilecopier.cpp \
    qtcopydialog.cpp \
    filedeleter.cpp \
    deletedialog.cpp
HEADERS += mainwindow.h \
    qextfilesystemmodel.h \
    qextfilesystemcontroller.h \
    qextdireditor.h \
    previewwidget.h \
    imagerenderer.h \
    qtfilecopier.h \
    qtcopydialog.h \
    filedeleter.h \
    deletedialog.h
FORMS += mainwindow.ui \
    qextdireditor.ui \
    previewwidget.ui \
    qtoverwritedialog.ui \
    qtotherdialog.ui \
    qtcopydialog.ui \
    deletedialog.ui
RESOURCES += rresources.qrc
OTHER_FILES += go_previous.svg \
    go_up.svg \
    gohome.svg \
    go_next.svg \
    go_jump_locationbar.svg \
    edit_paste.svg \
    edit_delete.svg \
    edit_cut.svg \
    edit_copy.svg \
    QtCopyDialog \
    QtFileCopier
