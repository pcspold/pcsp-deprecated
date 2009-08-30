/*
 * memory.cpp
 *
 *  Created on: 13 nov. 2008
 *      Author: hli
 */



#include <stdio.h>
#include <string.h>

#include "memory.h"


bool Memory::initialize()
{
	if (Memory::reserve() == NULL)
	{
//		fatalf(memory, "Out of memory !");
		Memory::finalize();
		return false;
	}

	return true;
}

void Memory::finalize()
{
	if (Memory::pointer)
	{
		Memory::release();
//		Log::memory.flush();
	}
}

void Memory::reset()
{
	memset((void*)Memory::mram, 0, MRAM_SIZE);
	memset((void*)Memory::vram, 0, VRAM_SIZE);
	memset((void*)Memory::sram, 0, SRAM_SIZE);
}
