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
#include "Mp3Header.h"
#include "Mp3Id3Tag2.h"

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

int readMP3header(FILE *f, Mp3Header *h){
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

//	unsigned char* data = new unsigned char[30];
//
//	fread(data, 1, 30, f);
//
//	cout << "data: ";
//	for(int i=0 ; i<30 ; i++)
//		cout << (int)data[i] << " ";
//	cout << endl;
//
//	delete [] data;


//	//I'm currently not interested in the final state of the file pointer
//	do{//read a frame header
//		if(fread(h, 1, sizeof(Mp3Header), f)<1){//returns -1 if eof
//			return 0;
//		}
//		cout << (h->framesync & 0b11111111111) << " =? " << 0b11111111111 << endl;
//		fseek(f, 1-sizeof(Mp3Header), SEEK_CUR);
//	//verifies if the framesync bytes are wellset - if not no frame header was read: go to next file byte
//	}while((h->framesync & 0b11111111111) == 0b11111111111);

	return 1;
}

int MP3bitrate(Mp3Header h){
	int index=0;
	if( (0x03&h.mpegid)==MPEGVersion1 ){
		index = 3-h.layer;
	}else if( (0x03&h.mpegid)==MPEGVersion2 || (0x03&h.mpegid)==MPEGVersion2_5 ){
		index = (0x03&h.layer) == LAYER1 ? 3 :4 ;
	}
	return bitrates[ index + (0x0f&h.bitrateindx) * 5];
}

int main() {
	cout << "starting!" << endl;

	FILE *f;
	Mp3Header h;

	f = fopen("resources/Tenebrous.mp3", "rb");

	if(readMP3header(f, &h))
        printf("MPEGID: %d\nLAYER: %d\nBITIND: %d\nBITRATE: %d\n", 0x03&h.mpegid, 0x03&h.layer, 0x0f&h.bitrateindx , MP3bitrate(h));
    else
        printf("no, header not found.");

	cout << "done!" << endl;

	delete f;

	return 0;
}
