/*
 * PhysicalFrame.h
 *
 *  Created on: Apr 23, 2015
 *      Author: ethan
 */

#ifndef PHYSICALFRAME_H_
#define PHYSICALFRAME_H_

#include "../FrameHeaders/Mp3Header.h"
#include "../FrameHeaders/Mp3SideInfo.h"
#include <vector>

using namespace std;

class PhysicalFrame {
public:
	Mp3Header* header;
	Mp3SideInfo* side_info;
	unsigned char* data;
	int frame_size;

	PhysicalFrame();
	PhysicalFrame(Mp3Header* header, Mp3SideInfo* side_info);
	virtual ~PhysicalFrame();
	void setData(vector<unsigned char> data);
};

#endif /* PHYSICALFRAME_H_ */
