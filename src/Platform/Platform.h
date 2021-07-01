#pragma once

#ifdef PLATFORM_PC
#include "PC/PlatformPC.h"

using Platform = PlatformPC;

#elif PLATFORM_ORBIS
#include "PS4/PlatformPS4.h"

using Platform = PlatformPS4;

#else

#error "Plataforma no soportada"

#endif 