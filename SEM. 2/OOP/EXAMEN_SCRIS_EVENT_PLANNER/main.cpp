#include <QApplication>
#include "./UI/ui.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainUI mainUI;
    mainUI.startApplication();

    return app.exec();
}