#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofBackground(0,0,0);
    ofEnableSmoothing();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetFrameRate(30);
    camWidth = 1280;
    camHeight = 720;
    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(30);
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(camWidth, camHeight);
    ofTrueTypeFont::setGlobalDpi(72);
    ofTrueTypeFontSettings settings("HiraginoSans.ttf", 15);
    settings.addRanges(ofAlphabet::Japanese);
    settings.addRange(ofUnicode::MathOperators);
    settings.addRange(ofUnicode::Latin1Supplement);
    font.load(settings);
    font.setLineHeight(12);
    font.setLetterSpacing(1.0);
}

//--------------------------------------------------------------
void ofApp::update() {
    ofSeedRandom(39);
    vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0xffffff);
    ofDrawCircle(100, 100, 209);
    vidGrabber.draw(0, 0, camWidth, camHeight);
    ofPixels pixels = vidGrabber.getPixels();
    for (int i = 0; i < camWidth; i += 15) {
        for (int j = 0; j < camHeight; j+= 15) {
            unsigned char r = pixels[(j * camWidth + i) * 3];
            unsigned char g = pixels[(j * camWidth + i) * 3 + 1];
            unsigned char b = pixels[(j * camWidth + i) * 3 + 2];
            std::string chars[] = {".", "鷲", "_", "+", "%", "#", "@", "一"};
            int stringDepth = r + g + b;
            int idx = 0;
            if (stringDepth > 600) {
                idx = 0;
            } else if (stringDepth > 500) {
                idx = 1;
            } else if (stringDepth > 400) {
                idx = 2;
            } else if(stringDepth > 300) {
                idx = 3;
            } else if(stringDepth > 200) {
                idx = 4;
            } else if(stringDepth > 100) {
                idx = 5;
            } else if(stringDepth > 50) {
                idx = 6;
            } else {
                idx = 7;
            }
            std::string s = chars[idx];
            font.drawString(s, 10 + i, 10 + j);
        }
    }
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
