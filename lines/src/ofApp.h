#pragma once

#include "ofMain.h"
#include "tori.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		ofEasyCam cam;
		ofLight light;
		ofPlanePrimitive plane;
		ofBoxPrimitive tiles[20][5];
		ofBoxPrimitive tilesR[20][5];
		ofBoxPrimitive tilesB[20][5];
		ofBoxPrimitive tilesF[20][5];

		int numberOfTarget = 512;
		vector<ofPoint> noiseSeeds;
		vector<deque<ofPoint>> logs;

		// line
		vector<glm::vec3> glitchColors;

		ofSoundPlayer soundPlayer;
		float speedX;
		float speedY;
		float timingE;
		float angle;
		bool bOrbit, bRoll;
		float angleH, roll, distance;
		float angleV = -9.0f;
		int centerLineWidth[30];
		int linesSize = 30;
		ofMaterial tileMaterial;
};
