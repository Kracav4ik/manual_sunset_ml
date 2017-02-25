#include <QApplication>
#include "MainWindow.h"
#include "layer.h"

int main(int argc, char* argv[]) {
//    QApplication app(argc, argv);
//    MainWindow* window = new MainWindow();
//    return app.exec();
    Matrix m1(3,1);
    Matrix m2(1,3);

    printf("%s", (m2*m1).str().toUtf8().toStdString().c_str());

    return 0;
}
