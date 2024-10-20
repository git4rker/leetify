#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unicode.h"
#include "map.h"

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
    char uc[5];

    do {
        const char *leetified = leetify(uc);
        if (!leetified) leetified = uc;

        fwrite(leetified, 1, strlen(leetified), stdout);
    } while (fgetuc(stdin, uc) != -1);
}