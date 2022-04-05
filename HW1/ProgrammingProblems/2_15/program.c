#include <stdio.h>
#include <stdlib.h>


int main()
{
    FILE *srcPtr, *destPtr;
    char sourcePath[200], destPath[200], ch;

    // source path get set
    printf("Please enter source file path: ");
    scanf("%s", sourcePath);
    srcPtr = fopen(sourcePath, "r");
    if (!srcPtr)
    {
        printf("\nUnable to open file.\n");
        printf("Please check if file exists and you have read privilege.\n");
        exit(EXIT_FAILURE);
    }
    
    // destination path get set
    printf("Please enter destination file path: ");
    scanf("%s", destPath);
    destPtr = fopen(destPath, "w");
    if (!destPtr)
    {
        printf("\nUnable to open file.\n");
        printf("Please check if file exists and you have write privilege.\n");
        exit(EXIT_FAILURE);
    }

    // get chars from source and put to destination
    ch = fgetc(srcPtr);
    while (ch != EOF)
    {
        fputc(ch, destPtr);
        ch = fgetc(srcPtr);
    }
    printf("\nFiles copied successfully.\n");

    // close files
    fclose(srcPtr);
    fclose(destPtr);

    return 0;
}