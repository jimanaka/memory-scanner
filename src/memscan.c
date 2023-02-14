/////////////////////////////////////////////////////////////////////////////////
//           University of Hawaii, College of Engineering
/// @brief   Lab03a - memscanner - EE 491 - Spr 2022
///
/// @file    memscan.c
/// @version 1.0 
///
/// memscan - Scans /proc/self/maps, prints the mapped memory regions, and counts the number of 'A's in the mapped memory region. 
///
/// @author Jake Imanaka   <jimanaka@hawaii.edu>
/// @date   01_02_2022
///
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "memscan.h"
#include "parse-file.h"
#include "bounded-memory-scan.h"

size_t parse_file( FILE* fp, struct sections* sectionArr[] );

int main(int argc, char** argv){

   // array of section structs to hold information of each mapped memory region
   size_t const SECTION_ARR_MAX = 256;
   struct sections* sectionArr[SECTION_ARR_MAX]; 
   size_t sectionArrLen = 0;

   for(int i = 0; i < SECTION_ARR_MAX; i++)
   {
      sectionArr[i] = NULL;
   }

   // pointer to /proc/self/maps
   // fopen() returns NULL and exits if the method was unable to open /proc/self/maps
   FILE* fp = NULL;
   if((fp = fopen("/proc/self/maps", "r")) == NULL) {
      fprintf(stderr, "%s: failed to open file\n", PROGRAM);
      exit(EXIT_FAILURE);
   }

   // parses /proc/self/maps, stores info of each section in sectionArr, and returns the number of sections
   sectionArrLen = parse_file(fp, sectionArr);

   // scans memory ranges for each section and counts the number of 'A's
   bounded_memory_scan(sectionArr, sectionArrLen);

   // printing information for each section in sectionArr.
   for(int i = 0; i < sectionArrLen; i++)
   {
      printf("%d:\t%p - %p\t%s\tNumber of bytes read: [%zu]\t\tNumber of 'A' is [%zu]\n",
            i,
            sectionArr[i]->addressStart,
            sectionArr[i]->addressEnd,
            sectionArr[i]->permissions,
            sectionArr[i]->bytes,
            sectionArr[i]->ACount
            );
   }
   fclose(fp);

   // freeing sectionArr and its elements
   for(int i = 0; i < sectionArrLen; i++)
   {
      free(sectionArr[i]->pathName);
      free(sectionArr[i]->permissions);
      free(sectionArr[i]);
   }

   return EXIT_SUCCESS;
}
