﻿#pragma once
#include <cassert>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <functional>
#include <array>
#include <algorithm>
#include <limits>
#include <type_traits>
#include <string>
#include <iostream>

#ifdef _WIN32
#include <intrin.h>     // _BitScanReverse  64
#include <objbase.h>
#else
#include <uuid/uuid.h>
typedef struct _GUID {
	unsigned int   Data1;
	unsigned short Data2;
	unsigned short Data3;
	unsigned char  Data4[8];
} GUID;
#endif

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#ifndef _countof
template<typename T, size_t N>
size_t _countof(T const (&arr)[N])
{
	return N;
}
#endif

#ifndef _offsetof
#define _offsetof(s,m) ((size_t)&reinterpret_cast<char const volatile&>((((s*)0)->m)))
#endif

#ifndef container_of
#define container_of(ptr, type, member) \
  ((type *) ((char *) (ptr) - _offsetof(type, member)))
#endif



#include "xx_mempool.h"
#include "xx_list.h"
#include "xx_queue.h"
#include "xx_hashutils.h"
#include "xx_dict.h"
#include "xx_charsutils.h"
#include "xx_string.h"
#include "xx_bytesutils.h"
#include "xx_bbuffer.h"
#include "xx_guid.h"
#include "xx_guid.h"

#include "xx_mempool.hpp"
#include "xx_list.hpp"
#include "xx_queue.hpp"
#include "xx_hashutils.hpp"
#include "xx_dict.hpp"
#include "xx_charsutils.hpp"
#include "xx_string.hpp"
#include "xx_bytesutils.hpp"
#include "xx_bbuffer.hpp"