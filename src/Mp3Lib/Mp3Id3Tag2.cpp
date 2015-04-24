/*
 * Mp3Id3Tag2.cpp
 *
 *  Created on: Apr 23, 2015
 *      Author: ethan
 */

#include "../Mp3Lib/Mp3Id3Tag2.h"

using namespace std;

Mp3Id3Tag2::Mp3Id3Tag2(){
	version = 0;
	revision = 0;
	flags = 0;
	size = 0;
}

Mp3Id3Tag2::Mp3Id3Tag2(Mp3Id3Tag2Data data){
	tag_id[0] = data.data[0];
	tag_id[1] = data.data[1];
	tag_id[2] = data.data[2];

	version = (short) data.data[3];

	revision = (short) data.data[4];

	flags = (short) data.data[5];

	int a, b, c, d;
	a = data.data[6];
	b = data.data[7];
	c = data.data[8];
	d = data.data[9];

	size = a << 24 | b << 16 | c << 8 | d;

	// bit 7 of each byte is set to 0 and ignored resulting in a 28 bit long int

	a = size & 0x7f000000;
	b = size & 0x007f0000;
	c = size & 0x00007f00;
	d = size & 0x0000007f;

	size = a>>3 | b>>2 | c>>1 | d;
}

Mp3Id3Tag2::~Mp3Id3Tag2(){

}
