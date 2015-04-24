//============================================================================
// Name        : AudioEngine.cpp
// Author      : Ethan Toney
// Version     : v1.0
// Copyright   : GNU GENERAL PUBLIC LICENSE Version 2
//					Please see LICENSE for a more detailed description of the license
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <vector>
#include "Mp3Header.h"
#include "Mp3Id3Tag2.h"
#include "PhysicalFrame.h"

using namespace std;

/*
 * Sources
 * 		http://blog.bjrn.se/2008/10/lets-build-mp3-decoder.html
 * 		http://www.mp3-tech.org/programmer/frame_header.html
 * 		http://cboard.cprogramming.com/c-programming/54179-reading-mp3-header.html
 * 		http://id3.org/id3v2.3.0
 *
 * Read physical frames...
 * 		look for, FF FB 78 64
 * 		or 255 251 120 100
 */

#define MPEGVersion2_5 0
#define MPEGreserved   1
#define MPEGVersion2   2
#define MPEGVersion1   3

#define LAYER1  3
#define LAYER2  2
#define LAYER3  1
#define LAYERRESERVED   0
//some macros defined by me... you can do what ever you want with these
#define BITRATEFREE 0xfffe
#define BITRATEBAD  0xffff

int bitrates[] = {
    BITRATEFREE, BITRATEFREE, BITRATEFREE, BITRATEFREE, BITRATEFREE,
    32,  32,  32,  32,    8,
    64,  48,  40,  48,   16,
    96,  56,  48,  56,  24,
    128,  64,  56,  64,  32,
    160,  80,  64,  80,  40,
    192,  96,  80,  96,  48,
    224, 112,  96, 112,  56,
    256, 128, 112, 128,  64,
    288, 160, 128, 144,  80,
    320, 192, 160, 160,  96,
    352, 224, 192, 176, 112,
    384, 256, 224, 192, 128,
    416, 320, 256, 224, 144,
    448, 384, 320, 256, 160,
    BITRATEBAD, BITRATEBAD, BITRATEBAD, BITRATEBAD, BITRATEBAD
};

//
//// Id tag at end of file
//typedef struct{
//	char    tagid  [ 3];    //0-2     3  Tag identifier. Must contain "TAG" string if Tag is valid.
//	char    name   [30];    //3-32   30  Song Name
//	char    artist [30];    //33-62  30  Artist
//	char    album  [30];    //63-92  30  Album
//	int     year   :32 ;    //93-96   4  Year
//	char    comment[30];    //97-126 30  Comment
//	char    genre  : 8 ;    //127  1  Genre
//} Mp3Id3Tag2;

bool framesyncOn(unsigned char c[2]){
	int a,b;
	a = ((int) c[0]) << 8;
	b = ((int) c[1]);

	int r = ( a | b) & FRAMESYNC_MASK;

	//cout << "framesync " << r << " ?= " << FRAMESYNC_MASK << endl;

	return r == FRAMESYNC_MASK;
}

vector<PhysicalFrame*> readMP3File(FILE *f){
	cout << "Starting to read physical frames!" << endl;

	Mp3Id3Tag2Data tag_data;

	//push file point to the beginning
	rewind(f);
	fread(&tag_data, 1, sizeof(tag_data), f);

	Mp3Id3Tag2 tag(tag_data);

	// check to see if it is a ID3 v3, since they are at the beginning
	if(tag.tag_id[0]=='I' && tag.tag_id[1]=='D' && tag.tag_id[2]=='3'){
		// skip over the ID3 v3 header tag
		fseek(f, tag.size, SEEK_CUR);
	}else{//isn't tag id3v2 - go back
		rewind(f);
	}

	vector<PhysicalFrame*> frames;
	Mp3HeaderData header_data;

	bool reading = true;
	do{
		//read a frame header
		if(fread(&header_data, 1, sizeof(header_data), f) <1 ){//returns -1 if eof
			break;
		}

		//init the header
		Mp3Header* h = new Mp3Header(header_data);

		//init the physical frame
		PhysicalFrame* frame = new PhysicalFrame(h);

		//move past the current header
		fseek(f, sizeof(header_data), SEEK_CUR);

		//read till another header is found
		vector<unsigned char> past_data;
		unsigned char curr_data[2];

		//initial read of two bytes
		if(fread(curr_data, 1, sizeof(curr_data), f) <1 )//returns -1 if eof
			break;

		//till it finds another header or reaches the end of file
		while( !framesyncOn(curr_data) ){
			//push first byte to past_data since it isn't header data
			past_data.push_back(curr_data[0]);

			//back up one byte
			fseek(f, -1, SEEK_CUR);
			//read next two bytes
			if(fread(curr_data, 1, sizeof(curr_data), f) <1 ){//returns -1 if eof
				reading = false;
				break;
			}
			//move forward two bytes
			fseek(f, 2, SEEK_CUR);
		}

		//push data to header
		frame->setData(past_data);
		frames.push_back(frame);

		//back up two bytes so that the whole header can correctly be read
		fseek(f, -2, SEEK_CUR);
	}while( reading );

	cout << "Finished reading physical frames!" << endl;

	return frames;
}

int MP3bitrate(Mp3Header* h){
	int index=0;
	if( (h->mpegid)==MPEGVersion1 ){
		index = 3-h->layer;
	}else if( (h->mpegid)==MPEGVersion2 || (h->mpegid)==MPEGVersion2_5 ){
		index = (h->layer) == LAYER1 ? 3 :4 ;
	}
	return bitrates[ index + (h->bitrateindx) * 5];
}

int main() {
	cout << "starting!" << endl;

	FILE *f;

	f = fopen("resources/Tenebrous.mp3", "rb");

	vector<PhysicalFrame*> frames = readMP3File(f);

	if(frames.size() > 0){
		printf("MPEGID: %d\nLAYER: %d\nBITIND: %d\nBITRATE: %d\n", frames[0]->header->mpegid, frames[0]->header->layer, frames[0]->header->bitrateindx , MP3bitrate(frames[0]->header));
		cout << endl;
		printf("MPEGID: %d\nLAYER: %d\nBITIND: %d\nBITRATE: %d\n", frames[1]->header->mpegid, frames[1]->header->layer, frames[1]->header->bitrateindx , MP3bitrate(frames[1]->header));
		cout << endl;
		printf("MPEGID: %d\nLAYER: %d\nBITIND: %d\nBITRATE: %d\n", frames[2]->header->mpegid, frames[2]->header->layer, frames[2]->header->bitrateindx , MP3bitrate(frames[2]->header));
	}else{
        printf("no, header not found.");
	}

	cout << "stopping!" << endl;

	for (unsigned int i=0 ; i<frames.size() ; i++){
		delete frames[i];
	}
	delete f;

	return 0;
}
