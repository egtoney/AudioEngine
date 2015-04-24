/*
 * PhysicalFrame.cpp
 *
 *  Created on: Apr 23, 2015
 *      Author: ethan
 */

#include <vector>
#include <string.h>
#include "Mp3Header.h"
#include "PhysicalFrame.h"

using namespace std;

PhysicalFrame::PhysicalFrame() {
	frame_size = 0;
	data = NULL;
}

PhysicalFrame::PhysicalFrame(Mp3Header* head) {
	frame_size = 0;
	data = NULL;
	header = head;
}

PhysicalFrame::~PhysicalFrame() {
	delete [] data;
	delete header;
}

void PhysicalFrame::setData(vector<unsigned char> vec){
	frame_size = vec.size();
	data = new unsigned char[frame_size];

	for(int i=0 ; i<frame_size ; i++)
		data[i] = vec[i];
}

