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
    NeuralNetwork network(IMG_PIXELS, {100, 10});
    
    int right = 0;
    int wrong = 0;
    for (int i = 0; i < 10000; ++i) {
        int lab = array_lab[i];
        if (i % 100 == 0) {
            progressBar->setValue(i/100);
        }
        QCoreApplication::processEvents();
        baseDir.mkpath(QString("%1").arg(lab));
        QString fileName(baseDir.filePath(QString("%1/%2.png").arg(lab).arg(idxs[lab])));

        idxs[lab] += 1;
        const uchar* t = reinterpret_cast<const uchar*>(array_img.constData()) + i*IMG_PIXELS;
        QImage image = QImage(t, IMG_SIZE, IMG_SIZE, QImage::Format_Grayscale8);
        Vector img;
        for (int x = 0; x < IMG_SIZE; ++x) {
            for (int y = 0; y < IMG_SIZE; ++y) {
                img.push_back((float) image.pixelColor(x, y).valueF());
            }
        }

        network.process(img);
        if (i % 200 < 100) {
            Vector out = network.output();
            float maxv = out[0];
            int maxi = 0;
            for (int k = 1; k < out.size(); ++k) {
                if (maxv < out[k]){
                    maxv = out[k];
                    maxi = k;
                }
            }

            const char* status;
            if (lab == maxi) {
                right++;
                status = "-CORRECT-";
            } else {
                wrong++;
                status = "incorrect";
            }
            printf("%s: real %d, network think %d with %.2f%%\n", status, lab, maxi, maxv * 100);
        }
        else {
            if (i % 200 == 100) {
                printf("--------------------\nright %2d wrong %d\n====================\n", right, wrong);
                right = 0;
                wrong = 0;
            }
            printf("training %2d...\n", i % 100);
            network.train(lab, img, .1);
//            printf("deltas: %s\n", Matrix(network.deltas).str().toUtf8().toStdString().c_str());
        }

//*/

//        image.save(fileName);
    }
}

