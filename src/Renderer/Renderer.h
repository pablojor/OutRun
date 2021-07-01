#pragma once

#ifdef PLATFORM_PC
#include "PC/RendererPC.h"

using Renderer = RendererPC;

#elif PLATFORM_ORBIS
#include "PS4/RendererPS4.h"

using Renderer = RendererPS4;

#else

#error "Plataforma no soportada"

#endif 

