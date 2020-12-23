//
// Created by walidone on 16‏/1‏/2020.
//

#ifndef SLICE_IMG2FORME_H
#define SLICE_IMG2FORME_H

#include <iostream>
#include <list>
#include <vector>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

class img2forme {

private:
    Vec3b  getpixel(int x , int y , Mat_<Vec3b> img);
    void setpixel(int x , int y ,Mat_<Vec3b>& img,int r ,int g ,int b);
public:
    list<vector<double>> image2fome(string path);

    list<vector<double>> image2fome(string path, double size);

    vector<int> code2point(Mat_<Vec3b> &img, int x, int y, int c);

    list<vector<double>> External_contour2forme(Mat_<Vec3b> &img, list<int> code, double size);
};


#endif //SLICE_IMG2FORME_H
