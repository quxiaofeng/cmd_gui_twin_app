#include <QtCore/QCoreApplication>
#include <QThread>
#include <QDebug>
#include <QString>
#include <QRegExp>
#include <QTranslator>
#include <QFileInfo>
#include <QDir>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


#include <../algorithms/rocextractor.h>


#define DIE(r) die((r), __FILE__, __LINE__)

void die (const char *reason, const char *file, int line_num)
{
    qDebug() << "Exception occurred at line " << line_num << " in " << file
             << ": " << reason;
    exit(1);
}

void error(const char *reason)
{
    qDebug() << reason;
    exit(1);
}

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    const static bool debug = false;
    QFileInfo dstFileInfo;
    switch (argc) {
    case 2:
    case 3:
        break;
    default:
        error("wrong input number");
    }
    cv::Mat srcImage = cv::imread(argv[1]);
    if (debug) {
        qDebug() << argv[1];
    }
    RocExtractor roc_extractor;
    roc_extractor.setSrcImage(srcImage);
    cv::Mat dstImage = roc_extractor.getRocImage();
    switch (argc) {
    case 3:
        if (debug) {
            qDebug() << argv[2];
        }
        dstFileInfo = QFileInfo(argv[2]);
        if (dstFileInfo.exists()){
            cv::imwrite(argv[2],dstImage);
        }
        else if (dstFileInfo.absoluteDir().exists()) {
            cv::imwrite(dstFileInfo.filePath().toAscii().data(),dstImage);
        }
        else if (dstFileInfo.dir().mkpath(dstFileInfo.absoluteDir().absolutePath())) {
            cv::imwrite(dstFileInfo.filePath().toAscii().data(),dstImage);
        }
        break;
    case 2:
        QRegExp rxImageName("(?=.+)\\.(?=(bmp|dib|jpeg|jpg|jpe|jp2|png|pbm|pgm|ppm|sr|ras|tiff|tif)$)");
        rxImageName.setCaseSensitivity(Qt::CaseInsensitive);
        QString fullDstImageName = QString(argv[1]);
        QString suffix = QString(QObject::tr("_roc."));
        fullDstImageName.replace(rxImageName, suffix);
        if (debug) {
            qDebug() << fullDstImageName;
        }
        cv::imwrite(fullDstImageName.toAscii().data(),dstImage);
        break;
    }
    //return a.exec();
}
