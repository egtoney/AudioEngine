/*
 * Mp3SideInfo.h
 *
 *  Created on: Apr 23, 2015
 *      Author: ethan
 */

#ifndef MP3SIDEINFO_H_
#define MP3SIDEINFO_H_

// (17 bytes) Used to read in single channel mono side data
typedef struct{
	unsigned char data[17];
} MONO_DATA;

// (32 bytes) Used to read in all other side data
typedef struct{
	unsigned char data[32];
} OTHER_DATA;

//TODO
class Mp3SideInfo {
public:
	Mp3SideInfo();
	Mp3SideInfo(MONO_DATA dat);
	Mp3SideInfo(OTHER_DATA dat);
	virtual ~Mp3SideInfo();
};

#endif /* MP3SIDEINFO_H_ */
