#pragma once

#include "base_event.h"
const int INIT = 5;

namespace mtm
{
	class ClonesArray
	{
	public:
		BaseEvent** clone_ptr;
		int len;
		int counter;

		/**
		* ClonesArray: constructor for the array .
		*
		* @param lenght - the length of the array.
		* @return 
		*        array .
		*/
		ClonesArray(int length = INIT);

		/**
		* ~ClonesArray: Destrucotr of the Clones array.
		* frees the array 
		*/
		~ClonesArray();

		/**
		* add: adds a pointer member to the array.
		*
		* @param pointer - pointer of the base_event that we need to add to the array.
		*/
		void add(BaseEvent* pointer);
	};
}