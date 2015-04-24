/*
 * Mp3Header.cpp
 *
 *  Created on: Apr 23, 2015
 *      Author: ethan
 */

#include "../Mp3Lib/Mp3Header.h"

#include <iostream>

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
	updateDataFields(data);
}

Mp3Header::~Mp3Header(){

}

void Mp3Header::updateDataFields(Mp3HeaderData data){
	char b, c, d;

	cout << "New Data: ";

	for(int i=0 ; i<10 ; i++)
		cout << (int) data.data[i] << "\t";

	cout << endl;

	b = data.data[1];
	c = data.data[2];
	d = data.data[3];

	// byte b
	mpegid = (b & MPEG_VERSION_MASK) >> 3;
	layer = (b & LAYER_MASK) >> 1;
	protectbit = (b & CRC_PROTECTION_MASK);

	// byte c
	bitrateindx = (c & BITRATE_INDEX_MASK) >> 4;
	samplefreq = (c & SAMPLE_RATE_MASK) >> 2;
	paddingbit = (c & PADDING_MASK) >> 1;
	privatebit = (c & PRIVATE_MASK);

	// byte d
	channel = (d & CHANNEL_MASK) >> 6;
	modeext = (d & MODE_EXTENSION_MASK) >> 4;
	copyright = (d & COPYRIGHT_MASK) >> 3;
	original = (d & ORIGINAL_MASK) >> 2;
	emphasis = (d & EMPHASIS_MASK);
}

bool Mp3Header::isMono(){
	return (channel & MONO_SEL) == MONO_SEL;
}
