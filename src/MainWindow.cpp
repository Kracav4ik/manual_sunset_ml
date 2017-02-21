#include "MainWindow.h"
#include <QFileDialog>

MainWindow::MainWindow() {
    setupUi(this);
    show();
}

void MainWindow::on_browseButton_clicked() {
    QString path = QFileDialog::getOpenFileName(this, "Open data pack", "../conve", "*-labels.idx1-ubyte");
    if (!path.isNull()){
        pathEdit->setText(path);
    }
}

void MainWindow::on_processButton_clicked() {
    if (pathEdit->text().isEmpty()){
        return;
    }

    QFile labFile("../conve/t10k-labels.idx1-ubyte");
    labFile.open(QIODevice::ReadOnly);

    QFile imgFile("../conve/t10k-images.idx3-ubyte");
    imgFile.open(QIODevice::ReadOnly);

    int idxs[10] = {0};
    QByteArray array_lab = labFile.readAll().mid(8);
    QByteArray array_img = imgFile.readAll().mid(16);
    QDir baseDir("../conve/images/");
    for (int i = 0; i < 10000; ++i) {
        int lab = array_lab[i];
        if (i % 100 == 0) {
            progressBar->setValue(i/100);
        }

        baseDir.mkpath(QString("%1").arg(lab));
        QString fileName(baseDir.filePath(QString("%1/%2.png").arg(lab).arg(idxs[lab])));

        idxs[lab] += 1;
        const uchar* t = reinterpret_cast<const uchar*>(array_img.constData()) + i*28*28;
        QImage image = QImage(t, 28, 28, QImage::Format_Grayscale8);
        
        image.save(fileName);
    }
}

