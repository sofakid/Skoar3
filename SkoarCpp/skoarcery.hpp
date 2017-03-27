#pragma once

using namespace std;

// if this is enabled, all allocations of tokes, noads, skoarpuscles, koars, fairies, etc will be counted. 
// we define it as 1 for debug builds, 0 for release.

#ifdef DEBUG
#define SKOAR_DEBUG_MEMORY 1
#else
#ifdef _DEBUG
#define SKOAR_DEBUG_MEMORY 1
#else
#define SKOAR_DEBUG_MEMORY 0
#endif
#endif


#include <string>
#include <list>
#include <regex>
#include <map>
#include <set>
#include <vector>
#include <exception>

#include <memory>
#include <typeinfo>
#include <type_traits>
#include <functional>

#include "logging.hpp"