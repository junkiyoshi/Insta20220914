#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofEnableDepthTest();

	this->mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	vector<float> min_distance_list;
	this->mesh.clear();

	for (int i = 0; i < 2800; i++) {

		auto vertex = glm::vec3(
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.001), 0, 1, -300, 300),
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.001), 0, 1, -300, 300),
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.001), 0, 1, -300, 300));
		this->mesh.addVertex(vertex);
		min_distance_list.push_back(20);
	}

	for (auto& vertex : this->mesh.getVertices()) {

		vertex.x = vertex.x < -150 ? -150 : vertex.x > 150 ? 150 : vertex.x;
		vertex.y = vertex.y < -150 ? -150 : vertex.y > 150 ? 150 : vertex.y;
		vertex.z = vertex.z < -150 ? -150 : vertex.z > 150 ? 150 : vertex.z;
	}


	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		for (int k = 0; k < this->mesh.getNumVertices(); k++) {

			if (i == k) { continue; }

			auto distance = glm::distance(this->mesh.getVertex(i), this->mesh.getVertex(k));
			if (distance < 20) {

				this->mesh.addIndex(i);
				this->mesh.addIndex(k);

				if (distance < min_distance_list[i]) {

					min_distance_list[i] = distance;
				}
			}
		}

		this->mesh.addColor(ofColor(255, ofMap(min_distance_list[i], 0, 20, 255, 0)));
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofRotateY(ofGetFrameNum());

	this->mesh.draw();

	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		ofSetColor(this->mesh.getColor(i));
		ofDrawSphere(this->mesh.getVertex(i), 1.5);
	}

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}