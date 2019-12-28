/******************************************************************************************************************//**
 * @defgroup DynabyteSoftwareCore DynabyteSoftware Core
 * @brief Core library with generally useful utilities
 * @author Rod Leonard
 * @version 0.0.2
 * @date 2015/10/27
 * @copyright Dynabyte Software LLC, licensed under LGPL 3.0 so later
 * 
 * @details
 * This library contains a collection of C++ classes so useful, there's no reason to ever not include them as a way
 * of keeping executable size down.
 * *******************************************************************************************************************/

/**
 * @file CoreExports.h
 * This file is used to define some macros that are necessary to build dynamic libraries under Windows.  Specfically,
 * Windows compilers require that every symbol exported from a dynamic library be tagged with __declspec
 */

#pragma once
#ifdef _WIN32
#include "SDKDDKVer.h"
#define SHARED_EXPORT __declspec(dllexport)
#define SHARED_IMPORT __declspec(dllimport)
#else
#define SHARED_EXPORT
#define SHARED_IMPORT
#endif

#ifdef CORE_STATIC
#define CORE_EXPORT
#elif CORE_DYNAMIC
#define CORE_EXPORT SHARED_EXPORT
#else
#define CORE_EXPORT SHARED_IMPORT
#endif
