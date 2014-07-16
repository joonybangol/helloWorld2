#include "testApp.h"

int eraseSpeed = 10;

//--------------------------------------------------------------
void testApp::setup(){
	
	camWidth = 640;
	camHeight = 480;
	
	#ifdef _USE_LIVE_VIDEO
        vidGrabber.setVerbose(true);
        vidGrabber.initGrabber(camWidth,camHeight);
	#else
        vidPlayer.loadMovie("fingers.mov");
        vidPlayer.play();
	#endif

    colorImg.allocate(camWidth, camHeight);
	grayImage.allocate(camWidth, camHeight);
	grayBg.allocate(camWidth, camHeight);
	grayDiff.allocate(camWidth, camHeight);

	videoProcessed 	= new unsigned char[camWidth*camHeight];
	int totalPixels = camWidth*camHeight;
	for (int i = 0; i < totalPixels; i++){
		videoProcessed[i] = 0;
	}
	videoTexture.allocate(camWidth,camHeight, GL_LUMINANCE);	
	
}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(100,100,100);

    bool bNewFrame = false;

	#ifdef _USE_LIVE_VIDEO
       vidGrabber.update();
	   bNewFrame = vidGrabber.isFrameNew();
    #else
        vidPlayer.update();
        bNewFrame = vidPlayer.isFrameNew();
	#endif

	if (bNewFrame){

		#ifdef _USE_LIVE_VIDEO
            colorImg.setFromPixels(vidGrabber.getPixels(), camWidth, camHeight);
	    #else
            colorImg.setFromPixels(vidPlayer.getPixels(), camWidth, camHeight);
        #endif

        grayImage = colorImg;
		
		int totalPixels = camWidth*camHeight;
		unsigned char * pixels = grayImage.getPixels();
		for (int i = 0; i < totalPixels; i++){
			videoProcessed[i] = videoProcessed[i] + pixels[i];// - (unsigned char)eraseSpeed;
		}
		videoTexture.loadData(videoProcessed, camWidth,camHeight, GL_LUMINANCE);
		
//		if (bLearnBakground == true){
//			grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
//			bLearnBakground = false;
//		}


//		grayDiff.absDiff(grayBg, grayImage);
//		grayDiff.threshold(threshold);
	}

}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetHexColor(0xffffff);
	ofPushMatrix();
	ofScale(1.6,1.6);
	videoTexture.draw(20,20);
	ofPopMatrix();
	vidGrabber.draw(20,20,camWidth/2,camHeight/2);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	if (key == 's' || key == 'S'){
		vidGrabber.videoSettings();
	}
	if (key == '-' ) eraseSpeed--;
	if (key == '=' ) eraseSpeed++;
	if (key == 'e' ) {
		int totalPixels = camWidth*camHeight*3;
		for (int i = 0; i < totalPixels; i++){
			videoProcessed[i] = 0;
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
