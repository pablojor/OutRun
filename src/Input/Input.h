#pragma once

#ifdef PLATFORM_PC
#include "PC/InputPC.h"

using Input = InputPC;

#elif PLATFORM_ORBIS
#include "PS4/InputPS4.h"

using Input = InputPS4;

#else

#error "Plataforma no soportada"

#endif 

