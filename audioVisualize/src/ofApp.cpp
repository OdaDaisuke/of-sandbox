#include "ofApp.h"

static const int PARTICLES = 1000;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofEnableDepthTest();
    ofBackground(0);
    ofSetSmoothLighting(true);
    light.setSpotlight();
    light.setPosition(0, 200, 250);
    light.enable();
    plane.set(800, 800);
    plane.setPosition(0, -150, 125);
    for (int i = 0; i < PARTICLES; i++) {
        particles[i].set(2, 8);
        particles[i].setPosition(ofRandom(-250, 250), ofRandom(-20, 0), ofRandom(-400, 0));
    }
    tori.setup();
}

//--------------------------------------------------------------
void ofApp::update() {
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    for (int i = 0; i < PARTICLES; i++) {
        light.setSpecularColor(ofColor(255, 255, 255));
	    light.setDiffuseColor(ofColor(172, 172, 172));
    	light.setAmbientColor(ofColor(39));
        ofSetColor(255);
        particles[i].draw();
    }
    ofSetColor(0);
    light.setSpecularColor(ofColor(0, 0, 0));
	light.setDiffuseColor(ofColor(0, 0, 0));
	light.setAmbientColor(ofColor(0));
    tori.draw();
    ofRotateXDeg(90);
    plane.draw();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
