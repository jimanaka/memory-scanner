/////////////////////////////////////////////////////////////////////////////////
//           University of Hawaii, College of Engineering
/// @brief   Lab03a - memscanner - EE 491 - Spr 2022
///
/// @file    bounded-memory-scan.c
/// @version 1.0 
///
/// memscan - Scans /proc/self/maps, prints the mapped memory regions, and counts the number of 'A's in the mapped memory region. 
///
/// @author Jake Imanaka   <jimanaka@hawaii.edu>
/// @date   1_02_2022
///
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bounded-memory-scan.h"
#include "memscan.h"

void bounded_memory_scan(struct sections* sectionArr[], size_t sectionArrLen){

   // loops over each section i sectionArr
   for(int i = 0; i < sectionArrLen; i++)
   {

      // storing start and end addresses
      char* addressStart = sectionArr[i]->addressStart;
      char* addressEnd = sectionArr[i]->addressEnd;
      
      // skipping vvar section
      if(strcmp(sectionArr[i]->pathName, "[vvar]") == 0) continue;

      // checking if memory section is readable
      if(sectionArr[i]->permissions[0] == 'r'){

         // looping over entire memory section
         while(addressStart < addressEnd)
         {

            // incrementing the section's ACount if the byte is == 'A'
            if(*addressStart == 'A') sectionArr[i]->ACount += 1;
            sectionArr[i]->bytes += 1;
            addressStart += 1;
         }  
      }
   }
}
