#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    ofEnableDepthTest();
    ofBackground(39);
    ofSetColor(39);
    ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
    soundPlayer.load("feelGoodInc.mp3");
    soundPlayer.setLoop(true);
    soundPlayer.play();
    ofSetLineWidth(1);
    // soundPlayer.setPosition(0.791f);
    soundPlayer.setPosition(0.416f);
    for (int i = 0; i < this->numberOfTarget; i++) {
        ofPoint noiseSeed = ofPoint(ofRandom(10), ofRandom(10), ofRandom(10));
        this->noiseSeeds.push_back(noiseSeed);
        deque<ofPoint> log;
        this->logs.push_back(log);
    }
    // #23049d
    // #aa2ee6
    // #ff79cd
    glitchColors.push_back(glm::vec3(63, 251, 240));
    glitchColors.push_back(glm::vec3(170, 42, 246));
    glitchColors.push_back(glm::vec3(225, 255, 255));
    plane.set(ofGetWidth(), ofGetHeight(), 10, 10);
    plane.setResolution(16, 16);
    plane.setPosition(0, -250, 0);
    plane.rotate(90, 1, 0, 0);

    ofSetSmoothLighting(true);
    light.setSpotlight();
    light.enable();
    light.setPosition(0, 50, 800);

    bOrbit = bRoll = true;
    angleH = roll = 0.0f;
    distance = 500.f;
    cam.setPosition(0, 0, 1000);
    for (int i = 0; i < 30; i++) {
        centerLineWidth[i] = 2000 + ofRandom(10 * i, 10 * i + 20);
    }
    int tileSize = 50;
    for (int i = 0; i < 20; i++) {
        for(int j = 0; j < 5; j++) {
            int x = -200 + ((tileSize + 10) * i);
            int y = -200 + ((tileSize + 10) * j);
            int z = -520;
            tiles[i][j].set(tileSize, tileSize, 4);
            tiles[i][j].setPosition(x, y, z);

            tilesR[i][j].set(tileSize, tileSize, 4);
            tilesR[i][j].setPosition(x, y, -z);
            tilesB[i][j].set(tileSize, tileSize, 4);
            tilesB[i][j].setPosition(z, y, x);
            tilesF[i][j].set(tileSize, tileSize, 4);
            tilesF[i][j].setPosition(-z, y, x);
        }
    }
    tileMaterial.setAmbientColor(ofColor(30, 63, 1));
    tileMaterial.setDiffuseColor(ofColor(20, 27, 5));
    tileMaterial.setSpecularColor(ofColor(5, 10, 35, 255));
    tileMaterial.setShininess(1);
    tileMaterial.setEmissiveColor(ofColor(37, 30, 30));
}

//--------------------------------------------------------------
void ofApp::update() {
    ofSeedRandom(39);
    float* rawSoundVolume = ofSoundGetSpectrum(1);
    float soundVolume = rawSoundVolume[0] * 300.0;
    bool isLowVolume;
    if (soundVolume < 3.8) {
        isLowVolume = true;
        soundVolume *= 0.02;
    } else {
        isLowVolume = false;
        soundVolume *= 0.95;
    }
    for (int i = 0; i < 20; i++) {
        for(int j = 0; j < 5; j++) {
            if (soundVolume < 3.7) {
                float rX = (float)(i + j) * 7.0 * timingE + soundVolume;
                float rZ = (float)(i + j) * 8.0 * timingE + soundVolume;
                float rY = ofRandom(0, 42) + (float)(i + j) * 5.0 * timingE + soundVolume;
                int idxShine = ((5 * i) + (10 * j)) % 155;
                if (rX > 40) {
                    tileMaterial.setShininess(((5 * i) + (10 * j)) % 5);
                    tileMaterial.setAmbientColor(ofColor(idxShine, 63, 31));
                    tileMaterial.setSpecularColor(ofColor(idxShine, 250, 125, 155));
                    tileMaterial.setDiffuseColor(ofColor(idxShine, 27, 5));
                    rX = 50;
                    rZ = 50;
                }
                if (rY > 33) {
                    tileMaterial.setAmbientColor(ofColor(idxShine, idxShine, idxShine));
                    tileMaterial.setSpecularColor(ofColor(idxShine, idxShine, idxShine, 255));
                    tileMaterial.setDiffuseColor(ofColor(idxShine, idxShine, idxShine));
                    tileMaterial.setShininess(idxShine);
                    rY = 50;
                }
                tiles[i][j].set(rX,rY + soundVolume, rZ);
                tilesR[i][j].set(rX, rY + soundVolume, rZ);
                tilesB[i][j].set(rX, rY, rZ);
                tilesF[i][j].set(rX, rY + soundVolume, rZ);
            } else {
                tiles[i][j].set((timingE * ofRandom(20, 40)) + soundVolume, ofRandom(5, 50) + timingE + soundVolume, 1);
                tilesR[i][j].set((timingE * ofRandom(20, 30)) + soundVolume, ofRandom(5, 50) + timingE + soundVolume, 1);
                tilesB[i][j].set((timingE * ofRandom(20, 60)) + soundVolume, ofRandom(5, 50) + timingE + soundVolume, 1);
                tilesF[i][j].set((timingE * ofRandom(20, 50)) + soundVolume, ofRandom(5, 50) + timingE + soundVolume, 1);
            }
        }
    }
    // 角丸に
    float seedX = ofNoise(5, ofGetFrameNum() * 0.003) * ((timingE + soundVolume) / 50.0);
    float seedY = ofNoise(5, ofGetFrameNum() * 0.003) * ((timingE + soundVolume) / 50.0);
    float seedZ = ofNoise(5, ofGetFrameNum() * 0.003) * ((timingE + soundVolume) / 50.0);
    for (int i = 0; i < this->numberOfTarget; i++) {
        float noiseX = ofNoise(this->noiseSeeds[i].x);
        float noiseY = ofNoise(this->noiseSeeds[i].y);
        float noiseZ = ofNoise(this->noiseSeeds[i].z);
        ofPoint point(ofMap(noiseX, 0, 1, -100, 100), ofMap(noiseY, 0, 1, -100, 100), ofMap(noiseZ, 0, 1, -100, 150));
        this->logs[i].push_front(point);
        while (this->logs[i].size() > 10) {
            this->logs[i].pop_back();
        }
        // 移動にeasing
        this->noiseSeeds[i].x += seedX;
        this->noiseSeeds[i].y += seedY;
        this->noiseSeeds[i].z += seedZ;
    }
    if (bOrbit) {
        angleH += 1.f;
        if (angleH > 360.f) angleH = 0.f;
    }
    if (bRoll) roll += 0.5f;
    float vFac = sin(angleV * M_PI / 180.f) * 90.f;
    cam.orbit(angleH, vFac, distance);
    linesSize += (int)(sin(timingE * 30)) * (soundVolume * 2);
}

