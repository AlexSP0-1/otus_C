#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "charset.h"

int main(int argc, char* argv[])
{
    if(argc < 4)
    {
        puts("Convert code-paged text file to utf-8.\n"
             "Usage:\tcp2utf8 <cp-file-in> <code-page> <out-file> \n"
             "Code pages supported:");

        for(size_t i = 0; i < cp_size; i++) {
            printf("\t%s\n", cp_names[i]);
        }
        return EXIT_FAILURE;
    }

    const char *input_file_path = argv[1];
    const char *code_page_name = argv[2];
    const char *output_file_path = argv[3];

    size_t cp_index = 0;
    while(cp_index < cp_size)
    {
        if(strncmp(code_page_name, cp_names[cp_index], max_cp_name_len) == 0)
        {
            break;
        }
        cp_index++;
    }

    if(cp_index == cp_size) {
        fprintf(stderr, "Error: code-page is not supported! \n Run without args to see supported code-pages.\n");
        return EXIT_FAILURE;
    }

    FILE *in_file = fopen(input_file_path, "rb");
    if(!in_file)
    {
        fprintf(stderr, "%s - io error: %s\n", input_file_path, strerror(errno));
        return EXIT_FAILURE;
    }

    FILE *out_file = fopen(output_file_path, "wb");
    if(!out_file)
    {
        fprintf(stderr, "%s - io error: %s\n", output_file_path, strerror(errno));
        fclose(in_file);
        return EXIT_FAILURE;
    }

    int ch;
    int io_result = 0;
    const unsigned int *cp = cp_data[cp_index];
    while((ch = fgetc(in_file) != EOF) && (io_result != EOF)) {
        if( ch < 0x80) {
            io_result = fputc(ch, out_file);
        }
        else
        {
            unsigned int up = cp[ch - 0x80];
            if (up < 0x800) {
              fputc(0xC0 | up >> 6, out_file);
            } else if (up < 0x8000) {
              fputc(0xE0 | up >> 12, out_file);
              fputc(0x80 | (up >> 6 & 0x3F), out_file);
            } else {
              fputc(0xF0 | up >> 18, out_file);
              fputc(0x80 | (up >> 12 & 0x3F), out_file);
              fputc(0x80 | (up >> 6 & 0x3F), out_file);
            }
            io_result = fputc(0x80 | (up & 0x3F), out_file);
        }
    }

    if(io_result == EOF)
    {
        perror("Failed on writing file:");
    }
    fclose(in_file);
    fclose(out_file);

    return io_result == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
}
