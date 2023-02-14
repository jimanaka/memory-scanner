/////////////////////////////////////////////////////////////////////////////////
//           University of Hawaii, College of Engineering
/// @brief   Lab03a - memscanner - EE 491 - Spr 2022
///
/// @file    parse-file.c
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
#include <string.h>
#include "memscan.h"

// converts string to 8 bit flag.  Used in previous version but I'm keeping it in in case I need to use it later
uint8_t string_to_perms(char* buildstring){
   size_t len = strlen(buildstring);
   uint8_t ret = 0;
   for(int i = 0; i < len; i++)
   {
      if(buildstring[i] != '-') ret = (ret << 1) | 1; 
      else ret = ret << 1;
   }
   return ret;
}

// parses /proc/self/maps, fills in sectionArr with section info, returns number of sections
size_t parse_file(FILE* fp, struct sections* sectionArr[]){

   // enum representing the different inline states for the state machine
   enum posState{addressStart, addressEnd, permissions, offset, deviceMajor, deviceMinor, inode, pathName, newline} position = newline;
   char readchar;                            // char read from file
   const size_t BUILD_STRING_LEN = 256;      // length of the buildable string created from readchar
   char buildstring[BUILD_STRING_LEN];       // buildable string representing each inline section
   bzero(buildstring, BUILD_STRING_LEN);     // zero'ing out buildstring buffer
   size_t i = 0;                             // iterator to keep track of sectionArr index

   // state machine reading file char by char
   while((readchar = fgetc(fp)) != EOF)
   {
      
      // malloc a new section if starting a new line
      if(position == newline) {
         sectionArr[i] = (struct sections*)malloc(sizeof(struct sections));
         position = addressStart;
      }

      // determining what to do with readchar
      switch (readchar)
      {
         case '-':
            // store addressStart and change position to address end if currently at addressStart
            if(position == addressStart){
               sectionArr[i]->addressStart = (char*)strtol(buildstring, NULL, 16);
               position = addressEnd;
               bzero(buildstring, BUILD_STRING_LEN);
            // else cat readchar to buildstring
            } else {
               strncat(buildstring, &readchar, 1);
            }
            break;
         case ' ':
            // store addressEnd and change position to permissions if currently at addressEnd
            if(position == addressEnd){
               sectionArr[i]->addressEnd = (char*)strtol(buildstring, NULL, 16);
               position = permissions;
               bzero(buildstring, BUILD_STRING_LEN);

            } else if (position == permissions){
               // store permissions and change position to offset if currently at permissions
               sectionArr[i]->permissions = (char*)malloc(5);
               strcpy(sectionArr[i]->permissions, buildstring);
               sectionArr[i]->permissions[4] = 0;
               position = offset;
               bzero(buildstring, BUILD_STRING_LEN);

            } else if (position == offset){
               // store offset and change position to deviceMajor if currently at offset
               sectionArr[i]->offset = (char*)strtol(buildstring, NULL, 16);
               position = deviceMajor;
               bzero(buildstring, BUILD_STRING_LEN);

            } else if (position == deviceMinor) {
               // store deviceMinor and change position to inode if currently at deviceMinor
               sectionArr[i]->deviceMinor = (uint32_t)strtol(buildstring, NULL, 16);
               position = inode;
               bzero(buildstring, BUILD_STRING_LEN);

            } else if (position == inode){
               // store inode and change position to pathName if currently at inode
               sectionArr[i]->inode = (uint32_t)strtol(buildstring, NULL, 16);
               position = pathName;
               bzero(buildstring, BUILD_STRING_LEN);
            }
            break;
         case ':':
            // store deviceMajor and change position to deviceMinor if currently at deviceMajor
            if(position == deviceMajor){
               sectionArr[i]->deviceMajor = (uint32_t)strtol(buildstring, NULL, 16);
               position = deviceMinor;
               bzero(buildstring, BUILD_STRING_LEN);
            }
            break;
         case '\n':
            // storing pathname at the end of the line and changing position to newline
            sectionArr[i]->pathName = (char*)malloc(strlen(buildstring) + 1);
            memcpy(sectionArr[i]->pathName, buildstring, strlen(buildstring) + 1);
            position = newline;
            bzero(buildstring, BUILD_STRING_LEN);
            i++;
            break;
         default:
            // cats readchar to buildstring if not changing states/positions.  At each position change buildstring should hold a section element as a string.
            strncat(buildstring, &readchar, 1);
            break;
      }
   }
   
   // return i, the number of sections read
   return i; 

}
