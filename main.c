#include <stdio.h>
#include <stdlib.h>

int main() {
    int packet_size = 10240;
    unsigned char *buffer;
    size_t read_bytes;
    
    // Open the file in binary mode as all the files data merely comes down to binary digits so this code will be scalable for different kinds of files.
    FILE* file = fopen("8bit.png", "rb");
    // checking if the file is opened correctly
    if (file == NULL) {
        printf("Error opening file");
        return 1;
    }


    // file to save the paths of the packet data
    remove("packet_path.txt");
    FILE* packet_file_path = fopen("packet_path.txt", "a");


    // after opening the file, allocate memory for the buffer
    buffer = (unsigned char*) malloc(packet_size);
    

    // tracking the file number for packet sequencing
    int file_number = 0;
    
    // Read each byte of the file till EOF
    while (( read_bytes = fread(buffer, sizeof(unsigned char), packet_size, file)) > 0) {
        
        // print the number of bytes read from the file
        printf("wrote %zu bytes from the file in the packet_%i file.\n", read_bytes, file_number);

        // dynamic file name generation
        char packet_base[] = "packet_";
        char packet_file_name[100];
        sprintf(packet_file_name, "%s%s%d%s" , "packets_folder/", packet_base, file_number, ".dat");

        // save the path in the packet_path.txt
        char packet_file_new_line[100];
        sprintf(packet_file_new_line, "%s%s", packet_file_name, "\n");
        fprintf(packet_file_path, packet_file_new_line);

        // opening the file
        FILE* packet_file = fopen(packet_file_name, "ab");

        // write the buffer in the packet file
        fwrite(buffer, sizeof(unsigned char), read_bytes, packet_file);

        // closing the packet file
        fclose(packet_file);

        // incrementing file number value
        file_number++;
    }

    // free memory which was saved for the buffer
    free(buffer);
    // close the file to save the paths of the packet files
    fclose(packet_file_path);
    // Close the main file
    fclose(file);
}
