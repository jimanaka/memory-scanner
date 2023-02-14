/////////////////////////////////////////////////////////////////////////////////
//           University of Hawaii, College of Engineering
/// @brief   Lab03a - memscanner - EE 491 - Spr 2022
///
/// @file    memscan.h
/// @version 1.0
///
/// memscan - Scans /proc/self/maps, prints the mapped memory regions, and counts the number of 'A's in the mapped memory region. 
///
/// @author Jake Imanaka   <jimanaka@hawaii.edu>
/// @date   01_02_2022
///
///////////////////////////////////////////////////////////////////////////////

#ifndef MEMSCAN_H
#define MEMSCAN_H
#define PROGRAM "memscan"

#include <stddef.h>
#include <stdint.h>

// represents a mapped section of memory in /proc/self/maps
struct sections {
   char*     addressStart;    // start address of the memory section
   char*     addressEnd;      // end address of the memory section
   char*     permissions;     // permissions of the memory section
   char*     offset;          // file offset
   uint32_t  deviceMajor;     // major device number
   uint32_t  deviceMinor;     // minor device number
   uint32_t  inode;           // inode number
   char*     pathName;        // path name of memory section
   size_t    ACount;          // count of 'A's
   size_t    bytes;           // number of bytes in the section
};

#endif
