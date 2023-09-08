#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define SIZEARR(ARR) (sizeof(ARR) / sizeof(ARR[0]))
#define MAX_FILE_NAME_LEN 512
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))

//ZIP Local File Header
const unsigned char zip_lfh_sign[] = { '\x50', '\x4b', '\x03', '\x04'};

// ZIP Local File Header without signature
#pragma pack(1)
struct lfh_tail {
    uint8_t something[14];
    uint32_t compressed_size;
    uint32_t uncompressed_size;
    uint16_t filename_len;
    uint16_t extra_len;
};
#pragma pack()

//JPEG

const unsigned char jpeg_soi[] = {'\xFF', '\xD8'};
const unsigned char jpeg_eoi[] = {'\xFF', '\xD9'};

bool read_until_match(FILE *f, const unsigned char pattern[], size_t sz, int *io_error) {
    size_t i = 0;
    int ch = '\0';

    while(i < sz && (ch = fgetc(f)) != EOF) {
        if(ch == pattern[i]) {
            i++;
        }
        else
        {
            i = 0;
        }
    }

    if(!io_error) {
        *io_error = (ch == EOF && !feof(f)) ? errno : 0;
    }

    return (i == sz);
}

bool read_until_mismatch(FILE *f, const unsigned char pattern[], size_t sz, int *io_error)
{
    size_t i = 0;
    int ch = '\0';

    while((ch = fgetc(f)) != EOF && (i < sz) && (ch == pattern[i]))
    {
        i++;
    }

    if(io_error)
    {
        *io_error = (ch == EOF && !feof(f)) ? errno : 0;
    }

    return (i == sz);
}



int main(int argc, char **argv)
{
    if(argc < 2) {
        printf("List zipped files in ZipJpeg archive. \nUsage: \t %s <path to archive> \n\n",  argv[0]);
        return EXIT_FAILURE;
    }

    const char *archive_path = argv[1];

    FILE *f = fopen(archive_path, "rb");
    if(!f) {
        printf("Error opening file\n");
        return EXIT_FAILURE;
    }

    //Check file begins with jpeg
    int io_error = 0;

    if(!read_until_mismatch(f, jpeg_soi, SIZEARR(jpeg_soi), &io_error) ||
            !read_until_match(f, jpeg_eoi, SIZEARR(jpeg_eoi), &io_error))
    {
        if(io_error == 0) {
            printf("%s in not Jpeg or ZipJpeg archive\n", archive_path);

        }
        else
        {
            perror("Error reading file\n");
        }
        fclose(f);
        return EXIT_FAILURE;
    }

    //Walking over zip LFH
    int file_counter = 0;


    while(read_until_match(f, zip_lfh_sign, SIZEARR(zip_lfh_sign), &io_error))
    {
        char string_buf[MAX_FILE_NAME_LEN + 1];
        struct lfh_tail lfh;
        size_t retval;
        uint16_t len;

        retval = fread(&lfh, sizeof(lfh), 1, f);
        if(retval == 0) {
            io_error = !feof(f);
            break;
        }

        len = le16toh(lfh.filename_len);
        retval = fread(string_buf, 1, MIN(MAX_FILE_NAME_LEN, len), f);
        if(retval == 0) {
            io_error = !feof(f);
            break;
        }
        string_buf[retval] = '\0';

        size_t offset = le32toh(lfh.compressed_size) + le16toh(lfh.extra_len);
        fseek(f, offset, SEEK_CUR);
        if(retval == 0) {
            io_error = !feof(f);
            break;
        }
        puts(string_buf);
        file_counter++;
    }

    if(io_error != 0 && !feof(f)) {
        perror("Error reading file\n");
    }
    else if(file_counter == 0) {
        printf("%s is jpeg file\n", archive_path);
    }

    fclose(f);
    return EXIT_SUCCESS;
}
