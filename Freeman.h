#ifndef TP2_TI_P1_FREEMAN_H
#define TP2_TI_P1_FREEMAN_H


#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

class Freeman {

private:
    Vec3b  getpixel(int x , int y , Mat_<Vec3b> img);
    void actualiser(int t[],int s[],int d);
public:
    list<int> get_code(Mat_<Vec3b> image);

};


#endif //TP2_TI_P1_FREEMAN_H
