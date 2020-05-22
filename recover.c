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
    BYTE* buffer = malloc(sizeof(BYTE) * 512);
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        return 1;
    }
    int i = 0; 
    int j = 4;  
    while (fread(buffer, 512, 1, file) >= 512)//fread(buffer, 512, 1, file) == 1
    {
        fread(buffer, sizeof(BYTE), 512, file);
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(argv[1], "%03i.jpg", i);
            i++;
            FILE *img = fopen(argv[1], "w");
            while (buffer[j] != 0xff && buffer[j + 1] != 0xd8 && buffer[j + 2] != 0xff && (buffer[j + 3] & 0xf0) != 0xe0) //not the beginning of the next jpeg file, keep writing to the current jpeg file
            {
                fwrite(buffer, sizeof(BYTE), 512, img);  
                j++;
            }
            fclose(img);
        }

    }
    fclose(file);
    free(buffer);
    

}
