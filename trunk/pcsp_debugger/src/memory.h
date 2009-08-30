/*
* memory.h
*
*  Created on: 2 nov. 2008
*      Author: hli
*/

#ifndef EMULATOR_MEMORY_H_
#define EMULATOR_MEMORY_H_

#include "common/types.h"

//	0×00010000	0×00004000 (16 KiB)	Scratch pad
//	0×04000000	0×00200000 (2 MiB)	Lower video ram
//	0×04200000	0×00200000 (2 MiB)	Upper video ram (SLIM only)
//	0×08000000	0×02000000 (32 MiB)	Lower main ram
//	0×0A000000	0×02000000 (32 MiB)	Upper main ram (SLIM only)

#define ECTX_START 0x00000000
#define VMEM_START 0x00000000
#define SRAM_START 0x00010000
#define VRAM_START 0x04000000
#define MRAM_START 0x08000000

#define SRAM_SIZE 0x00004000
#define ECTX_SIZE 0x00010000
#define GARB_SIZE 0x00020000
#define VRAM_SIZE 0x00400000
#define MRAM_SIZE 0x04000000
#define VMEM_SIZE 0x10000000

#ifndef KB
#define KB *1024
#endif
#ifndef MB
#define MB *1024 KB
#endif
#ifndef GB
#define GB *1024 * MB
#endif

union vmem_u
{
	char b[VMEM_SIZE];
	unsigned char bu[VMEM_SIZE];
	short h[VMEM_SIZE/2];
	unsigned short hu[VMEM_SIZE/2];
	int w[VMEM_SIZE/4];
	float f[VMEM_SIZE/4];
};

union sram_u
{
	char b[SRAM_SIZE];
	unsigned char bu[SRAM_SIZE];
	short h[SRAM_SIZE/2];
	unsigned short hu[SRAM_SIZE/2];
	int w[SRAM_SIZE/4];
	float f[SRAM_SIZE/4];
};

union vram_u
{
	char b[VRAM_SIZE];
	unsigned char bu[VRAM_SIZE];
	short h[VRAM_SIZE/2];
	unsigned short hu[VRAM_SIZE/2];
	int w[VRAM_SIZE/4];
	float f[VRAM_SIZE/4];
};

union mram_u
{
	char b[MRAM_SIZE];
	unsigned char bu[MRAM_SIZE];
	short h[MRAM_SIZE/2];
	unsigned short hu[MRAM_SIZE/2];
	int w[MRAM_SIZE/4];
	float f[MRAM_SIZE/4];
};

namespace Memory
{
	extern void *pointer;

	template< typename T > static __forceinline T *addr(u32 address)
	{
		return reinterpret_cast< T * > (reinterpret_cast< u32 > (Memory::pointer)
			+ (address & (VMEM_SIZE - 1)));
	}
	static __forceinline s8 *addrb(u32 address)
	{
		return addr< s8 > (address);
	}
	static __forceinline u8 *addrbu(u32 address)
	{
		return addr< u8 > (address);
	}
	static __forceinline s16 *addrh(u32 address)
	{
		return addr< s16 > (address);
	}
	static __forceinline u16 *addrhu(u32 address)
	{
		return addr< u16 > (address);
	}
	static __forceinline u32 *addrw(u32 address)
	{
		return addr< u32 > (address);
	}
	static __forceinline f32 *addrf(u32 address)
	{
		return addr< f32 > (address);
	}

	template< typename T > static inline T &mem(u32 address)
	{
		return *addr< T > (address);
	}
	static __forceinline s8 &memb(u32 address)
	{
		return *addrb(address);
	}
	static __forceinline u8 &membu(u32 address)
	{
		return *addrbu(address);
	}
	static __forceinline s16 &memh(int address)
	{
		return *addrh(address);
	}
	static __forceinline u16 &memhu(u32 address)
	{
		return *addrhu(address);
	}
	static __forceinline u32 &memw(u32 address)
	{
		return *addrw(address);
	}
	static __forceinline f32 &memf(u32 address)
	{
		return *addrf(address);
	}

	static __forceinline vmem_u &vmem()
	{
		return mem< vmem_u > (0);
	}
	static __forceinline sram_u &sram()
	{
		return mem< sram_u > (SRAM_START);
	}
	static __forceinline vram_u &vram()
	{
		return mem< vram_u > (VRAM_START);
	}
	static __forceinline mram_u &mram()
	{
		return mem< mram_u > (MRAM_START);
	}

	template< typename T >
	struct Ptr
	{
		T *_address;

		T * const operator -> () const { return addr< T >((u32)_address); }
		T * operator -> () { return addr< T >((u32)_address); }

		operator T * const () const { return addr< T >((u32)_address); } 
		operator T * () { return addr< T >((u32)_address); }

		bool is_inside() { u32 delta = (u32)(addr< T >((u32)_address) - addr< T >(VMEM_START)); return delta < VMEM_SIZE; }

		Ptr() {}
		explicit Ptr(int address) : _address((T *)address) {}
		Ptr(Ptr< T > const &ptr) : _address(ptr._address) {}
	};

	void *reserve();
	void release();

	bool initialize();
	void finalize();
	void reset();
	bool enable_guard(bool enable);
	void enable_exceptions(bool enable);
	
	bool is_valid(u32 addr);
	
	inline bool is_reserved()
	{
		return Memory::pointer != 0;
	}
}

#endif /* EMULATOR_MEMORY_H_ */
