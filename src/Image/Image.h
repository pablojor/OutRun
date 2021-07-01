#pragma once

#ifdef PLATFORM_PC
#include "PC/ImagePC.h"

using Image = ImagePC;

#elif PLATFORM_ORBIS
#include "PS4/ImagePS4.h"

using Image = ImagePS4;

#else

#error "Plataforma no soportada"

#endif 