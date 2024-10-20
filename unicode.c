#include <stdio.h>

int get_utf8_code_point_length(const unsigned char utf8) {
    if ((utf8 >> 7) == 0b00000000)
        return 1;
    else if ((utf8 >> 5) == 0b00000110)
        return 2;
    else if ((utf8 >> 4) == 0b00001110)
        return 3;
    else if ((utf8 >> 3) == 0b00011110)
        return 4;

    return -1;
}

int fgetuc(FILE *stream, char buf[5]) {
    int cp_length;

    if (fread(buf, 1, 1, stream) <= 0) return -1;
    cp_length = get_utf8_code_point_length(buf[0]);
    if (fread(buf + 1, 1, cp_length - 1, stream) != cp_length - 1) return -1;
    buf[cp_length] = '\0';
}