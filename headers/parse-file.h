
/////////////////////////////////////////////////////////////////////////////////
//           University of Hawaii, College of Engineering
/// @brief   Lab03a - memscanner - EE 491 - Spr 2022
///
/// @file    parse-file.h
/// @version 1.0 
///
/// memscan - Scans /proc/self/maps, prints the mapped memory regions, and counts the number of 'A's in the mapped memory region. 
///
/// @author Jake Imanaka   <jimanaka@hawaii.edu>
/// @date   01_02_2022
///
///////////////////////////////////////////////////////////////////////////////

#ifndef PARSE_FILE_H
#define PARSE_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include "memscan.h"

// parses file, stores section information in sectionArr, returns the number of sections 
size_t parse_file(FILE* fp, struct sections* sectionArr[]);

#endif
