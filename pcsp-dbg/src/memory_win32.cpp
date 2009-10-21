/*
This file is part of pcsp.

pcsp is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

pcsp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with pcsp.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "stdafx.h"
#include <windows.h>
#include "memory.h"

#define PAGE64K_ALIGN(x) ((x + 65535) & ~65535)

void *Memory::pointer = 0;

static HANDLE psp_memory_handle;

__forceinline void *map_view(unsigned int address, unsigned int offset, unsigned int size)
{
    return ::MapViewOfFileEx(psp_memory_handle, FILE_MAP_READ|FILE_MAP_WRITE, 0, offset, size, (LPVOID)(reinterpret_cast< unsigned int >(Memory::pointer) + address));
}

__forceinline void *map_view(unsigned int size)
{
    return ::VirtualAlloc((LPVOID)0, size, MEM_RESERVE, PAGE_NOACCESS);
}

__forceinline void unmap_view()
{
    ::VirtualFree((LPVOID)Memory::pointer, 0, MEM_RELEASE);
}

static bool mapped_buffer(unsigned int address, unsigned int times, unsigned int offset, unsigned int size)
{
    if (!(size & -65536)) // geez! windows has a pretty annoying restriction about the size of a virtual page
    {
        unsigned int total = times * size;
        size = 65536;
        times = (total + 65535) / 65536;
    }

    void *buffer = map_view(address, offset, size);

	if (!buffer)
	{
		return false;
	}

	for (unsigned int i = 1; i < times; ++i)
	{
		if (!map_view((address += size), offset, size))
		{
			return false;
		}
	}

	return true;
}


static bool unused_buffer(unsigned int start, unsigned int end)
{
	// map a mirror of 64KB pages to eat read/write in "unmapped" memory instead of raising an exception
	u32 address = PAGE64K_ALIGN(start);
	u32 times = (end - address + 65535) / 65536;
	return mapped_buffer(address, times, PAGE64K_ALIGN(SRAM_SIZE + VRAM_SIZE + MRAM_SIZE), 65536);
}

void *Memory::reserve()
{
    psp_memory_handle = ::CreateFileMappingA(INVALID_HANDLE_VALUE, 0, PAGE_READWRITE, 0, PAGE64K_ALIGN(SRAM_SIZE + VRAM_SIZE + MRAM_SIZE + ECTX_SIZE + GARB_SIZE - 1),"pcspmemory");

	if (psp_memory_handle == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	Memory::pointer = map_view(VMEM_SIZE);

	if (!Memory::pointer)
	{
		return 0;
	}

	unmap_view();

    // map emulator context
	if (mapped_buffer(0, 1, PAGE64K_ALIGN(SRAM_SIZE + VRAM_SIZE + MRAM_SIZE + GARB_SIZE), 65536))
	{
		Memory::pointer = (void *)((char *)Memory::pointer + 65536);

		//      0×00010000      0×00004000 (16 KiB)     Scratchpad
		//      0×04000000      0×00200000 (2 MiB)      Lower video ram
		//      0×04200000      0×00200000 (2 MiB)      Upper video ram (SLIM only)
		//      0×08000000      0×02000000 (32 MiB)     Lower main ram
		//      0×0A000000      0×02000000 (32 MiB)     Upper main ram (SLIM only)

		if
		(
			true
			&& unused_buffer(0x00000000, 0x00010000)
			&& mapped_buffer(0x00010000, 1, MRAM_SIZE + VRAM_SIZE, SRAM_SIZE)
			&& unused_buffer(0x00014000, 0x04000000)
            && mapped_buffer(0x04000000, 1, MRAM_SIZE            , VRAM_SIZE)
			&& unused_buffer(0x04400000, 0x08000000)
			&& mapped_buffer(0x08000000, 1, 0                    , MRAM_SIZE)
			&& unused_buffer(0x0C000000, 0x10000000)
		)
		{
			return Memory::pointer;
		}
	}

	return 0;
}

void Memory::release()
{
	if (Memory::pointer)
	{
		char *pointer = reinterpret_cast< char * >(Memory::pointer) - 65536;

		::UnmapViewOfFile(pointer);
	}

	if (psp_memory_handle != INVALID_HANDLE_VALUE)
	{
		::CloseHandle(psp_memory_handle);
	}
}

