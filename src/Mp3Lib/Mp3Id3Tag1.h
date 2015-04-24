/*
 * Mp3Id3Tag1.h
 *
 *  Created on: Apr 23, 2015
 *      Author: ethan
 */

#ifndef MP3LIB_MP3ID3TAG1_H_
#define MP3LIB_MP3ID3TAG1_H_

//TODO Add mask defines

typedef struct{
	unsigned char data[16];
} Mp3Id3Tag1Data;

class Mp3Id3Tag1 {
public:
	Mp3Id3Tag1();
	virtual ~Mp3Id3Tag1();
};

#endif /* MP3LIB_MP3ID3TAG1_H_ */
