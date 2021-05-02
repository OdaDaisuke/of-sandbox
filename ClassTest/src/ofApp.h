#pragma once

#include "ofMain.h"
#include "dog.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void audioRequested(float * input, int bufferSize, int nChannels);
		ofSoundStream soundStream;
		int sampleRate;
		int bufSize;
		int waveShape;
		// 定位
		float pan;
		// 振幅(音量)
		float amp;
		// 位相
		float phase;
		// 周波数(音の高さ)
		float frequency;
		float lAudio[256];
		float rAudio[256];
};
