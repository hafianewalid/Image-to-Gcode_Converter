//
// Created by walidone on 16‏/1‏/2020.
//


#include "img2forme.h"
#include "Freeman.h"

int deep=1;
int deepmax=1;


Vec3b img2forme::getpixel(int x, int y, Mat_<Vec3b> img) {
    if(x<0||x>img.cols||y<0||y>img.rows)
        return Vec3b(255,255,255);
    Vec3b pix = img.at<Vec3b>(y,x);
    return pix;
}

void img2forme::setpixel(int x , int y ,Mat_<Vec3b>& img,int r ,int g ,int b) {
    if(!(x<0||x>=img.cols||y<0||y>=img.rows)){
        Vec3b &pix = img.at<Vec3b>(y,x);
        pix[0] = r;
        pix[1] = g;
        pix[2] = b;
    }
}

list<vector<double>> img2forme::image2fome(string path, double size){

    Mat_<Vec3b> image = imread(path);
    list<vector<double>> forme;
    Freeman freeman;
    list<int>code=freeman.get_code(image);

    deep=0;
    while(!code.empty()&&deep<deepmax){
        deep++;
        forme.merge(External_contour2forme(image,code,size));
        code=freeman.get_code(image);
    }

    imwrite("res.png",image);
    return forme;
}
vector<int> img2forme::code2point(Mat_<Vec3b>& img, int x , int y , int c){
    vector<int> p={x,y};
    switch (c) {
        case 0 :
            p[0] = x+1;
            p[1] = y;
            break;
        case 1 :
            p[0] = x+1;
            p[1] = y-1;
            break;
        case 2 :
            p[0] = x;
            p[1] = y-1;
            break;
        case 3 :
            p[0] = x-1;
            p[1] = y-1;
            break;
        case 4 :
            p[0] = x-1;
            p[1] = y;
            break;
        case 5 :
            p[0] = x-1;
            p[1] = y+1;
            break;
        case 6 :
            p[0] = x;
            p[1] = y+1;
            break;
        case 7 :
            p[0] = x+1;
            p[1] = y+1;
            break;
    }
    setpixel(p[0],p[1],img,(deep*10)%255,(deep*20)%255,(deep*30)%255);
    return p;
}

list<vector<double>> img2forme::External_contour2forme(Mat_<Vec3b>& img,list<int> code,double size){
    list<vector<double>> forme;
    int x=code.front();code.pop_front();int y=code.front();code.pop_front();
    forme.push_back({x*size,y*size});
    forme.push_back({x*size,y*size,1});
    setpixel(x,y,img,deep,deep*2 ,deep*3);
    int c;int cp=code.front();vector<int>p={x,y};
    while (!code.empty()){
        c=code.front();code.pop_front();
        if(c!=cp){forme.push_back({p[0]*size,p[1]*size,1});setpixel(p[0],p[1],img,255,0 ,0);}
        //forme.push_back({p[0]*size,p[1]*size});
        p=code2point(img,p[0],p[1],c);cp=c;
    }
    //forme.push_back({x*size,y*size,1});
    return forme;
}

