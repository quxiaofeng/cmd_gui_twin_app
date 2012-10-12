#include "rocextractor.h"

RocExtractor::RocExtractor(QObject *parent) :
    QObject(parent)
{
    debug = true;
    center = cv::Point2d(240.0f, 180.0f);
    innerRadius = 80.0f;
    outerRadius = 180.0f;
    verticalDis = 85.0f;
    height = 70.0f;
    width = 120.0f;
}


void RocExtractor::setSrcImage(const cv::Mat &im)
{
    this->srcImage = im.clone();
}

cv::Mat RocExtractor::getRocImage()
{
    if (this->srcImage.data){
        this->run();
    }
    return this->rocImage;
}

cv::Mat RocExtractor::drawFov(cv::Mat& im)
{
    //    +--------------------------------------------+
    //    |                 ,,.----.,,                 |
    //    |             ,-``          ``',,            |
    //    |          ,-`                   ',          |
    //    |         -      innerRatius       ',        |
    //    |       ,'         _,.--.,,          \       |
    //    |      /         .`        .',        \      |
    //    |     /        ,'        ,'   .       \      |
    //    |     |       / center  -      ,       |     |
    //    |     |       |       @`----------------     |
    //    |     |       \   outerRadius  '       |     |
    //    |      ,       `,             `       /      |
    //    |      \         ',        ,-`        /      |
    //    |       `.         `''--''`          /       |
    //    |         .                        .`        |
    //    |          `.,                   .`          |
    //    |             '-,_          _,-'`            |
    //    |                 `'''---''`                 |
    //    +--------------------------------------------+
    if (im.channels() == 1) {
        cv::cvtColor(im,im,CV_GRAY2BGR);
    }
    int thickness = 2;
    cv::Scalar fillColor(0,0,255);
    cv::circle(im, center, thickness, fillColor, thickness, 8, 0);
    cv::circle(im, center, innerRadius, fillColor, thickness, 8, 0);
    cv::circle(im, center, outerRadius, fillColor, thickness, 8, 0);
    return im;
}


cv::Mat RocExtractor::drawReferRegion(cv::Mat& im)
{
    //    |                                                   |
    //    |                         @ image center            |
    //    |                         |                         |
    //    |                         |  verticalDis            |
    //    |                         |                         |
    //    |             upleft @----+-----+                   |
    //    |                    |          |                   |
    //    |                    |          |  height           |
    //    |                    |          |                   |
    //    |                    +----------@ downright         |
    //    |                        width                      |
    //    |                                                   |
    //    |                                                   |
    //    +---------------------------------------------------+
    cv::Point2d upleft(center.x-width/2.0f,center.y+verticalDis);
    cv::Point2d downright(upleft.x+width,upleft.y+height);
    if (im.channels() == 1) {
        cv::cvtColor(im,im,CV_GRAY2BGR);
    }
    int thickness = 1;
    cv::Scalar fillColor(0,255,0);
    cv::rectangle(im, upleft, downright, fillColor, thickness,8);
    return im;
}

void RocExtractor::run()
{
    rocImage = srcImage.clone();
    rocImage = drawFov(rocImage);
    rocImage = drawReferRegion(rocImage);
}


