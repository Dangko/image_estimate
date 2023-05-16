#include <iostream>

#include "ros/ros.h"
#include <cv_bridge/cv_bridge.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc_c.h>

#include "ImageAssessMetric.h"

using namespace cv;

int main(int argc, char** argv)
{ 
    //参考文献：Camera Exposure Control for Robust Robot Vision with Noise-Aware Image Quality Assessment
    //代码工程：https://github.com/UkcheolShin/Noise-AwareCameraExposureControl
    

    IMAGE_QUALITY_ESTIMATOR image_qulity_estimator;
    cv::Mat image1,image2;
    cv::Mat image1_gray,image2_gray;

    //add your absolute path
    image1 = imread("/home/dango/dango/issue_data/CODE/image_estimate_ws/src/image_estimate/image_test/RGB_night.jpg");
    image2 = imread("/home/dango/dango/issue_data/CODE/image_estimate_ws/src/image_estimate/image_test/RGB_day.jpg"); 

    cv::cvtColor(image1,image1_gray,cv::COLOR_RGB2GRAY);
    cv::cvtColor(image2,image2_gray,cv::COLOR_RGB2GRAY);
   
 
    int Img1_width  = image1.rows;
    int Img1_height = image1.cols;
    int Img2_width  = image2.rows;
    int Img2_height = image2.cols;
    cv::Mat image1_gradient(Img1_width,Img1_height,CV_32F);
    cv::Mat image2_gradient(Img2_width,Img2_height,CV_32F);

    //calculate noise metric
    double noise_metric_night     = image_qulity_estimator.CalImageNoiseVariance(image1);
    double noise_metric_day = image_qulity_estimator.CalImageNoiseVariance(image2);
    //calculate gradient metric
    double gradient_metric_night     = image_qulity_estimator.CalImgGradient(image1_gray,image1_gradient);
    double gradient_metric_day = image_qulity_estimator.CalImgGradient(image2_gray,image2_gradient);
    //calculate total metric
    double quality_night          = image_qulity_estimator.GetImgQualityValue(image1);
    double quality_day      = image_qulity_estimator.GetImgQualityValue(image2);

    //terminal output
    std::cout<<"RGB NIGHT noise metric      : "<<noise_metric_night<<std::endl;
    std::cout<<"RGB DAY noise metric        : "<<noise_metric_day<<std::endl;
    std::cout<<"RGB NIGHT gradient metric   : "<<gradient_metric_night<<std::endl;
    std::cout<<"RGB DAY gradient metric     : "<<gradient_metric_day<<std::endl;
    std::cout<<"RGB NIGHT total qulity metric   : "<<quality_night<<std::endl;
    std::cout<<"RGB DAY total qulity metric     : "<<quality_day<<std::endl;

    //show image
    imshow("RGB image night",image1);
    imshow("RGB image day",image2);
    

    waitKey(0);

    return 0;
}

