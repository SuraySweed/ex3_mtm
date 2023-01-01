#include "clones_array.h"

using namespace mtm;

mtm::ClonesArray::ClonesArray(int length) :
	len(length), counter(0) {
	clone_ptr = new BaseEvent * [length];
}

ClonesArray::~ClonesArray() {
	delete[] clone_ptr;
}

void ClonesArray::add(BaseEvent* pointer) {
	if (counter == len) {
		BaseEvent** new_arr = new BaseEvent * [len + INIT];
		for (int i = 0; i < counter; i++) {
			new_arr[i] = clone_ptr[i];
		}
		delete[] clone_ptr;
		clone_ptr = new_arr;
		len = len + INIT;
	}
	clone_ptr[counter] = pointer;
	counter++;
}