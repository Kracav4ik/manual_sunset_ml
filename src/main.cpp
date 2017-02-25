#include <QApplication>
#include "MainWindow.h"
#include "layer.h"

int main(int argc, char* argv[]) {
//    QApplication app(argc, argv);
//    MainWindow* window = new MainWindow();
//    return app.exec();
    Matrix m1({{1},{0},{3}});
    Matrix m2({{0, 5, 6}});
    Matrix m3(3,1);
    Matrix m4(1,3);

    printf("%s\n", (m1*m2).str().toUtf8().toStdString().c_str());
    printf("%s\n", (m3*m4).str().toUtf8().toStdString().c_str());

    return 0;
}
