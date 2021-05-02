#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    sampleRate = 44100;
    amp = 0.5;
    pan = 0.5;
    phase = 0;
    frequency = 440;
    bufSize = 256;
    ofSetFrameRate(30);
    ofBackground(32, 32, 32);

    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = 512;
    soundStream.setup(settings);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    float audioHeight = ofGetHeight() / 2.0f;
    float phaseDiff = ofGetWidth() / float(bufSize);
    ofSetColor(0, 0, 255);
    ofNoFill();
    ofSetLineWidth(2);

    ofBeginShape();
    for (int i = 0; i <bufSize; i++) {
        ofVertex(i * phaseDiff, audioHeight / 2 + lAudio[i] * audioHeight);
    }
    ofEndShape();

    ofBeginShape();
    for (int i = 0; i <bufSize; i++) {
        ofVertex(i * phaseDiff, audioHeight / 2 * 3 + rAudio[i] * audioHeight);
    }
    ofEndShape();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    waveShape += 1;
    if (waveShape > 5) {
        waveShape = 1;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    pan = (float)x / (float)ofGetWidth();
    float heightPct = (float(ofGetHeight() - y) / float(ofGetHeight()));
    frequency = 4000.0f * heightPct;
    if (frequency < 20) {
        frequency = 20;
    }
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

void ofApp::audioRequested(float* output, int bufferSize, int nChannels) {
    float sample;
    float phaseDiff;
    phaseDiff = TWO_PI * frequency / sampleRate;
    // バッファサイズ分の波形を生成
    for (int i = 0; i < bufferSize; i++) {
        phase += phaseDiff;
        while(phase > TWO_PI) {
            phase -= TWO_PI;
        }
        switch (waveShape) {
            case 1:
            // Sin波
                sample = sin(phase);
                break;
            case 2:
            // ノコギリ波
                sample = -phase / PI + 1;
                break;
            case 3:
            // 矩形波
                sample = (phase < PI) ? -1 : 1;
                break;
            case 4:
            // 三角波
                sample = (phase < PI) ? -2 / PI * phase + 1: 2 / PI * phase - 3;
                break;
            case 5:
            // ホワイトノイズ
                sample = ofRandom(-1, 1);
                break;
            default:
                sample = sin(phase);
        }
        lAudio[i] = output[i * nChannels] = sample * pan * amp;
        rAudio[i] = output[i * nChannels + 1] = sample * pan * amp;
    }
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
