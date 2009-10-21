//#pragma once

#ifndef __GNUC__
#pragma warning(disable:4996)
#endif

#ifdef WIN32
#   define _WIN32_WINNT 0x501
#   define WINVER 0x0500
#   ifndef _WIN32_IE
#       define _WIN32_IE 0x0501       // Default value is 0x0400
#   endif
#   define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#   include <windows.h>
#   define HAS_NATIVE_FIBERS 1
#else
#   include <sys/time.h>
#   include <sys/mman.h>
#   include <sys/stat.h>
#   include <fcntl.h>
#   include <unistd.h>
#   include <cerrno>
#   include <cstring>
#   if !defined(MAP_ANONYMOUS) && defined(MAP_ANON)
#       define MAP_ANONYMOUS MAP_ANON
#   endif 
#endif

#include <process.h>
#include <tchar.h>
#include <stdio.h>



#ifndef __GNUC__
// use instrinsic for byteswapping
#pragma intrinsic(_byteswap_ulong)
#endif

#define bswap16(x) ((x)>>8 | ((x)&255)<<8)
#define bswap32(x) ((bswap16((x)>>16)&65535)|(bswap16((x)&65535)<<16))

#include <math.h>
#include <time.h>
#include <mmsystem.h>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <queue>


using namespace std;

#include "common/types.h"

