/***************************************************************************************************************************************************
*Author         :MANOHARAN BALAKRISHNAN
*Date           :02/08/2024
*File           :edit.c
*Title          :To edit mp3 file tags and properties.
*Description    :This file has functions to find the tags based on user's input and the to edit that tag properties.
****************************************************************************************************************************************************/
#include"view.h"

/**
 * @brief edit_mp3->function to edit the properties of the mp3 file.
 * 
 * @param fptr_mp3 mp3 file pointer which has been already opened and verified in main functions. 
 * @param str character pointer which contains the tag of the mp3 file thats going to get deleted.
 * @param content character pointer which contains the content that is going to get replaced in the mp3 file.
 * @return 0 on success, non-zero on failure.
 */

Status edit_mp3(FILE *fptr_mp3, char* str,char* content) {
    char tag[5];                                                 //string to store tags
    char frame_id[5];                                           //String to store frame id
    uint size;
    uint csize;

    // Determine the tag based on the provided string argument
    if (strcmp(str, "-t") == 0) strcpy(tag, "TIT2");
    else if (strcmp(str, "-a") == 0) strcpy(tag, "TPE1");
    else if (strcmp(str, "-A") == 0) strcpy(tag, "TALB");
    else if (strcmp(str, "-m") == 0) strcpy(tag, "TCON");
    else if (strcmp(str, "-y") == 0) strcpy(tag, "TYER");
    else if (strcmp(str, "-c") == 0) strcpy(tag, "COMM");
    else {
        printf("Invalid tag string\n");
        return failure;
    }

    
    FILE* temp = fopen("output.mp3", "w");                      //// Open a temporary file for writing
    if (temp == NULL) {
        printf("file opening has been failed");
        return failure;
    }

    
    char buffer[10];
    rewind(fptr_mp3);
    fread(buffer, 10, 1, fptr_mp3);
    fwrite(buffer, 10, 1, temp);                            // Read and write the initial 10 bytes of the MP3 file

    // Iterate over the first 6 frames of the MP3 file
    for (int i = 0; i < 6; i++) {
        fread(frame_id, 4, 1, fptr_mp3);
        frame_id[4] = '\0';
        fread(&size, 4, 1, fptr_mp3);
        size = bigEndianToLittleEndian(size);
        csize = little_to_big_endian(size);

        
        if (strcmp(frame_id, tag) != 0) {                               // Check if the current frame matches the tag to be edited
            copy_content(fptr_mp3, temp, frame_id, size, csize);
        } else {
            edit_content(fptr_mp3, temp, frame_id, size,content);
            copy_remaining_data(fptr_mp3, temp);
            break;
        }
    }

    return success;
}

/**
 * @brief copy_content->function to copy the contents of tags that are not getting edited.
 * 
 * @param sample mp3 file pointer which has been already opened and verified in edit functions. 
 * @param fid tag to be written into the file.
 * @param size size to fetch content from original file.
 * @param size2 size to write into the output file.
 * @return void function(no return).
 */
void copy_content(FILE *sample, FILE *output, char* fid, uint size, uint size2) {       //function to copy the tag contents if tag doesnt match
    //printf("hello");
    char flag[2];

   
    fwrite(fid, 4, 1, output);
    fwrite(&size2, 4, 1, output);                                                    // Write frame ID and size to output
    fread(flag, 2, 1, sample);
    fwrite(flag, 2, 1, output);

   
    char ch;
    fread(&ch, 1, 1, sample);                                                //skipping first byte in every content of tag
    fwrite(&ch, 1, 1, output);
    char buffer[size];
    fread(buffer, size - 1, 1, sample);
    fwrite(buffer, size - 1, 1, output);
}
/**
 * @brief copy_content->function to copy the contents of tags that are not getting edited.
 * 
 * @param sample mp3 file pointer which has been already opened and verified in edit functions. 
 * @param output output mp3 file pointer.
 * @param fid tag to be written into the file.
 * @param size size to seek the original file pointer to read the next token.
 * @param content content going to be changes in mp3 file provided from the user.
 * @return void function(no return).
 */
void edit_content(FILE *sample, FILE *output, char* fid, uint size,char* content) {
    char flag[2];
    uint size2 = strlen(content) + 1;
    size2 = little_to_big_endian(size2);

    // Write edited content to output
    fwrite(fid, 4, 1, output);                              //write 4 bytes of tag into output file.
    fwrite(&size2, 4, 1, output);                           //write tag content size into output file. 
    fread(flag, 2, 1, sample);                              //read 2 flag bytes from the input file.
    fwrite(flag, 2, 1, output);                             //write 2 flag bytes into the output file.
    char ch;
    fread(&ch, 1, 1, sample);                               //reading one flag byte which is present at first byte of the tag content.
    fwrite(&ch, 1, 1, output);                              //writing that 1 byte into the output file.
    size2 = bigEndianToLittleEndian(size2);                 //converting the size2 from bigendian to littlendian .
    fwrite(content,size2 - 1, 1, output);                   // writing content into the output file.
    fseek(sample, size - 1, SEEK_CUR);                      //moving the input file pointer to next tag position.
}
/**
 * @brief copy_remaining_content->function to copy the remaining contents of tags the original file into output file.
 * 
 * @param sample mp3 file pointer of original file.
 * @param output mp3 file pointer of output file .
 * @return void function(no return).
 */
void copy_remaining_data(FILE *sample, FILE *output) {
    char ch;

    // Copy the remaining data from sample to output
    while ((fread(&ch, 1, 1, sample)) > 0) {
        fwrite(&ch, 1, 1, output);
    }

    // Close both files
    fclose(sample);
    fclose(output);
}
