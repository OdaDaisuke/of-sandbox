#pragma once

#include "ofMain.h"

#define NUM 500
#define BOX_SIZE 10

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
		ofBoxPrimitive box;
		ofSpherePrimitive sphere;
		ofEasyCam cam;
		ofLight light;
		int Yaxis;
		ofMesh mesh;
		int w, h;
		ofTrueTypeFont font;
};
