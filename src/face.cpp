#include "ofMain.h"
#include "face.h"

ofFace::ofFace(ofImage _face, ofVec3f _faceLocation, ofVec3f _circleLoc, int _area)
{
    theFace = _face;
    faceLocation = _faceLocation;
    x = _circleLoc.x;
    y = _circleLoc.y;
    loc = _circleLoc;
    area = _area;
        //    x = ofRandom(0,ofGetWidth());
        //    y = ofRandom(0,ofGetHeight());
    radius = ofRandom(area*.1,area);
    scale = 1.0;
    bActive = true;
    resolution = 24;
    genCircle();
    center = ofVec3f(x,y);
    debug = false;
    age = 0;
    tween = 0.0f;
    tweenStep = 0.05;
    selected = false;
    inactiveTimer = 0;
    inactiveTimerStep = 0.05f;
    changeThresh = 15;
}

ofFace::~ofFace() 
{
    
}

void ofFace::update() {
    x = loc.x;
    y = loc.y;
    //loc = ofVec3f(x,y,0);
    distanceFromCenter = distance(loc);
    if(circle.size() <= 1) {
        genCircle();
    }
    
    if( inactiveTimer >= 1.0) {
        bActive = false;
    }
    
    if(bActive) {
        inactiveTimer += inactiveTimerStep;
    }
    
    if(tween < 1.0) tween += tweenStep;
    else if (tween > 1.0) tween = 1.0f;
    
    tweenStep += tweenStep / 2;
        //center = ofPoint(x,y);
    age += 1;
}

void ofFace::scaleToMap(ofImage * map) {
    // Should be full sized to help users spot their own face, which will
    // help in connecting them to the piece.
    if(bActive) { 
        scale = 1.0;
        return;
    }
        //    scale = ofClamp(-(center.distanceSquared(loc) / center.x)-1, 0, 1.0);
//    if(&map == NULL) return;
//    if(map->width < 1) return;
//    int index = x + (y*map->width);
//    if (index < 5) return;
//        // ofLog() << "Index: " << ofToString(index);
//    if(map->getPixelsRef().size() < 5) return;
//
//    if(index < map->getPixelsRef().size()) {
//        int color = map->getPixelsRef()[index*3];
//        scale = color / (255);
//    }
//    if(scale == 0) scale = 0.1;
        //    scale = loc.squareDistance(spawnPoint);
        //    ofLog() << "scale: " << ofToString(scale);
}

void ofFace::scaleToCount(int _count) {
    scale = 1.0;
}

float ofFace::getRadius() {
    return radius * scale;
}

ofVec3f ofFace::cvFaceLocation() {
    // This might be better suited with a scale factor in future?
    return faceLocation;
}

void ofFace::updateFace(ofImage _face, ofVec3f _newLocation) {
    //I should have some kind of checking here, or something.
    if(inactiveTimer < 1.0f) {
        inactiveTimer -= inactiveTimerStep;
        theFace = _face;  
        faceLocation = _newLocation;
    }
}

bool ofFace::isActive() {
    return bActive;
}

bool ofFace::isWithinRange(ofVec3f & _difference) {
    if(!bActive) return false;
    else if(faceLocation.squareDistance(_difference) < changeThresh) return true;
    else return false;
}

void ofFace::draw(int _x, int _y) {
    glEnable(GL_DEPTH_TEST);

    glPushMatrix();
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
        glTranslatef(_x,_y,0.1f);
        glColor4f(1.0f,1.0f,1.0f,1.0f);
        theFace.reloadTexture();
        theFace.bind();  
        glBegin(GL_POLYGON);                  
        for(int i = 0; i < circleTex.size(); i++){  
            glTexCoord2f(circleTex[i].x, circleTex[i].y);
            glVertex2f( circle[i].x * (radius*tween)*scale,  circle[i].y * (radius*tween)*scale);  
        }  
        glEnd();  
        theFace.unbind();  
    
    if(bActive) {
        glBegin(GL_POLYGON);
        glTranslatef(_x,_y,0.0);
        glColor4f(1.0,0,0,.7);
        for(int i = 0; i < circle.size(); i++){  
            if( i > circle.size() * (1-inactiveTimer)) glColor3f(0,0,0);
            glVertex2f( circle[i].x * (radius*tween+2)*scale,  circle[i].y * (radius*tween+2)*scale);  
        }
        glColor4f(1.0f,1.0f,1.0f,1.0f);
        glEnd();
    }
    
    glPopMatrix();
    
    glDisable(GL_DEPTH_TEST);
    if(debug) {
        if(selected) {
        ofPushMatrix();
        ofTranslate(_x,_y,0.0f);
        ofScale(0.6,0.6);
            string stats;
            stats = "age: " + ofToString(age);
            ofDrawBitmapString(stats,0, 0);
            stats = "radius: " + ofToString(radius);
            ofDrawBitmapString(stats,0, 12);
            stats = "scale: " + ofToString(scale);
            ofDrawBitmapString(stats,0, 24);
            stats = "x: " + ofToString(loc.x) + " y: " + ofToString(loc.y);
            ofDrawBitmapString(stats,0, 36);
        ofPopMatrix();
        }
    }
}

void ofFace::draw() {
    ofFace::draw(x,y);
}

void ofFace::genCircle() {
    float angle = 0.0;  
    float step  = TWO_PI / (float)(resolution-1);  
    for(int i = 0; i < resolution; i++){  

        float px = cos(angle);  
        float py = sin(angle);  
        
        circle.push_back( ofPoint(px, py) );  
        
        float tx = ofMap( px, -1.0, 1.0, 0, theFace.getWidth());  
        float ty = ofMap( py, -1.0, 1.0, 0, theFace.getHeight());  
        
        circleTex.push_back( ofPoint(tx, ty) );  
        
        angle += step;  
    }  
}

float ofFace::distance(ofVec3f & point) {
    return center.squareDistance(point);
}

void ofFace::reset() {
    circle.clear();
    circleTex.clear();
}

void ofFace::remove() {
    x = -1;
    y = -1;
    center = ofPoint(-1,-1);
    radius = -1;
    theFace = ofImage();
    faceLocation = ofVec3f(-1,-1,-1);
}