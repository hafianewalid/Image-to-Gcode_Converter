#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#include "Freeman.h"

Vec3b Freeman::getpixel(int x, int y, Mat_<Vec3b> img) {
    if(x<0||x>img.cols||y<0||y>img.rows)
        return Vec3b(255,255,255);
    Vec3b pix = img.at<Vec3b>(y,x);
    return pix;
}

void Freeman::actualiser(int t[],int s[],int d){
    if(d==2){t[0]=s[0]; t[1]=s[1]-1;}
    if(d==6){t[0]=s[0]; t[1]=s[1]+1;}
    if(d==0){t[0]=s[0]+1; t[1]=s[1];}
    if(d==4){t[0]=s[0]-1; t[1]=s[1];}
    if(d==7){t[0]=s[0]+1; t[1]=s[1]+1;}
    if(d==3){t[0]=s[0]-1; t[1]=s[1]-1;}
    if(d==1){t[0]=s[0]+1; t[1]=s[1]-1;}
    if(d==5){t[0]=s[0]-1; t[1]=s[1]+1;}
}

list<int> Freeman::get_code(Mat_<Vec3b> image){

    list<int> code;
    bool FIN=false;
    bool sec=true;
    int dir=4,dir_init=4;
    int t[]={0,0};
    int s[]={0,0};
    int P0[2];
    int P1[2];

    bool ver=false;
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            if(getpixel(j,i,image)[0]==0){
                s[0]=j;s[1]=i;ver= true;
            }
            if(ver)break;
        }
        if(ver)break;
    }

    if(!ver)
        return code;

    int depx=s[0];int depy=s[1];
    P0[0]=s[0];P0[1]=s[1];
    while (!FIN){
        while(getpixel(t[0],t[1],image)[0]!=0){
            dir=(dir+1)%8;
            actualiser(t,s,dir);
        }
        dir_init=(dir+5)%8;
        if(sec)
        {P1[0]=t[0];P1[1]=t[1];sec=false;}
        else
            FIN=(P0[0]==s[0]&&P0[1]==s[1]&&P1[0]==t[0]&&P1[1]==t[1]);
        s[0]=t[0];s[1]=t[1];
        actualiser(t,s,dir_init);
        code.push_back(dir);
        dir=dir_init;
    }

    code.push_front(depy);code.push_front(depx);
    return  code;
}
