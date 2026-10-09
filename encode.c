#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IS_SMALL(C) (C >= 'a' && C <= 'z')
#define IS_CAPITAL(C) (C >= 'A' && C <= 'Z')

#if KEEP_LOWERCASE
#define UPPER_BASE 'a'
#else
#define UPPER_BASE 'A'
#endif

#if KEEP_UPPERCASE
#define LOWER_BASE 'A'
#else
#define LOWER_BASE 'a'
#endif

#if DECODE_MODE
#define TERM 26
#define FACTOR -1
#else
#define TERM 0
#define FACTOR 1
#endif

int main(int argc, const char **argv)
{
    int c, ret = EXIT_FAILURE;
    FILE *src = NULL, *dest = stdout;
    size_t key_idx = 0, key_len, shift;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <key> <src file> [<dest file>]\n", argv[0]);
        goto cleanup;
    }

    src = fopen(argv[2], "r");

    if (!src) {
        perror(argv[2]);
        goto cleanup;
    }

    if (argv[3]) {
        dest = fopen(argv[3], "w");
    }

    if (!dest) {
        perror(argv[3]);
        goto cleanup;
    }

    key_len = strlen(argv[1]);

    for (c = 0; c < key_len; c++) {
        if (!IS_SMALL(argv[1][c])) {
            fprintf(stderr, "Allowed characters for the key: a–z\n");
            goto cleanup;
        }
    }

    while ((c = fgetc(src)) != EOF) {
        if (!IS_CAPITAL(c) && !IS_SMALL(c)) {
#if SKIP_NON_LETTERS && !DECODE_MODE
            continue;
#else
            fputc(c, dest);
#endif
        } else {
            shift = FACTOR * (argv[1][key_idx++] - 'a') + TERM;

            if (IS_CAPITAL(c)) {
                fputc((c - 'A' + shift) % 26 + UPPER_BASE, dest);
            } else {
                fputc((c - 'a' + shift) % 26 + LOWER_BASE, dest);
            }
            key_idx %= key_len;
        }
    }
    fputc('\n', dest);

    ret = EXIT_SUCCESS;

cleanup:
    if (src) {
        fclose(src);
    }
    if (dest != stdout) {
        fclose(dest);
    }
    return ret;
}