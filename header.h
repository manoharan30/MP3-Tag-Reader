/***************************************************************************************************************************************************
*Author         :MANOHARAN BALAKRISHNAN
*Date           :02/08/2024
*File           :view.h
*Title          :Header file for enums and function prototypes.
*Description    :This header files contains the function prototypes and enums which requires to edit and view the properties of the mp3 file.
****************************************************************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef unsigned int uint;                      //aliasing unsigned integer into uint.

typedef enum                                    //enum for return values.
{
    success,                                    //return 0 for success.
    failure                                     //return 1 for failure.
} Status;



//function prototype to read and validate the files passed through CLA.
Status read_and_validate(FILE *,char *);  
//function prototype to verify the version of the mp3 file.            
Status version_verification(FILE *,char *); 
//function prototype to view the properties of mp3 file.            
Status view_mp3(FILE *); 
//function prototype to edit the properties of mp3 file.                              
Status edit_mp3(FILE *,char *,char*);  
//function prototype to convert bigendian to littlendian.                                              
uint bigEndianToLittleEndian(uint);      
//function prototype to convert littlendian to bigendian.              
uint little_to_big_endian(uint);  
//function prototype to copy the contents of the tags.                   
void copy_content(FILE *,FILE *,char*,uint,uint); 
//function prototype to edit the specific property of the mp3 file.      
void edit_content(FILE *,FILE *,char*,uint,char*); 
//function prototype to copy the remaining contents of the file after editing the desired content of the mp3 file.     
void copy_remaining_data(FILE *,FILE *); 
//function prototype to print information about passing CLA.               
void print_info();