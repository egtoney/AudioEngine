/*
 * PhysicalFrame.h
 *
 *  Created on: Apr 23, 2015
 *      Author: ethan
 */

#ifndef PHYSICALFRAME_H_
#define PHYSICALFRAME_H_

#include "Mp3Header.h"

using namespace std;

class PhysicalFrame {
public:
	Mp3Header* header;
	unsigned char* data;
	int frame_size;

	PhysicalFrame();
	PhysicalFrame(Mp3Header* header);
	virtual ~PhysicalFrame();
	void setData(vector<unsigned char> data);
};

#endif /* PHYSICALFRAME_H_ */
