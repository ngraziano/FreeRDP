/**
 * FreeRDP: A Remote Desktop Protocol Client
 * Bitmap Cache V2
 *
 * Copyright 2011 Marc-Andre Moreau <marcandre.moreau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __BITMAP_V2_CACHE_H
#define __BITMAP_V2_CACHE_H

#include <freerdp/api.h>
#include <freerdp/types.h>
#include <freerdp/update.h>
#include <freerdp/freerdp.h>
#include <freerdp/utils/stream.h>

typedef struct _BITMAP_V2_CELL BITMAP_V2_CELL;
typedef struct rdp_bitmap_cache rdpBitmapCache;

typedef void (*cbBitmapSize)(rdpUpdate* update, uint32* size);
typedef void (*cbBitmapNew)(rdpUpdate* update, rdpBitmap* bitmap);
typedef void (*cbBitmapFree)(rdpUpdate* update, rdpBitmap* bitmap);

#include <freerdp/cache/cache.h>

struct _BITMAP_V2_CELL
{
	uint32 number;
	rdpBitmap** entries;
};

struct rdp_bitmap_cache
{
	pcMemBlt MemBlt;
	pcMem3Blt Mem3Blt;
	pcCacheBitmap CacheBitmap;
	pcCacheBitmapV2 CacheBitmapV2;
	pcCacheBitmapV3 CacheBitmapV3;

	cbBitmapSize BitmapSize;
	cbBitmapNew BitmapNew;
	cbBitmapFree BitmapFree;

	uint8 maxCells;
	rdpUpdate* update;
	rdpSettings* settings;
	BITMAP_V2_CELL* cells;
};

FREERDP_API void bitmap_free(rdpBitmap* bitmap);

FREERDP_API rdpBitmap* bitmap_cache_get(rdpBitmapCache* bitmap_cache, uint8 id, uint16 index);
FREERDP_API void bitmap_cache_put(rdpBitmapCache* bitmap_cache, uint8 id, uint16 index, rdpBitmap* bitmap);

FREERDP_API void bitmap_cache_register_callbacks(rdpUpdate* update);

FREERDP_API rdpBitmapCache* bitmap_cache_new(rdpSettings* settings);
FREERDP_API void bitmap_cache_free(rdpBitmapCache* bitmap_cache);

#endif /* __BITMAP_V2_CACHE_H */
