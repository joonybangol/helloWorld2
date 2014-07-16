#include "testApp.h"

int eraseSpeed = 1;
int threshold = 150;

bool didGetFirstFrame = false;
float cummFPS = 0;
float avrgFPS = 0;
float pElapsedTime = 0;

//--------------------------------------------------------------
void testApp::setup(){
	
	camWidth 		= 1920;	// try to grab at this size. 
	camHeight 		= 1080;
	
	//vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);
	
	videoProcessed 	= new unsigned char[camWidth*camHeight*3];
	int totalPixels = camWidth*camHeight*3;
	for (int i = 0; i < totalPixels; i++){
		videoProcessed[i] = 0;
	}
	videoTexture.allocate(camWidth,camHeight, GL_RGB);	
	videoTextureThresh.allocate(camWidth,camHeight, GL_RGB);	
}


//--------------------------------------------------------------
void testApp::update(){
	
	//ofBackground(100,100,100);
	
	vidGrabber.update();
	
	if (vidGrabber.isFrameNew()){
		didGetFirstFrame = true;

		cout << "new frame" << endl;
		
		float timeBetweenFrames = (ofGetElapsedTimeMillis() - pElapsedTime);
		cout << "time : " << timeBetweenFrames << endl;
		pElapsedTime = ofGetElapsedTimeMillis();
		
		
		int totalPixels = camWidth*camHeight*3;
		unsigned char * pixels = vidGrabber.getPixels();
		unsigned char * newPixels = vidGrabber.getPixels();
		for (int i = 0; i < totalPixels; i++){
			if(pixels[i] > threshold) newPixels[i] = 255;
			else newPixels[i] = 0;			
			videoProcessed[i] = videoProcessed[i] + newPixels[i];// - eraseSpeed;
			//if(videoProcessed[i] < 1) videoProcessed[i] = 1;
		}
		videoTexture.loadData(videoProcessed, camWidth,camHeight, GL_RGB);
		videoTextureThresh.loadData(newPixels, camWidth,camHeight, GL_RGB);
	}
	
	cout <<ofGetFrameRate()<<endl;
	cummFPS += ofGetFrameRate();
	avrgFPS = cummFPS/ofGetFrameNum();
	ofSetWindowTitle(ofToString(avrgFPS));
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(0);
	ofSetColor(255);
	ofPushMatrix();
	ofScale(1.6,1.6);
	//videoTexture.draw(20,20);
	ofPopMatrix();
	if (didGetFirstFrame){
	vidGrabber.draw(20,20,camWidth/2,camHeight/2);
	}else{
		ofSetColor(0,255,0);
		ofRect(20,20,camWidth/2,camHeight/2);	
	}
	//videoTextureThresh.draw(20,40+camHeight/3,camWidth/3,camHeight/3);
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
	// in fullscreen mode, on a pc at least, the 
	// first time video settings the come up
	// they come up *under* the fullscreen window
	// use alt-tab to navigate to the settings
	// window. we are working on a fix for this...
	
	// Video settings no longer works in 10.7
	// You'll need to compile with the 10.6 SDK for this
    // For Xcode 4.4 and greater, see this forum post on instructions on installing the SDK
    // http://forum.openframeworks.cc/index.php?topic=10343        
	if (key == 's' || key == 'S'){
		vidGrabber.videoSettings();
	}
	if (key == '-' ) eraseSpeed--;
	if (key == '=' ) eraseSpeed++;
	if (key == ',' ) threshold--;
	if (key == '.' ) threshold++;
	if (key == 'e' ) {
		int totalPixels = camWidth*camHeight*3;
		for (int i = 0; i < totalPixels; i++){
			videoProcessed[i] = 1;
		}
	}
	if (key == 'r'){
		int totalPixels = camWidth*camHeight*3;
		unsigned char * pixels = vidGrabber.getPixels();
		for (int i = 0; i < totalPixels; i++){
			videoProcessed[i] = pixels[i];//videoProcessed[i] + pixels[i];// - (unsigned char)eraseSpeed;
		}
	}
	
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
