#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(239);
    ofSetColor(39);
    this->font.loadFont("fonts/HiraginoSans.ttf", 28, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    ofRotateX(ofGetFrameNum() * 0.25 * sin(ofGetElapsedTimef() * 0.1));
    ofRotateY(ofGetFrameNum() * 0.5);
    for (int i = 0; i < 1000; i++) {
        ofPushMatrix();
        auto location = glm::vec3(ofRandom(-ofGetWidth(), ofGetWidth()), ofRandom(-ofGetHeight(), ofGetHeight()), ofRandom(-720, 720));
        ofTranslate(location);
        ofRotateX(ofMap(ofNoise(ofRandom(10000), ofGetFrameNum() * 0.005), 0, 1, -180, 180));
        ofRotateY(ofMap(ofNoise(ofRandom(10000), ofGetFrameNum() * 0.005), 0, 1, -180, 180));
        ofRotateZ(ofMap(ofNoise(ofRandom(10000), ofGetFrameNum() * 0.005), 0, 1, -180, 180));
        char noise_value = ofMap(ofNoise(location.x * 0.008, location.y * 0.008, location.z * 0.008, ofGetFrameNum() * 0.004), 0, 1, 'D', 'Z');
        this->font.drawString({ noise_value }, -14, -14);
        ofPopMatrix();
    }
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
