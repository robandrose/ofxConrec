//
//  ofxConrec.h
//
//
//  Created by Matthias Rohrbach on 12.09.14.
//
//


#pragma once
#include "ofMain.h"
#include "contours.h"


class ofxConrec:public CRaster{
    
public:
	
	ofxConrec();
	virtual ~ofxConrec();
    
    void setHeightMap(float* heightmap);
    void setSize(int _width, int _height);
    void init(int _lowest, int _highest, int _nlevels);
    void draw();
    
    double value(double, double);
    SPoint upper_bound();
    SPoint lower_bound();
    

private:
	
    float* heightmap;
    int width;
    int height;
    
    int nlevels;
    int lowest;
    int highest;
    
    CContourMap* cmap;
    
    ofVboMesh mesh;
    
};
