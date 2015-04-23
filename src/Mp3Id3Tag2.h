/*
 * Mp3Id3Tag2.h
 *
 *  Created on: Apr 23, 2015
 *      Author: ethan
 */

#ifndef MP3ID3TAG2_H_
#define MP3ID3TAG2_H_

// Id tag at beginning of file
typedef struct{
	char		tag_id[3];		//0-2	Normally "ID3"			3 bytes
	char		version;		//3-4	Tag version				2 bytes
	char		revision;
	char		flags;			//5		Flags
	int			size;			//6-9	Size of Tag Message
} __attribute__((packed)) Mp3Id3Tag1;



typedef struct{
	char data[10];
} Mp3Id3Tag2Data;

class Mp3Id3Tag2{
public:
	char tag_id[3];
	short version;
	short revision;
	short flags;
	int size;

	Mp3Id3Tag2();
	Mp3Id3Tag2(Mp3Id3Tag2Data d);
	~Mp3Id3Tag2();
};

#endif /* MP3ID3TAG2_H_ */
