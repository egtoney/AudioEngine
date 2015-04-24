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
#define BITRATE_INDEX_MASK 	0xF0	// Bitrate index								byte  5
#define SAMPLE_RATE_MASK 	0xC		// Sample rate frequency index					byte  6
#define PADDING_MASK 		0x2		// Padding										byte  6
#define PRIVATE_MASK 		0x1		// Private bit									byte  6
#define CHANNEL_MASK 		0xC0	// Channel										byte  7
#define MODE_EXTENSION_MASK 0x30	// Mode extension (only if Joint Stereo is set)	byte  7
#define COPYRIGHT_MASK 		0x8		// Copyright									byte  8
#define ORIGINAL_MASK 		0x4		// Original										byte  8
#define EMPHASIS_MASK 		0x3		// Emphasis										byte  8

// byte		0			1			2			3
// data =	ffffffff,	fffvvllp,	bbbbssar,	ccmmcoee
typedef struct{
	unsigned char data[4];
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
	void updateData(Mp3HeaderData d);
};

#endif /* MP3HEADER_H_ */
