//// Projection manager for easy configuration times!
//// Homographic transform is basically taken from
//// Kyle McDonald's ofxCv HomographyExample, either
//// copied or changed only slightly.
////  
//// This should probably be extending ofBaseApp 
//// instead of being a separate class, but will
//// consider this after
//#pragma once
//
//#ifndef _projManager_h
//#define _projManager_h
//
//#include "ofMain.h"
//#include "ofxCv.h"
//#include "ofxAutoControlPanel.h"
//#include "face.h"
//#include "canvas.h"
//
//class testApp: public ofBaseApp {
//    
//public:
//        //   virtual void setup();
//        //    testApp();
//        //    ~testApp();
//    void setup();
//
//    void update();
//    void draw();
//    
//    void setupType();
//    void reset();
//    void updateCamera();
//    void configure();
//    int numberOfCanvases();
//    void updateConditional();
//    
//    //Add uses contour finder to gen the poly line
//    void add(ofVec3f& _pos, ofImage& _map);
//    ofxCv::ContourFinder contourFinder;
//    
//    void saveHomography();
//    bool loadHomography( string * path );
//    void updateHomography();
//    bool movePoint(vector<ofVec2f>& points, ofVec2f point);
//    
//    vector<ofVec2f> destination;
//    vector<ofVec2f> source;
//    ofVec2f* curPoint;
//        //ofCanvas tempCanvas;
//    bool loadMap(string * path);
//    void parseMap(ofImage * map);
//
//    // Canvas frame states
//    bool saveImage;
//    bool isConfigCanvases;
//    float rotation;
//
//    ofVec3f skew;
//    cv::Mat homography;
//    
//    ofFbo screen;
//    
//    vector<ofVec2f> drawnPoints;
//    
//        // Setup declarations
//    vector<ofVec3f> points;
//    ofTrueTypeFont raleway;
//    void setupPanel();
//    ofxAutoControlPanel panel;
//    ofImage thresh;
//    ofImage bgThresh;
//    
//    int panelWidth;
//    bool debug;
//    
//    float threshold;
//    ofVideoGrabber cam;
//    cv::Mat currentFrame;
//    ofImage newFrame;
//    
//    //Face tracking stuff
//    ofImage gray, graySmall;
//    cv::CascadeClassifier classifier;
//    vector<cv::Rect> objects;
//    float scaleFactor;
//    
//
//    
//    
//    
//    
//    
//    // Methods and variables to track
//    // and smooth face rec
//    void filterFace(cv::Rect* objects);
//    ofPolyline getContour(ofImage * map);
//    void delegateToCanvas(ofImage _face, int x, int y, int w, int h);
//    vector<ofCanvas*> canvases; // Holds canvases
//    vector<ofFace*> faces; // Holds ALL ofFace obj
//    vector<ofFace*> trackedFaces; // Holds temp faces to be included in main
//    ofImage * map;
//    ofImage * mapCopy;
//    ofPolyline * poly;
//    int faceSmoothing;
//    
//    
//    
//    
//        //Events
//    void mousePressed( int x, int y, int button);
//    void mouseDragged( int x, int y, int button);
//    void mouseReleased( int x, int y, int button);
//    void keyPressed(int key);
//    
//private:
//    
//        // Homography state
//    bool isConfigHomograph;
//    bool saveMatrix;
//    bool loadMatrix;
//    bool movingPoint;
//    bool matrixReady;
//};
//#endif
