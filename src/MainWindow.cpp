#include "MainWindow.h"
#include "NeuralNetwork.h"
#include <QFileDialog>
#include <QTime>
#include "utils.h"


float clamp(float a, float b, float x) {
    return qMax(a, qMin(x, b));
}

template<typename T>
float vmin(const T& rv) {
    float result = 0;
    for (int i = 0; i < IMG_PIXELS; ++i) {
        result = result < rv[i] ? result : rv[i];
    }
    return result;
}

template<typename T>
float vmax(const T& rv) {
    float result = 0;
    for (int i = 0; i < IMG_PIXELS; ++i) {
        result = result > rv[i] ? result : rv[i];
    }
    return result;
}

void layer1Img(NeuralNetwork network, QString fileName, int outNeuron) {
    Matrix coeffMatrix = network.layers[0].coef;
    QImage image = QImage(280, 280, QImage::Format_RGB32);

    /*
    const RowView& l1Row = network.layers[1].coef.get_row(outNeuron);
    for (int x : range(coeffMatrix.width())) {
        for (int y : range(coeffMatrix.height())) {
            coeffMatrix[x][y] *= l1Row[y];
        }
    }
    //*/

    float img_min = coeffMatrix[0][0];
    float img_max = coeffMatrix[0][0];

    for (int x = 0; x < coeffMatrix.width(); ++x) {
        for (int y = 0; y < coeffMatrix.height(); ++y) {
            float val = coeffMatrix.get(x, y);
            if (img_max < val) {
                img_max = val;
            }
            if (img_min > val) {
                img_min = val;
            }
        }
    }


    for (int x_offset = 0; x_offset < 10; ++x_offset) {
        for (int y_offset = 0; y_offset < 10; ++y_offset) {
            const RowView& row = coeffMatrix.get_row(x_offset * 10 + y_offset);
            for (int x = 0; x < 28; ++x) {
                for (int y = 0; y < 28; ++y) {
                    float value = row[x * 28 + y];
                    QColor col(0, 0, 0);
                    if (value > 0) {
//                        value = clamp(0, 1, value);
                        value /= img_max;
                        col.setRedF(value);
                    } else {
//                        value = clamp(0, 1, value);
                        value /= img_min;
                        col.setBlueF(value);
                    }
                    image.setPixelColor(x_offset * 28 + x, y_offset * 28 + y, col);
                }
            }
        }
    }
    image.save(fileName);
}

void finalImg(const NeuralNetwork& network, QString fileName, int outer_neuron) {
    const RowView& outer_coeffs = network.layers[1].coef.get_row(outer_neuron);
    Vector image_data(IMG_PIXELS);
    for (int mid_neuron = 0; mid_neuron < network.layers[0].coef.height(); ++mid_neuron) {
        const RowView& mid_coeffs = network.layers[0].coef.get_row(mid_neuron);
        for (int pix = 0; pix < IMG_PIXELS; ++pix) {
            image_data[pix] += sigma(mid_coeffs[pix]) * outer_coeffs[mid_neuron];
        }
    }
//                    image_data = sigma(image_data)*2 - Vector(IMG_PIXELS, 1);
    float img_min = vmin(image_data);
    float img_max = vmax(image_data);
    QImage image = QImage(28, 28, QImage::Format_RGB32);
    for (int x = 0; x < 28; ++x) {
        for (int y = 0; y < 28; ++y) {
            float value = image_data[x * 28 + y];
            QColor col(0, 0, 0);
            if (value > 0) {
//                                value = clamp(0, 1, value);
                value /= img_max;
                col.setRedF(value);
            } else if (value < 0) {
//                                value = clamp(0, 1, -value);
                value /= img_min;
                col.setBlueF(value);
            }
            image.setPixelColor(x, y, col);
        }
    }
    image.save(fileName);

}

const int BATCH_SIZE = 200; // keep it divisible by 2 please

MainWindow::MainWindow() {
    setupUi(this);
    show();
}

void MainWindow::on_browseButton_clicked() {
    QString path = QFileDialog::getOpenFileName(this, "Open data pack", "../conve", "*-labels.idx1-ubyte");
    if (!path.isNull()) {
        pathEdit->setText(path);
    }
}

void MainWindow::on_processButton_clicked() {
    if (pathEdit->text().isEmpty()) {
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
        printf("%02x ", (uchar) byte);
    }
    printf("\n");
    int count = *(int*) array.data();
    array_img = array_img.mid(16);
    QDir baseDir("../conve/images/");
    NeuralNetwork network(IMG_PIXELS, {100, 10});

    int right = 0;
    int wrong = 0;
    float step = (float) doubleSpinBox->value();
    int start = QTime::currentTime().msecsSinceStartOfDay();
    int globalStart = start;
    int idx = 4000;
    QDir ib("../conve/images/train");
    baseDir.mkpath("gug_for_degug");
    for (int val: range(10)) {
        ib.mkpath(QString("%1").arg(val));
        layer1Img(network, ib.filePath(QString("%1/----.png").arg(val)), val);
    }
    for (int i = 0; i < count; ++i) {
        int lab = array_lab[i];
        if (i % 100 == 0) {
            progressBar->setValue(i / (count / 100));
        }
        QCoreApplication::processEvents();

        idxs[lab] += 1;
        const uchar* t = reinterpret_cast<const uchar*>(array_img.constData()) + i * IMG_PIXELS;
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
                if (maxv < out[k]) {
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
        } else {
            if (i % BATCH_SIZE == BATCH_SIZE / 2) {
                printf("--------------------\nright %2d wrong %d\n====================\n", right, wrong);
                right = 0;
                wrong = 0;
            }
//            printf("training %2d...\n", i % (BATCH_SIZE - BATCH_SIZE / 2));
            network.train(lab, img, step);
//            printf("deltas: %s\n", Matrix(network.deltas).str().toUtf8().toStdString().c_str());
        }
        if ((i + 1) % BATCH_SIZE == 0) {
            int end = QTime::currentTime().msecsSinceStartOfDay();
            printf("--------------------\ntime spent for batch: %2d msec\n====================\n", end - start);
            start = end;
            if (saveImages) {

                for (int val: range(10)) {
                    layer1Img(network, ib.filePath(QString("%2/%1.png").arg(i, 4, 10, QLatin1Char('0')).arg(val)), val);
                }
                for (int outer_neuron = 0; outer_neuron < network.layers[1].coef.height(); ++outer_neuron) {
                    QString fileName(baseDir.filePath(QString("gug_for_degug/%1-%2.png").arg(outer_neuron).arg(idx)));
                    finalImg(network, fileName, outer_neuron);
                }
                idx++;
                int genEnd = QTime::currentTime().msecsSinceStartOfDay();
                printf("--------------------\ntime spent for generate: %2d msec\n====================\n", genEnd - start);
                start = genEnd;
            }
        }
    }
    progressBar->setValue(100);
    int globalEnd = QTime::currentTime().msecsSinceStartOfDay();
    printf("\n--------------------\ntotal time spent: %2d msec\n====================\n", globalEnd - globalStart);
}

