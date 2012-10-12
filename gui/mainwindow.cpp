#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton_flip->setEnabled(false);

    opencvDispWindow = false;
    ui->checkBox_disp->setChecked(opencvDispWindow);

    ui->spinBox_centerX->setValue(roc_extractor.center.x);
    ui->spinBox_centerY->setValue(roc_extractor.center.y);
    ui->spinBox_inR->setValue(roc_extractor.innerRadius);
    ui->spinBox_outR->setValue(roc_extractor.outerRadius);
    ui->doubleSpinBox_vd->setValue(roc_extractor.verticalDis);
    ui->doubleSpinBox_h->setValue(roc_extractor.height);
    ui->doubleSpinBox_w->setValue(roc_extractor.width);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_open_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"),
                                                    "*",
                                                    tr("Image Files (*.png *.jpg *.bmp"));
    if (fileName.isNull()) return;
    image = cv::imread(fileName.toAscii().data());
    if (image.data) roc_extractor.setSrcImage(image);
    else return;
    ui->textBrowser_log->append(tr("image file: ")+fileName+tr(" loaded successfully"));
    ui->pushButton_flip->setEnabled(true);

    cv::Mat tempImage = image.clone();
    cv::cvtColor(tempImage,tempImage,CV_BGR2RGB);
    QImage img = QImage((const unsigned char*)(tempImage.data),
                        tempImage.cols,
                        tempImage.rows,
                        QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));
    tempImage.release();
    ui->label->resize(ui->label->pixmap()->size());

    if (opencvDispWindow) {
        cv::namedWindow("Original Image", CV_GUI_NORMAL);
        cv::imshow("Original Image", image);
    }
}

void MainWindow::on_pushButton_flip_clicked()
{
    dispImage = roc_extractor.getRocImage();
    if (dispImage.data);
    else{
        ui->pushButton_flip->setEnabled(false);
        return;
    }

    update(dispImage);
}

void MainWindow::on_checkBox_disp_stateChanged(int arg1)
{
    opencvDispWindow = arg1 == 2;
    if (opencvDispWindow);
    else
        cv::destroyAllWindows();
    // 0 unchecked, 1 partially checked, 2 checked.
}

void MainWindow::on_spinBox_centerX_valueChanged(int arg1)
{
    roc_extractor.center.x = arg1;
    dispImage = roc_extractor.getRocImage();
    if (dispImage.data)
        update(dispImage);
}

void MainWindow::on_spinBox_centerY_valueChanged(int arg1)
{
    roc_extractor.center.y = arg1;
    dispImage = roc_extractor.getRocImage();
    if (dispImage.data)
        update(dispImage);
}

void MainWindow::on_spinBox_inR_valueChanged(int arg1)
{
    roc_extractor.innerRadius = arg1;
    dispImage = roc_extractor.getRocImage();
    if (dispImage.data)
        update(dispImage);
}

void MainWindow::on_spinBox_outR_valueChanged(int arg1)
{
    roc_extractor.outerRadius = arg1;
    dispImage = roc_extractor.getRocImage();
    if (dispImage.data)
        update(dispImage);
}

void MainWindow::update(const cv::Mat image)
{
    cv::Mat drawnImage = image.clone();
    if (drawnImage.channels() == 1) {
        cv::cvtColor(drawnImage,drawnImage,CV_GRAY2RGB);
    } else if (drawnImage.channels() == 3) {
        cv::cvtColor(drawnImage,drawnImage,CV_BGR2RGB);
    }
    QImage img = QImage((const unsigned char*)(drawnImage.data),
                        drawnImage.cols,
                        drawnImage.rows,
                        QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));
    drawnImage.release();
    ui->label->resize(ui->label->pixmap()->size());

    if (opencvDispWindow) {
        cv::namedWindow("Current Image", CV_GUI_NORMAL);
        cv::imshow("Current Image", dispImage);
    }

    return;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (opencvDispWindow)
        cv::destroyAllWindows();
    event->accept();
}



void MainWindow::on_doubleSpinBox_vd_valueChanged(double arg1)
{
    roc_extractor.verticalDis = arg1;
    dispImage = roc_extractor.getRocImage();
    if (dispImage.data)
        update(dispImage);
}

void MainWindow::on_doubleSpinBox_h_valueChanged(double arg1)
{
    roc_extractor.height = arg1;
    dispImage = roc_extractor.getRocImage();
    if (dispImage.data)
        update(dispImage);
}

void MainWindow::on_doubleSpinBox_w_valueChanged(double arg1)
{
    roc_extractor.width = arg1;
    dispImage = roc_extractor.getRocImage();
    if (dispImage.data)
        update(dispImage);
}
