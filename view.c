 /***************************************************************************************************************************************************
*Author         :MANOHARAN BALAKRISHNAN
*Date           :02/08/2024
*File           :view.c
*Title          :Contains view function.
*Description    :This file contains the function defenition for view function,it is being called by main function when user opts to view the contents of mp3 file.
****************************************************************************************************************************************************/
 #include "view.h"

/**
 * @brief view_mp3->function to view the contents of tags present in mp3 file.
 * 
 * @param fptr_mp3 mp3 file pointer which has been already opened and verified in main function. 
 * @return returns 0 upon success and 1 upon failure.
 */
Status view_mp3(FILE *fptr_mp3){
    char frame_id[5];                   //string to store the tags.
    uint size;                          //integer variable to store the size for the contents of tags.
    char *title=NULL;                   //string to store title.
    char *artist=NULL;                  //string to store the artist.
    char *album=NULL;                   //string to store album.
    char *year=NULL;                    //string to share year.
    char *music=NULL;                   //string to store music.
    char *comment=NULL;                 //string to store the comments.

    for(int i=0;i<6;i++){
        fread(frame_id,4,1,fptr_mp3);           //reading the tag into the frame id.
        frame_id[4]='\0';                       //closing the array with null character so it will become a string.
        fread(&size,4,1,fptr_mp3);              //reading the tag content sixe from the file pointer.
        size=bigEndianToLittleEndian(size);     //converting the size fetched from the file from big indian to littel endian.
        fseek(fptr_mp3,3,SEEK_CUR);             //skipped 3 bytes by using fseek inbuilt function.
        if(strcmp(frame_id,"TIT2")==0){         //comparing the tag with the frame id.
            title=malloc(size);                 //if tag matches allocating memmory for that string. 
            fread(title,size-1,1,fptr_mp3);     //reading the size many contents into that string.
            title[size-1]='\0';                 //closing the array with null character so it will become string.
        }
        else if(strcmp(frame_id,"TPE1")==0){
            artist=malloc(size);
            fread(artist,size-1,1,fptr_mp3);
            artist[size-1]='\0';
        }
        else if(strcmp(frame_id,"TALB")==0){
            album=malloc(size);
            fread(album,size-1,1,fptr_mp3);
            album[size-1]='\0';
        }
        else if(strcmp(frame_id,"TYER")==0){
            year=malloc(size);
            fread(year,size-1,1,fptr_mp3);
            year[size-1]='\0';
        }
        else if(strcmp(frame_id,"TCON")==0){
            music=malloc(size);
            fread(music,size-1,1,fptr_mp3);
            music[size-1]='\0';
        }
        else if (strcmp(frame_id,"COMM")==0){
            comment=malloc(size);
            fread(comment,size-1,1,fptr_mp3);
            comment[size-1]='\0';
        }
    }
    printf("\n-------------------------------------------------------------------------------------------------------------------------------------------\n\n");
    printf("%-10s : %s\n","TITLE",title);       //printing title.
    printf("%-10s : %s\n","ARTIST",artist);     //printing artist.
    printf("%-10s : %s\n","ALBUM",album);       //printing album.
    printf("%-10s : %s\n","YEAR",year);         //printing year.
    printf("%-10s : %s\n","MUSIC",music);       //printing music.
    printf("%-10s : %s\n","COMMENT",comment);   //printing comments.
     printf("\n-------------------------------------------------------------------------------------------------------------------------------------------\n\n");
    return success;
}

/**
 * @brief bigEndianToLittleEndian->function to convert bigendian number to littleendian.
 * 
 * @param bigEndian an unsigned integer which is going to be converted from bigendian to littleendian.
 * @return void function(no return).
 */
uint bigEndianToLittleEndian(uint bigEndian) {                     
    unsigned int littleEndian = 0;
    littleEndian |= (bigEndian & 0x000000FF) << 24;
    littleEndian |= (bigEndian & 0x0000FF00) << 8;
    littleEndian |= (bigEndian & 0x00FF0000) >> 8;
    littleEndian |= (bigEndian & 0xFF000000) >> 24;
    return littleEndian;        //returns a littleEndian value.
}
/**
 * @brief little_to_big_eEndian->function to convert littleendian number to littlendian.
 * 
 * @param little_endian_value an unsigned integer which is going to be converted from bigendian to bigendian.
 * @return void function(no return).
 */
uint little_to_big_endian(uint little_endian_value) {               
    uint big_endian_value = 0;
    
    big_endian_value |= (little_endian_value & 0x000000FF) << 24;
    big_endian_value |= (little_endian_value & 0x0000FF00) << 8;
    big_endian_value |= (little_endian_value & 0x00FF0000) >> 8;
    big_endian_value |= (little_endian_value & 0xFF000000) >> 24;
    
    return big_endian_value;        //returns a bigendian value.
}

