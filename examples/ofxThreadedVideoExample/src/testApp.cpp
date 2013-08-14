#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofSetLogLevel(OF_LOG_VERBOSE);

    // uncomment to see the command queue logging
    //video1.setVerbose(true);
    //video2.setVerbose(true);
    
    files.allowExt("mov");
    files.listDir("/Users/gameover/Desktop/DeepDataTest/ANIME60"); // put a video path here with several video files in a folder

    // ofxThreadedVideo is asynchronous - ie., it executes all commands
    // on a background thread. However it now implements a FIFO queue for
    // commands - this means you can call any 'setting' command before you
    // you know the movie has loaded, as ofxThreadedVideo guarantees these
    // will be executed in order. But be careful with this!! For instance
    // you can't call video1.setFrame(ofRandom(video1.getNumTotalFrames())
    // unless you are sure the movie is loaded.
    
    video1.loadMovie(files.getPath(ofRandom(files.numFiles())));
    video1.play();
    
    video2.loadMovie(files.getPath(ofRandom(files.numFiles())));
    video2.play();
    
    ofBackground(0, 0, 0);
    
    ofAddListener(video1.threadedVideoEvent, this, &testApp::threadedVideoEvent);
    ofAddListener(video2.threadedVideoEvent, this, &testApp::threadedVideoEvent);
}

//--------------------------------------------------------------
void testApp::update(){
    video1.update();
    video2.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255, 255, 255);
    video1.draw(0, 0, video1.getWidth(), video1.getHeight());
    video2.draw(video1.getWidth(), 0, video2.getWidth(), video2.getHeight());

    ofSetColor(0, 255, 0);
    int duration1 = video1.getDuration();
    int duration2 = video2.getDuration();
    ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate()) + " duration vid1: " + ofToString(duration1) + " duration vid2: " + ofToString(duration2), 20, ofGetHeight() - 20);
}

//--------------------------------------------------------------
void testApp::threadedVideoEvent(ofxThreadedVideoEvent & event){
    ofLogVerbose() << "VideoEvent: " << event.eventTypeAsString << " for " << event.path;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    switch (key) {
        case '<':
        case ',':
            video1.loadMovie(files.getPath(ofRandom(files.numFiles())));
            video1.play();
            break;
        case '>':
        case '.':
            video2.loadMovie(files.getPath(ofRandom(files.numFiles())));
            video2.play();
            break;
        case '?':
        case '/':
            video1.loadMovie(files.getPath(ofRandom(files.numFiles())));
            video1.play();
            video2.loadMovie(files.getPath(ofRandom(files.numFiles())));
            video2.play();
            break;
        case 'p':
            video1.setPaused(!video1.isPaused());
            break;
        case OF_KEY_LEFT:
            video1.firstFrame();
            break;
        case OF_KEY_RIGHT:
            video1.setFrame(video1.getTotalNumFrames());
            break;
        case OF_KEY_UP:
            video1.setSpeed(video1.getSpeed() + 0.2);
            break;
        case OF_KEY_DOWN:
            video1.setSpeed(video1.getSpeed() - 0.2);
            break;
        default:
            break;
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
    video1.setFrame(video1.getTotalNumFrames() * (float)x/ofGetWidth());
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
