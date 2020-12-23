//
// Created by walidone on 16‏/1‏/2020.
//
#include <iostream>
#include <fstream>
#include <math.h>
#include <list>
#include <vector>
#include "img2forme.h"
#include <math.h>
using namespace std;

// param machine
double d = 1.75;
double nw = 0.4;

// param pieces
double lt = 0.2;



double delta_e(double l) {
    return ((nw*lt*l*4) / (M_PI*d*d));
}

double dist(vector<double> p1 ,vector<double> p2){
    return sqrt((p1[0] - p2[0])*(p1[0] - p2[0]) + (p1[1] - p2[1])*(p1[1] - p2[1]) );
}

string Move(vector<double> point,double e){
    return "G1 X"+to_string(point[0])+" Y"+to_string(point[1])+" E"+to_string(e)+"  F1200 \n";
}
string Move(vector<double> point){
    return "G1 X"+to_string(point[0])+" Y"+to_string(point[1])+"  F3000 \n";
}
string Start(vector<double> point, double Z){
    return "G1 X"+to_string(point[0])+" Y"+to_string(point[1])+" Z"+to_string(Z)+"  F3000 \nG92 E0\n";
}

string Gcode_layer(list<vector<double>> points, double z){
   vector<double> p,pnext;
   p=points.front();points.pop_front();
   string gcode=Start(p,z);
   double e=0.0;
   while(!points.empty()){
       pnext=points.front();points.pop_front();
       if(p[2]) {
           e += delta_e(dist(p, pnext));
           gcode += Move(pnext, e);
       } else
           gcode += Move(pnext);
       p=pnext;
   }
   return gcode;
}


list<vector<double>> translation(vector<double> pos,list<vector<double>> forme){
    list<vector<double>> formeT;
    for (auto& p : forme) {
        vector<double> pt(3,0);
        pt[0]=p[0]+pos[0];pt[1]=p[1]+pos[1];pt[2]=p[2];
        formeT.push_back(pt);
    }
    return formeT;
}

string Gcode_forme(list<vector<double>>forme,int layers){
    string Gcode="";
    for(int i=0;i<layers;i++)
       Gcode+=Gcode_layer(forme,i*lt);
    return Gcode;
}

string Start_param(){
    return "G21 G90\nG28\nM104 S210\nM190 S60\nM109 S210\nM140 S60\nM106\nM105\nG92 E0\nG1 E10 F1200 \nG92 E0\n";
}
string End_param(){
    return  "G92 E0\nM104 S0\nM140 S0;Retract the filament\nG92 E1\nG1 E-1 F300\nG28 X0 Y0\nM84;\n";
}


list<vector<double>> Circle(vector<double> center , double r , double nb_seg){
    list<vector<double>> list_points;
    for( int i=0 ;i<nb_seg+1;i++){
        vector<double> p(3);
        p[0] = center[0] + cos(i * 2 * M_PI/nb_seg) * r;
        p[1] = center[1] + sin(i * 2 * M_PI/nb_seg) * r;
        p[2] = 1;
        list_points.push_back(p);
    }
    //list_points.pop_back();
    return list_points;
}

string Solidcylender(vector<double> center , double r , double nb_seg ,int layers){
    string gcode;
    list<vector<double>> cocenter_circles1,cocenter_circles2;

    for(int i=0 ;i<r/nw ;i++) {
        cocenter_circles1.merge(Circle(center, r - (nw * i), nb_seg));
        cocenter_circles2.merge(Circle(center, r - (nw * i), nb_seg));
    }
    cocenter_circles2.reverse();

    for(int i=0;i<layers;i++)
        if(i%2)gcode+=Gcode_layer(cocenter_circles2,i*lt);
        else gcode+=Gcode_layer(cocenter_circles1,i*lt);
    return gcode;
}

string Hemispher(vector<double> center , double nb_seg ,int layers){
    string gcode;
    list<vector<double>> circle;
    double rayon;double l=layers-1;
    for(int i=1;i<layers;i++) {
        rayon=cos(i*((M_PI/2)/(l)))*(l);
        rayon=sqrt(rayon*rayon-i*i);
        //l=center[1]+sin(i*((M_PI/2)/layers))*layers;
        for(int j=0;j<10;j++) {
            circle = Circle(center, rayon * lt - j * lt, nb_seg);
            gcode += Gcode_layer(circle, i * lt);
        }
    }

    return gcode;
}

void img_gcode(string path){
   img2forme img2f;
   list<vector<double>> forme = img2f.image2fome(path,0.1);
   //for (auto& it : forme) {cout<<" "<<it[0]<<","<<it[1]<<endl;}cout<<"\n\n\n";
   forme=translation({50,50},forme);
   string gc=Gcode_forme(forme,40);

    ofstream gcode_file;
    gcode_file.open(path+".gcode");
    gcode_file << Start_param();
    gcode_file <<gc;
    gcode_file << End_param();
    gcode_file.close();

}

int main (int argc, char** argv) {


    ofstream gcode_file;
    //gcode_file.open("g.gcode");
    //gcode_file << Start_param();

    //list<vector<double>> circle=Circle({50.0,50.0},10.0,1000.0);
    //circle=translation({50,50},circle);
    //string cylinder=Gcode_forme(circle,30);
    //gcode_file <<cylinder;

    //gcode_file<<Solidcylender({100,100},10,100,50);

    //gcode_file<<Hemispher({100,100},100,50);

    //gcode_file << End_param();
    //gcode_file.close();


    string path=argv[1];
    img_gcode(path);

    return 0;
}
