//
//  ofxConrec.cpp
//  emptyExample
//
//  Created by Matthias Rohrbach on 12.09.14.
//
//

#include "ofxConrec.h"

ofxConrec::ofxConrec(){
    
    mesh.setMode(OF_PRIMITIVE_LINES);
    
}
ofxConrec::~ofxConrec(){
    
}
void ofxConrec::setHeightMap(float* _heightmap){
    heightmap=_heightmap;
}

void ofxConrec::setSize(int _width, int _height){
    width=_width;
    height=_height;
}


void ofxConrec::init(int _lowest, int _highest, int _nlevels){
    
    nlevels=_nlevels;
    lowest=_lowest;
    highest=_highest;
    
    float levelstep=(float)(highest-lowest)/nlevels;
    
    cmap=new CContourMap();
    nlevels=cmap->generate_levels(lowest, highest, nlevels);
    cmap->contour(this);
    
    ofFloatColor linec;
    linec.setHsb(1, 1,1);
    
    for(int i=0;i<nlevels;i++){
        CContourLevel* level=cmap->level(i);
        
        linec.setHue(i/50.0f);
        
        if(level!=NULL){
            
            for(int h=0;h<level->raw->size();h++){
                SPair pair=level->raw->at(h);
                
                mesh.addColor(linec);
                mesh.addVertex(ofVec3f(pair.p1.x, pair.p1.y,i*levelstep));
                
                mesh.addColor(linec);
                mesh.addVertex(ofVec3f(pair.p2.x, pair.p2.y,i*levelstep));
                
            }
        }
    }
}

void ofxConrec::draw(){
    ofSetColor(255,255,255);
    mesh.draw();
    
}


double ofxConrec::value(double _x, double _y){
    int index=_x+_y*width;
    return (double)heightmap[index];
}

SPoint ofxConrec::upper_bound(){
    return SPoint(width-1,height-1);
    
}
SPoint ofxConrec::lower_bound(){
    return SPoint(0,0);
}
