/***********************************************************************************************************************
 * @defgroup DynabyteSoftwareCore DynabyteSoftware Core
 * @brief Core library with generally useful utilities
 * @author Rod Leonard
 * @version 0.0.1
 * @date 2015/10/27
 * @copyright Dynabyte Software LLC, licensed under LGPL 3.0 so later
 * 
 * @details
 * This library contains a collection of C++ classes so useful, there's no reason to ever not include them as a way
 * of keeping executable size down.
 * ********************************************************************************************************************/

/**
 * @file CoreExports.h
 * This file is used to define some macros that are necessary to build dynamic libraries under Windows.  Specfically,
 * Windows compilers require that every symbol exported from a dynamic library be tagged with __declspec
 */

#pragma once
#ifdef _WIN32
#ifdef COREDYNAMIC_EXPORTS
#define CORE_EXPORT __declspec(dllexport)
#else
#ifdef COREDYNAMIC_IMPORTS
#define CORE_EXPORT __declspec(dllimport)
#else
#define CORE_EXPORT
#endif
#endif
#else
#define CORE_EXPORT
#endif