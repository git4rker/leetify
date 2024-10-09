#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

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

const char *leetify(const char *str) {
    for (int i = 0; i < sizeof(map) / sizeof(map[0]); i += 2) {
        const char *key = map[i];
        const char *value = map[i + 1];
        
        if (strcmp(key, str) == 0) return value;
    }

    return NULL;
}

void die_in_shame(const char *cause) {
    perror(cause);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    char buf[5];
    int bytes_read, cp_length;

    do {
        bytes_read = fread(buf, 1, 1, stdin);
        if (bytes_read <= 0) break;
        
        cp_length = get_utf8_code_point_length(buf[0]);

        bytes_read += fread(buf + 1, 1, cp_length - 1, stdin);
        buf[cp_length] = '\0';

        const char *leetified = leetify(buf);
        if (!leetified) leetified = buf;

        fwrite(leetified, 1, strlen(leetified), stdout);
    } while (bytes_read == cp_length);

    if (bytes_read < 0) die_in_shame("couldn't read from stdin");
}