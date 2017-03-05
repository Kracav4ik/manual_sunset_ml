#include "MainWindow.h"
#include "NeuralNetwork.h"
#include <QFileDialog>
#include <QTime>

const int BATCH_SIZE = 200; // keep it divisible by 2 please

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
    bool saveImages = generateImages->isChecked();

    QFile labFile(pathEdit->text());
    labFile.open(QIODevice::ReadOnly);

    QFile imgFile(pathEdit->text().replace("-labels.idx1-ubyte", "-images.idx3-ubyte"));
    imgFile.open(QIODevice::ReadOnly);

    int idxs[10] = {0};
    QByteArray array_lab = labFile.readAll().mid(8);
    QByteArray array_img = imgFile.readAll();
    QByteArray array;
    for (int j = 7; j > 3; --j) {
        array.push_back(array_img.mid(j, 1));
    }
    for (char byte : array) {
        printf("%02x ", (uchar)byte);
    }
    printf("\n");
    int count = *(int*)array.data();
    array_img = array_img.mid(16);
    QDir baseDir("../conve/images/");
    NeuralNetwork network(IMG_PIXELS, {100, 10});
    
    int right = 0;
    int wrong = 0;
    float step = (float) doubleSpinBox->value();
    int start = QTime::currentTime().msecsSinceStartOfDay();
    int globalStart = start;
    for (int i = 0; i < count; ++i) {
        int lab = array_lab[i];
        if (i % 100 == 0) {
            progressBar->setValue(i/(count/100));
        }
        QCoreApplication::processEvents();

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
        if (i % BATCH_SIZE < BATCH_SIZE / 2) {
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
//            printf("%s: real %d, network think %d with %.2f%%\n", status, lab, maxi, maxv * 100);
        }
        else {
            if (i % BATCH_SIZE == BATCH_SIZE / 2) {
                printf("--------------------\nright %2d wrong %d\n====================\n", right, wrong);
                right = 0;
                wrong = 0;
            }
//            printf("training %2d...\n", i % (BATCH_SIZE - BATCH_SIZE / 2));
            network.train(lab, img, step);
//            printf("deltas: %s\n", Matrix(network.deltas).str().toUtf8().toStdString().c_str());
        }
        if ((i+1) % BATCH_SIZE == 0) {
            int end = QTime::currentTime().msecsSinceStartOfDay();
            printf("--------------------\ntime spent for batch: %2d msec\n====================\n", end - start);
            start = end;
        }

//*/

        if (saveImages) {
            baseDir.mkpath(QString("%1").arg(lab));
            QString fileName(baseDir.filePath(QString("%1/%2.png").arg(lab).arg(idxs[lab])));
            image.save(fileName);
        }
    }
    progressBar->setValue(100);
    int globalEnd = QTime::currentTime().msecsSinceStartOfDay();
    printf("\n--------------------\ntotal time spent: %2d msec\n====================\n", globalEnd - globalStart);
}