//--------------------------------------------------------------
// TODO: render beam
void ofApp::draw(){
    this->cam.begin();
    timingE = abs(sin(ofGetElapsedTimef() * 7.34));
    int rows = 5;
    ofSetColor(255, 255, 255);
    plane.drawWireframe();
    // ffdf6b
    // ofSetColor(255, 234, 106);
    ofSetColor(255, 223, 233);
    int boxHeight = 1;
    int boxDepth = 1;
    int boxPosY = -250;
    ofBoxPrimitive box;
    ofSetColor(255, 255, 255);
    ofRotateYDeg(80);
    tileMaterial.begin();
    for (int i = 0; i < 20; i++) {
        for(int j = 0; j < 5; j++) {
            int deg = ofRandom(1, 2);
            ofRotateYDeg(deg);
            tiles[i][j].drawWireframe();
            ofRotateYDeg(-deg);

            ofRotateYDeg(deg);
            tilesR[i][j].drawWireframe();
            ofRotateYDeg(-deg);

            ofRotateYDeg(deg);
            tilesB[i][j].drawWireframe();
            ofRotateYDeg(-deg);
            tilesF[i][j].drawWireframe();
        }
    }
    tileMaterial.end();
    ofRotateYDeg(-80);
    ofSetColor(55, 55, 55);
    for (int i = 0; i < linesSize; i++) {
        box.set(centerLineWidth[i % linesSize] + ofRandom(-20, 20), boxHeight, boxDepth);
        box.setPosition(50, boxPosY, 30 + ofRandom(-200, 200));
        box.draw();
    }
    for (int i = 0; i < linesSize; i++) {
        box.set(boxDepth, boxHeight, centerLineWidth[i % linesSize] + ofRandom(-20, 20));
        box.setPosition(ofRandom(-200, 200), boxPosY, 30 + 0);
        box.draw();
    }
    for (int i = 0; i < linesSize; i++) {
        box.set(centerLineWidth[i % linesSize] + ofRandom(-20, 20), boxHeight, boxDepth);
        box.setPosition(50, boxPosY * -1, 30 + ofRandom(-200, 200));
        box.draw();
    }
    for (int i = 0; i < linesSize; i++) {
        box.set(boxDepth, boxHeight, centerLineWidth[i % linesSize] + ofRandom(-20, 20));
        box.setPosition(ofRandom(-200, 200), boxPosY * -1, 30 + 0);
        box.draw();
    }
    for (int i = 0; i < this->numberOfTarget; i++) {
        ofPushMatrix();
        int posX = i % 16;
        int posY = i % rows;
        int x = ofGetWidth() * -0.15 + (20.0 * (posX));
        int y = ofGetHeight() * -0.15 + (20.0 * (posY));
        int z = -200 + 25.0 * (i % 16);
        ofTranslate(x, y, z);
        ofNoFill();
        ofBeginShape();
        glm::vec3 currentColor = glitchColors[0];
        ofSetColor(currentColor.x * timingE, currentColor.y * timingE, currentColor.z * timingE);
        for (int l = 0; l < this->logs[i].size(); l++) {
            ofPoint basePoint = this->logs[i][l];
            ofVertex(basePoint);
        }
        ofEndShape();
        ofFill();
        ofSetColor(currentColor.x * timingE + 30, currentColor.y * timingE + 30, currentColor.z * timingE + 30);
        // 先端
        ofDrawSphere(this->logs[i][0], 2);
        ofPopMatrix();
    }
    this->cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

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
