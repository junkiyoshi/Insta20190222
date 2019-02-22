#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	int radius_min = 15;
	int radius_max = 100;
	float deg_width = 45;
	int span = 240;

	for (int y = span * 0.5; y < ofGetHeight(); y += span) {

		for (int x = span * 0.5; x < ofGetWidth(); x += span) {

			ofPushMatrix();
			ofTranslate(x, y);

			vector<glm::vec2> vertices_top;
			vector<glm::vec2> vertices_right;
			vector<glm::vec2> vertices_bottom;
			vector<glm::vec2> vertices_left;

			float random_seed = ofRandom(720);
			for (int radius = radius_min; radius <= radius_max; radius += 1) {

				float deg_center = ofMap(ofNoise(random_seed, radius * 0.005 + ofGetFrameNum() * 0.01), 0, 1, 0, 360);

				vertices_right.push_back(glm::vec2(radius * cos((deg_center + deg_width * 0.5) * DEG_TO_RAD), radius * sin((deg_center + deg_width * 0.5) * DEG_TO_RAD)));
				vertices_left.push_back(glm::vec2(radius * cos((deg_center - deg_width * 0.5) * DEG_TO_RAD), radius * sin((deg_center - deg_width * 0.5) * DEG_TO_RAD)));

				if (radius == radius_min) {

					for (int deg = deg_center - deg_width * 0.5; deg <= deg_center + deg_width * 0.5; deg += 1) {

						vertices_bottom.push_back(glm::vec2(radius_min * cos(deg * DEG_TO_RAD), radius_min * sin(deg * DEG_TO_RAD)));
					}
				}

				if (radius == radius_max) {

					for (int deg = deg_center - deg_width * 0.5; deg <= deg_center + deg_width * 0.5; deg += 1) {

						vertices_top.push_back(glm::vec2(radius_max * cos(deg * DEG_TO_RAD), radius_max * sin(deg * DEG_TO_RAD)));
					}
				}
			}

			std::reverse(vertices_right.begin(), vertices_right.end());
			std::reverse(vertices_bottom.begin(), vertices_bottom.end());

			for (int i = 0; i < 4; i++) {

				ofRotate(90);

				ofBeginShape();
				ofVertices(vertices_top);
				ofVertices(vertices_right);
				ofVertices(vertices_bottom);
				ofVertices(vertices_left);
				ofEndShape();
			}

			ofPopMatrix();
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}