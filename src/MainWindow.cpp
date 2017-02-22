#include "MainWindow.h"
#include "NeuralNetwork.h"
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
        const uchar* t = reinterpret_cast<const uchar*>(array_img.constData()) + i*IMG_PIXELS;
        QImage image = QImage(t, IMG_SIZE, IMG_SIZE, QImage::Format_Grayscale8);
        NeuroVector<float> img;
        for (int x = 0; x < IMG_SIZE; ++x) {
            for (int y = 0; y < IMG_SIZE; ++y) {
                img.push_back((float) image.pixelColor(x, y).valueF());
            }
        }
        NeuralNetwork network(1000, 10);
        NeuroVector<float> out = network.input(img);
        float maxv = out[0];
        int maxi = 0;
        for (int k = 1; k < out.size(); ++k) {
            if (maxv < out[k]){
                maxv = out[k];
                maxi = k;
            }
        }
        printf("real %d, network think %d with %f%%\n", lab, maxi, maxv*100);
//        image.save(fileName);
    }
}

