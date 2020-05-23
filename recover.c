#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    typedef uint8_t BYTE; 
    if (argc != 2){
        printf("Enter memory card name");
        return 1; 
    }
    /*Malloc allocates memory at run time; it returns a pointer to the first block of memory allocated; the information stays until it is manually free 
      whereas in arrays, it is automically destroyed when the function that calls it is destroyed. Since arrays are stored in the stack, there may be less space available to. */
    BYTE *buffer = malloc(sizeof(BYTE) * 512); // create buffer to store bytes read from card
    FILE *file = fopen(argv[1], "r"); //open the file in read mode
    if (!file)
    {
        return 1;
    }
    int i = 0; 
    FILE *img; // declaration to make new file

    while (fread(buffer, 512, 1, file) == 1)// read 512 bytes once each until you can no longer read one 512 bytes
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) //if it's the beginning of a jpeg file 
        {
            char filename[8];  //create holder for name of file
            sprintf(filename, "%03i.jpg", i); //print name to the holder
            if (i == 0) // if it's the first jpeg
            {//we need to check for first file so that we have a condition to close files i.e., we know that a new file has begun and an old file has finished 
                img = fopen(filename, "w"); // open new file to write to 
                i++; // increase file count
                fwrite(buffer, 512, 1, img); // write to new file from buffer   
            }
            else
            {
                fclose(img); //if not the first jpeg, then close the current file and open a new file
                img = fopen(filename, "w");  
                i++;
                fwrite(buffer, 512, 1, img); 
            }
            
        }
        else if (i > 0) // if not the beginning of a jpeg file but we know that we passed the "blank zone", then continue writing to the current file that was opened
        {
            fwrite(buffer, 512, 1, img);  
        }

    }
    fclose(file);
    free(buffer);
    

}
