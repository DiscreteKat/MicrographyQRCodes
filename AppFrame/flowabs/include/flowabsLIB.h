#pragma once

#include <texture_2d.h>
#include <glsl_program.h>
#include <flowabsParam.h>
#include <flowabs.h>
#include <flowabsProp.h>

#ifdef NDEBUG
#pragma comment( lib, "flowabs.lib" )
#pragma message( "Link with flowabs.lib." )
#else
#pragma comment( lib, "flowabsd.lib" )
#pragma message( "Link with flowabsd.lib." )
#endif