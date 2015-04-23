/*
 * Mp3Header.h
 *
 *  Created on: Apr 23, 2015
 *      Author: ethan
 */

#ifndef MP3HEADER_H_
#define MP3HEADER_H_

#define FRAMESYNC_MASK 		0xFFE0	// Framesync									bytes 1-4
#define MPEG_VERSION_MASK 	0x18	// MPEG version id								bytes 3-4
#define LAYER_MASK 			0x6		// Layer										byte  4
#define CRC_PROTECTION_MASK 0x1		// CRC Protection								byte  4
#define BITRATE_INDEX_MASK 	0xF		// Bitrate index								byte  5
#define SAMPLE_RATE_MASK 	0xC		// Sample rate frequency index					byte  6
#define PADDING_MASK 		0x2		// Padding										byte  6
#define PRIVE_MASK 			0x1		// Private bit									byte  6
#define CHANNEL_MASK 		0xC		// Channel										byte  7
#define MODE_EXTENSION_MASK 0x3		// Mode extension (only if Joint Stereo is set)	byte  7
#define COPYRIGHT_MASK 		0x8		// Copyright									byte  8
#define ORIGINAL_MASK 		0x4		// Original										byte  8
#define EMPHASIS_MASK 		0x3		// Emphasis										byte  8

// byte		1		2		3		4		5		6		7		8
// data =	ffff,	ffff,	fffv,	vllp,	bbbb,	ssar,	ccmm,	coee
typedef struct{
	char data[8];
} Mp3HeaderData;

class Mp3Header{
public:
	short mpegid;
	short layer;
	bool protectbit;
	short bitrateindx;
	short samplefreq;
	short paddingbit;
	short privatebit;
	short channel;
	short modeext;
	bool copyright;
	bool original;
	short emphasis;

	Mp3Header();
	Mp3Header(Mp3HeaderData d);
	~Mp3Header();
};

#endif /* MP3HEADER_H_ */
