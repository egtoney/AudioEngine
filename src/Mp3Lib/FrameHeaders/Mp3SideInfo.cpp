/*
 * Mp3SideInfo.cpp
 *
 *  Created on: Apr 23, 2015
 *      Author: ethan
 */

#include "../FrameHeaders/Mp3SideInfo.h"

Mp3SideInfo::Mp3SideInfo() {
	// TODO Auto-generated constructor stub

}

// TODO Auto-generated constructor stub
Mp3SideInfo::Mp3SideInfo(MONO_DATA dat) {
	//----------------------------------------
	int a,b,c;

	a = ((int) dat.data[0]) << 8;
	b = (int) dat.data[1];

	main_data_begin = ( a | b ) & SINGLE_MAIN_DATA_BEGIN_MASK;

	//----------------------------------------
	private_bits = ( b ) & SINGLE_PRIVATE_BITS_MASK;

	//----------------------------------------
	a = b << 8;
	b = (int) dat.data[2];

	scfsi = ( a | b ) & SINGLE_SCFSI_MASK;

	//----------------------------------------
	a = b << 8;
	b = (int) dat.data[3];

	g1.part2_3_length = ( a | b ) & SINGLE_GRAN1_PART2_3_LENGTH_MASK;

	//----------------------------------------
	a = b << 8;
	b = (int) dat.data[4];

	g1.big_values = ( a | b ) & SINGLE_GRAN1_BIG_VALUES_MASK;

	//----------------------------------------
	a = b << 8;
	b = (int) dat.data[5];

	g1.global_gain = ( a | b ) & SINGLE_GRAN1_GLOBAL_GAIN_MASK;

	//----------------------------------------
	a = b << 8;
	b = (int) dat.data[6];

	g1.scalefac_compress = ( a | b ) & SINGLE_GRAN1_SCALEFAC_COMPRESS_MASK;

	//----------------------------------------
	g1.window_switching_flag = ( b ) & SINGLE_GRAN1_WINDOW_SWITCHING_MASK;

	//----------------------------------------
	a = b << 16;
	b = (int) dat.data[7] << 8;
	c = (int) dat.data[8];

	g1.table_select = ( a | b | c ) & SINGLE_GRAN1_TABLE_SELECT_MASK;

	//----------------------------------------
	g1.region0_count = ( c ) & SINGLE_GRAN1_REGION0_COUNT_MASK;

	//----------------------------------------
	a = c << 8;
	b = (int) dat.data[9];

	g1.region1_count = ( a | b ) & SINGLE_GRAN1_RAGION1_COUNT_MASK;

	//----------------------------------------
	g1.preflag = ( b ) & SINGLE_GRAN1_PREFLAG_MASK;

	//----------------------------------------
	g1.scalefac_scale = ( b ) & SINGLE_GRAN1_SCAlEFAC_SCALE_MASK;

	//----------------------------------------
	g1.count1table_select = ( b ) & SINGLE_GRAN1_COUNT1TABLE_SELECT_MASK;

	//----------------------------------------
	a = b << 16;
	b = (int) dat.data[10] << 8;
	c = (int) dat.data[11];

	g2.part2_3_length = ( a | b | c ) & SINGLE_GRAN2_PART2_3_LENGTH_MASK;

	//----------------------------------------
	a = c << 8;
	b = (int) dat.data[12];

	g2.big_values = ( a | b ) & SINGLE_GRAN2_BIG_VALUES_MASK;

	//----------------------------------------
	a = b << 8;
	b = (int) dat.data[13];

	g2.global_gain = ( a | b ) & SINGLE_GRAN2_GLOBAL_GAIN_MASK;

	//----------------------------------------
	g2.scalefac_compress = ( b ) & SINGLE_GRAN2_SCALEFAC_COMPRESS_MASK;

	//----------------------------------------
	g2.window_switching_flag = ( b ) & SINGLE_GRAN2_WINDOW_SWITCHING_MASK;

	//----------------------------------------
	a = b << 16;
	b = (int) dat.data[14] << 8;
	c = (int) dat.data[15];

	g2.table_select = ( a | b | c ) & SINGLE_GRAN2_TABLE_SELECT_MASK;

	//----------------------------------------
	a = c << 8;
	b = (int) dat.data[16];

	g2.region0_count = ( a | b ) & SINGLE_GRAN2_REGION0_COUNT_MASK;

	//----------------------------------------
	g2.region1_count = ( b ) & SINGLE_GRAN2_RAGION1_COUNT_MASK;

	//----------------------------------------
	g2.preflag = ( b ) & SINGLE_GRAN2_PREFLAG_MASK;

	//----------------------------------------
	g2.scalefac_scale = ( b ) & SINGLE_GRAN2_SCAlEFAC_SCALE_MASK;

	//----------------------------------------
	g2.count1table_select = ( b ) & SINGLE_GRAN2_COUNT1TABLE_SELECT_MASK;

}

Mp3SideInfo::Mp3SideInfo(OTHER_DATA dat) {
	// TODO Auto-generated constructor stub

}

Mp3SideInfo::~Mp3SideInfo() {
	// TODO Auto-generated destructor stub
}

