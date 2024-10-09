#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    // code to recollect the files
    FILE* packet_paths = fopen("packet_path.txt", "r");

    // final file
    FILE* final = fopen("final.png", "ab");
    char paths[200];

    int packet_size = 10240;
    unsigned char *buffer;

    // after opening the file, allocate memory for the buffer
    buffer = (unsigned char*) malloc(packet_size);


    while(fgets(paths, 200, packet_paths)){
        
        printf("reading from %s and appending to final.png",paths);
        char *trimmed_file_name = strtok(paths, "\n");
        FILE* collection_file = fopen(trimmed_file_name, "rb");
        fread(buffer, sizeof(unsigned char), packet_size, collection_file);
        fwrite(buffer, sizeof(unsigned char), packet_size, final);
        fclose(collection_file);
    }
    
    free(buffer);
    fclose(final);
    fclose(packet_paths);
}