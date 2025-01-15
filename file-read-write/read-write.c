#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: <%s> -o file\nReads the contents of the file and prints them to stdout.\n",argv[0]);
        return 0;
    }
    if (argv[1][0] == '-') {
        for (int i = 0; i < argc; i++){
            if (strcmp(argv[i], "-o") == 0) {
                //read current content then write number
                char *filename = argv[i+1];
                FILE *fptr = fopen(filename, "r");
                if (fptr == NULL) {
                    printf("Error: unable to open file.");
                    fclose(fptr);
                    return 3;
                }
                fseek(fptr, 0, SEEK_END);
                int size = (int)ftell(fptr);
                printf("%i\n",size);
                fflush(stdout);
                rewind(fptr);

                char content[size];
                while(fgets(content, size, fptr)) {
                    printf("%s",content);
                }
                fclose(fptr);
                printf("\n");
            }
        }
    }
    return 0;
}