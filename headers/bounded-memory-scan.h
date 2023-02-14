/////////////////////////////////////////////////////////////////////////////////
//           University of Hawaii, College of Engineering
/// @brief   Lab03a - memscanner - EE 491 - Spr 2022
///
/// @file    bounded-memory-scan.h
/// @version 1.0
///
/// memscan - Scans /proc/self/maps, prints the mapped memory regions, and counts the number of 'A's in the mapped memory region. 
///
/// @author Jake Imanaka   <jimanaka@hawaii.edu>
/// @date   01_02_2022
///
///////////////////////////////////////////////////////////////////////////////

#ifndef BOUNDED_MEMORY_SCAN_H
#define BOUNDED_MEMORY_SCAN_H

#include <stdint.h>
#include "memscan.h"

// scans memory of each section from their start addresses to their end addresses and counts the number of 'A' bytes
void bounded_memory_scan(struct sections* sectionArr[], size_t sectionArrLen);

#endif
