/*
 * Mp3Header.cpp
 *
 *  Created on: Apr 23, 2015
 *      Author: ethan
 */

#include "Mp3Header.h"

using namespace std;

Mp3Header::Mp3Header(){
	mpegid = 0;
	layer = 0;
	protectbit = 0;
	bitrateindx = 0;
	samplefreq = 0;
	paddingbit = 0;
	privatebit = 0;
	channel = 0;
	modeext = 0;
	copyright = 0;
	original = 0;
	emphasis = 0;
}

Mp3Header::Mp3Header(Mp3HeaderData data){

}

Mp3Header::~Mp3Header(){

}
