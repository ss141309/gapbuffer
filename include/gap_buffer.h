/* This file is part of gapbuffer.

gapbuffer is free software: you can redistribute it and/or modify it under the terms of the GNU
General Public License as published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

gapbuffer is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
Public License for more details.

You should have received a copy of the GNU General Public License along with gapbuffer. If not, see
<https://www.gnu.org/licenses/>. */

#pragma once

#include <stdbool.h>

#include "s8.h"
#include "utils.h"

typedef struct GapBuffer GapBuffer;

bool GapBuffer_new(GapBuffer **buffer, size req_size);
void GapBuffer_free(GapBuffer *buffer);
bool GapBuffer_insert(GapBuffer **buffer, const s8 string, usize position);
bool GapBuffer_delete(GapBuffer *buffer, usize position, size bytes);
bool GapBuffer_replace(GapBuffer **buffer, const s8 string, usize position);
s8 GapBuffer_getBufferData(GapBuffer *buffer);
