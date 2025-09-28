#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// --- Function Prototypes ---
// REMOVED: #include "convert.c"
// These declarations tell main.c that the functions exist in another file.
// This is the correct way to link files in C.
void oct_to_bin(const char *oct, char *out);
void oct_to_hex(const char *oct, char *out);
void hex_to_bin(const char *hex, char *out);
void to_sign_magnitude(int32_t n, char *out);
void to_ones_complement(int32_t n, char *out);
void to_twos_complement(int32_t n, char *out);


#define LINEBUF 256
#define MAX_BUFFER 128

int main() {
    // Open test file
    FILE *file = fopen("a2_test.txt", "r");
    // Print no file error if no test file is present
    if (!file) {
        perror("Could not open test file a2_test.txt");
        return 1;
    }
    // Hold each line read from file
    char line[LINEBUF];
    // Var to hold passed tests and total tests
    int passed = 0, total = 0;
    // Read each line of file
    while (fgets(line, sizeof(line), file)) {
        // This skips comments & blank lines
        if (line[0] == '#' || strlen(line) < 2) continue;

        // Remove trailing newline character
        line[strcspn(line, "\r\n")] = 0;

        char func[32], input_str[128], expected[128], out[128];
        int32_t n;

        // Test cases for mapping functions (string input)
        if (sscanf(line, "oct_to_bin %s %s", input_str, expected) == 2) {
            total++;
            oct_to_bin(input_str, out);
            if (strcmp(out, expected) == 0) {
                passed++;
                printf("Test %d: oct_to_bin(\"%s\") -> Expected:\"%s\" Got:\"%s\" [PASS]\n", total, input_str, expected, out);
            } else {
                printf("Test %d: oct_to_bin(\"%s\") -> Expected:\"%s\" Got:\"%s\" [FAIL]\n", total, input_str, expected, out);
            }
        } else if (sscanf(line, "oct_to_hex %s %s", input_str, expected) == 2) {
            total++;
            oct_to_hex(input_str, out);
            if (strcmp(out, expected) == 0) {
                passed++;
                printf("Test %d: oct_to_hex(\"%s\") -> Expected:\"%s\" Got:\"%s\" [PASS]\n", total, input_str, expected, out);
            } else {
                printf("Test %d: oct_to_hex(\"%s\") -> Expected:\"%s\" Got:\"%s\" [FAIL]\n", total, input_str, expected, out);
            }
        } else if (sscanf(line, "hex_to_bin %s %s", input_str, expected) == 2) {
            total++;
            hex_to_bin(input_str, out);
            if (strcmp(out, expected) == 0) {
                passed++;
                printf("Test %d: hex_to_bin(\"%s\") -> Expected:\"%s\" Got:\"%s\" [PASS]\n", total, input_str, expected, out);
            } else {
                printf("Test %d: hex_to_bin(\"%s\") -> Expected:\"%s\" Got:\"%s\" [FAIL]\n", total, input_str, expected, out);
            }
        }
        // Test cases for signed representation functions (integer input)
        else if (sscanf(line, "to_sign_magnitude %d %s", &n, expected) == 2) {
            total++;
            to_sign_magnitude(n, out);
            if (strcmp(out, expected) == 0) {
                passed++;
                printf("Test %d: to_sign_magnitude(%d) -> Expected:\"%s\" Got:\"%s\" [PASS]\n", total, n, expected, out);
            } else {
                printf("Test %d: to_sign_magnitude(%d) -> Expected:\"%s\" Got:\"%s\" [FAIL]\n", total, n, expected, out);
            }
        } else if (sscanf(line, "to_ones_complement %d %s", &n, expected) == 2) {
            total++;
            to_ones_complement(n, out);
            if (strcmp(out, expected) == 0) {
                passed++;
                printf("Test %d: to_ones_complement(%d) -> Expected:\"%s\" Got:\"%s\" [PASS]\n", total, n, expected, out);
            } else {
                printf("Test %d: to_ones_complement(%d) -> Expected:\"%s\" Got:\"%s\" [FAIL]\n", total, n, expected, out);
            }
        } else if (sscanf(line, "to_twos_complement %d %s", &n, expected) == 2) {
            total++;
            to_twos_complement(n, out);
            if (strcmp(out, expected) == 0) {
                passed++;
                printf("Test %d: to_twos_complement(%d) -> Expected:\"%s\" Got:\"%s\" [PASS]\n", total, n, expected, out);
            } else {
                printf("Test %d: to_twos_complement(%d) -> Expected:\"%s\" Got:\"%s\" [FAIL]\n", total, n, expected, out);
            }
        }
    }

    fclose(file); //Close file
    printf("\nSummary: %d/%d tests passed\n", passed, total); //Summary after code compiles
    return 0; // Exit point
}

