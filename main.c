/***************************************************************************************************************************************************
*Author         :MANOHARAN BALAKRISHNAN
*Date           :02/08/2024
*File           :main.c
*Title          :To decide whether to view or edit based on user's input.
*Description    :This file has the validation parts of CLA and function calls for view and edit both operations.
****************************************************************************************************************************************************/
#include "view.h"


/**
 * @brief main function ->will call functions based on user's choice(edit or view or help).
 * 
 * @param argc argument count which are passed through the command line. 
 * @param argv arguments(strings) passed through command line.
 * @return 0 on success, non-zero on failure.
 */
int main(int argc, char** argv) {
    // Check if the number of arguments is less than 3
    if(strcmp(argv[1],"-v")==0){
    if(argc < 3){
        print_info();
        return 0;
    }
    }
    else{
        if(argc<=3){
        print_info();
        return 0;
        }
    }

    FILE *fptr_mp3;

    // Check if the first argument is for viewing the MP3 file
    if (strcmp(argv[1], "-v") == 0) {
        if (strstr(argv[2], ".mp3") != NULL) {
            fptr_mp3 = fopen(argv[2], "r");
            if (fptr_mp3 != NULL) {
                printf("INFO: FILE OPENED SUCCESSFULLY\n");
                if (version_verification(fptr_mp3, "ID3") == success) {
                    printf("INFO: VERSION CONFIRMED\n");
                    if (view_mp3(fptr_mp3) == success) printf("INFO: DONE\n");      //function call to view properties of mp3 file.
                    else printf("INFO: MP3 VIEW HAS BEEN FAILED\n");
                } else {
                    printf("INFO: VERSION VERIFICATION HAS BEEN FAILED\n");
                }
            } else {
                printf("INFO: FILE OPENING HAS BEEN FAILED\n");
            }
        } else {
            printf("INFO: ERROR PASS A FILE WITH .MP3 EXTENSION\n");
        }
    // Check if the first argument is for editing the MP3 file
    } else if (strcmp(argv[1], "-e") == 0) {   
        if (strstr(argv[3], ".mp3") != NULL) {
            fptr_mp3 = fopen(argv[3], "r");
            if (fptr_mp3 != NULL) {
                printf("INFO: FILE OPENED SUCCESSFULLY\n");
                if (version_verification(fptr_mp3, "ID3") == success) {
                    printf("INFO: VERSION CONFIRMED\n");          
                    if (edit_mp3(fptr_mp3, argv[2],argv[4]) == success){                    //function call to edit the mp3 file.
                        printf("INFO: DONE");
                        remove(argv[3]);
                        rename("output.mp3", argv[3]);                              //renaming the new file with older name.
                    }
                    else printf("INFO: MP3 EDITING HAS BEEN FAILED");
                } else {
                    printf("INFO: VERSION VERIFICATION HAS BEEN FAILED\n");
                }
            } else {
                printf("INFO: FILE OPENING HAS BEEN FAILED\n");
            }
        } else {
            printf("INFO: ERROR PASS A FILE WITH .MP3 EXTENSION\n");
        }
    // Check if the argument is for displaying help information
    } else if (strcmp(argv[1], "--help") == 0) {                        
        print_info();
        return 0;
    } 
    else {
        printf("INFO: ENTER A VALID OPTION\n");
    }

    return 0; 
}

/**
 * @brief version verification->this function has been used to verify the version of our mp3 file(ID3).
 * 
 * @param fptr_mp3 mp3 file pointer which has been already opened and verified in main functions. 
 * @param str character pointer which will hold the version of mp3 file.
 * @return 0 on success, non-zero on failure.
 */
Status version_verification(FILE *fptr_mp3, char *str) {                          
    char id[4];
    fread(id, 3, 1, fptr_mp3);
    id[3] = '\0';
    if(strcmp(id, "ID3") == 0){
        rewind(fptr_mp3);
        fseek(fptr_mp3, 10, SEEK_SET);
        return success;
    }
    else{
        printf("INFO:VERSION MISMATCH\n");
        return failure;
    }
}

/**
 * @brief print_info->function to print informations about passing arguments through CLA.
 * 
 * @param -NA. 
 * @param -NA.
 * @return return type is void.
 */
void print_info(){
     printf("\n---------------------------------------------------------------------------------------\n\n");
        printf("1. -v -> to view mp3 file contents\n");
        printf("2. -e -> to edit mp3 file contents\n");
        printf("\t2.1. -t -> to edit song title\n");
        printf("\t2.2. -a -> to edit artist name\n");                                       //printing help message
        printf("\t2.3. -A -> to edit album name\n");
        printf("\t2.4. -y -> to edit year\n");
        printf("\t2.5. -m -> to edit content\n");
        printf("\t2.6. -c -> to edit comment\n");
        printf("\n---------------------------------------------------------------------------------------\n\n");
}


