/*
 * Mp3SideInfo.h
 *
 *  Created on: Apr 23, 2015
 *      Author: ethan
 */

#ifndef MP3SIDEINFO_H_
#define MP3SIDEINFO_H_

/*
 * Below are all of the constants for Single Channel side info parsing
 */
#define SINGLE_MAIN_DATA_BEGIN_MASK				0xFF80		// 9 (bytes 1-2)	11111111 10000000
#define SINGLE_PRIVATE_BITS_MASK				0x7C		// 5 (byte 2)		01111100
#define SINGLE_SCFSI_MASK						0x03C0		// 4 (bytes 2-3)	00000011 11000000

/*
 * Granule One
 */
#define SINGLE_GRAN1_PART2_3_LENGTH_MASK		0x3FFC		// 12 (bytes 3-4)	00111111 11111100
#define SINGLE_GRAN1_BIG_VALUES_MASK			0x03FE		// 9 (bytes 4-5)	00000011 11111110
#define SINGLE_GRAN1_GLOBAL_GAIN_MASK			0x01FE		// 8 (bytes 5-6)	00000001 11111110
#define SINGLE_GRAN1_SCALEFAC_COMPRESS_MASK		0x01E0		// 4 (bytes 6-7)	00000001 11100000
#define SINGLE_GRAN1_WINDOW_SWITCHING_MASK		0x10		// 1 (byte 7)		00010000

// Normal Block Data
#define SINGLE_GRAN1_TABLE_SELECT_MASK			0x0FFFE0	// 15 (byte 7-9)	00001111 11111111 11100000
#define SINGLE_GRAN1_REGION0_COUNT_MASK			0x1E		// 4 (byte 9)		00011110
#define SINGLE_GRAN1_RAGION1_COUNT_MASK			0x01C0		// 3 (byte 9-10)	00000001 11000000

// Flags
#define SINGLE_GRAN1_PREFLAG_MASK				0x20		// 1 (byte 10) 		00100000
#define SINGLE_GRAN1_SCAlEFAC_SCALE_MASK		0x10		// 1 (byte 10) 		00010000
#define SINGLE_GRAN1_COUNT1TABLE_SELECT_MASK	0x08		// 1 (byte 10) 		00001000

/*
 * Granule Two
 */
#define SINGLE_GRAN2_PART2_3_LENGTH_MASK		0x07FF80	// 12 (bytes 10-12)	00000111 11111111 10000000
#define SINGLE_GRAN2_BIG_VALUES_MASK			0x7FC0		// 9 (bytes 12-13)	01111111 11000000
#define SINGLE_GRAN2_GLOBAL_GAIN_MASK			0x3FC0		// 8 (bytes 13-14)	00111111 11000000
#define SINGLE_GRAN2_SCALEFAC_COMPRESS_MASK		0x3C		// 4 (byte 14)		00111100
#define SINGLE_GRAN2_WINDOW_SWITCHING_MASK		0x02		// 1 (byte 14)		00000010

// Normal Block Data
#define SINGLE_GRAN2_TABLE_SELECT_MASK			0x01FFFC	// 15 (bytes 14-16)	00000001 11111111 11111100
#define SINGLE_GRAN2_REGION0_COUNT_MASK			0x03C0		// 4 (bytes 16-17)	00000011 11000000
#define SINGLE_GRAN2_RAGION1_COUNT_MASK			0x38		// 3 (byte 17)		00111000

// Flags
#define SINGLE_GRAN2_PREFLAG_MASK				0x04		// 1 (byte 17)		00000100
#define SINGLE_GRAN2_SCAlEFAC_SCALE_MASK		0x02		// 1 (byte 17)		00000010
#define SINGLE_GRAN2_COUNT1TABLE_SELECT_MASK	0x01		// 1 (byte 17)		00000001

// (17 bytes) Used to read in single channel mono side data
typedef struct{
	unsigned char data[17];
} MONO_DATA;

// (32 bytes) Used to read in all other side data
typedef struct{
	unsigned char data[32];
} OTHER_DATA;

// Granule data
typedef struct{
	unsigned short part2_3_length;	//length of data in main_data
	unsigned short big_values;		// TODO
	unsigned char global_gain;		// TODO
	unsigned char scalefac_compress;// TODO
		unsigned char slen1;		// TODO
		unsigned char slen2;		// TODO
	bool window_switching_flag;		// TODO
	unsigned char block_type;		// TODO
	bool mixed_block_flag;			// TODO
	unsigned int table_select;		// TODO
	unsigned short subblock_gain;	// TODO
	unsigned short region0_count;	// TODO
	unsigned short region1_count;	// TODO
	bool preflag;					// TODO
	bool scalefac_scale;			// TODO
	bool count1table_select;		// TODO
} GRANULE;

//TODO
class Mp3SideInfo {
public:
	int main_data_begin; // how many bytes before the header the main data can be found at
	char private_bits; //
	char scfsi; // scalefactor selection information
	GRANULE g1;
	GRANULE g2;

	Mp3SideInfo();
	Mp3SideInfo(MONO_DATA dat);
	Mp3SideInfo(OTHER_DATA dat);
	virtual ~Mp3SideInfo();
};

#endif /* MP3SIDEINFO_H_ */
