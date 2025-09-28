#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

// Helper function to convert a positive integer to a 31-bit binary string
void int_to_binary_31(uint32_t n, char *out) {
    for (int i = 0; i < 31; ++i) {
        out[30 - i] = ((n >> i) & 1) ? '1' : '0';
    }
    out[31] = '\0';
}

// Function 1: Convert octal to binary using 3-bit mapping
void oct_to_bin(const char *oct, char *out) {
    int out_pos = 0;
    for (int i = 0; oct[i] != '\0'; ++i) {
        switch (oct[i]) {
            case '0': strcpy(&out[out_pos], "000"); break;
            case '1': strcpy(&out[out_pos], "001"); break;
            case '2': strcpy(&out[out_pos], "010"); break;
            case '3': strcpy(&out[out_pos], "011"); break;
            case '4': strcpy(&out[out_pos], "100"); break;
            case '5': strcpy(&out[out_pos], "101"); break;
            case '6': strcpy(&out[out_pos], "110"); break;
            case '7': strcpy(&out[out_pos], "111"); break;
        }
        out_pos += 3;
    }
    out[out_pos] = '\0';
}

// Function 2: Convert octal to hexadecimal via binary
void oct_to_hex(const char *oct, char *out) {
    char binary_representation[100]; // Intermediate buffer for binary string
    oct_to_bin(oct, binary_representation);

    int bin_len = strlen(binary_representation);
    int hex_pos = 0;

    // Pad with leading zeros to make the length a multiple of 4
    int padding = (4 - (bin_len % 4)) % 4;
    char padded_binary[100];
    if (padding != 4) {
        for(int i = 0; i < padding; ++i) {
            padded_binary[i] = '0';
        }
    }
    strcpy(padded_binary + padding, binary_representation);


    // Group by 4 and convert to hex
    for (int i = 0; i < strlen(padded_binary); i += 4) {
        int val = 0;
        if (padded_binary[i] == '1') val += 8;
        if (padded_binary[i+1] == '1') val += 4;
        if (padded_binary[i+2] == '1') val += 2;
        if (padded_binary[i+3] == '1') val += 1;

        if (val < 10) {
            out[hex_pos++] = val + '0';
        } else {
            out[hex_pos++] = val - 10 + 'A';
        }
    }
    out[hex_pos] = '\0';
    
    //Remove leading zero unless the result is just "0"
    if (hex_pos > 1 && out[0] == '0') {
        memmove(out, out + 1, hex_pos);
    }
}

// Function 3: Convert hexadecimal to binary using 4-bit mapping
void hex_to_bin(const char *hex, char *out) {
    int out_pos = 0;
    for (int i = 0; hex[i] != '\0'; ++i) {
        char c = toupper(hex[i]);
        switch (c) {
            case '0': strcpy(&out[out_pos], "0000"); break;
            case '1': strcpy(&out[out_pos], "0001"); break;
            case '2': strcpy(&out[out_pos], "0010"); break;
            case '3': strcpy(&out[out_pos], "0011"); break;
            case '4': strcpy(&out[out_pos], "0100"); break;
            case '5': strcpy(&out[out_pos], "0101"); break;
            case '6': strcpy(&out[out_pos], "0110"); break;
            case '7': strcpy(&out[out_pos], "0111"); break;
            case '8': strcpy(&out[out_pos], "1000"); break;
            case '9': strcpy(&out[out_pos], "1001"); break;
            case 'A': strcpy(&out[out_pos], "1010"); break;
            case 'B': strcpy(&out[out_pos], "1011"); break;
            case 'C': strcpy(&out[out_pos], "1100"); break;
            case 'D': strcpy(&out[out_pos], "1101"); break;
            case 'E': strcpy(&out[out_pos], "1110"); break;
            case 'F': strcpy(&out[out_pos], "1111"); break;
        }
        out_pos += 4;
    }
    out[out_pos] = '\0';
}

// Function 4: Convert to sign-magnitude representation
void to_sign_magnitude(int32_t n, char *out) {
    if (n >= 0) {
        out[0] = '0';
        int_to_binary_31(n, &out[1]);
    } else {
        out[0] = '1';
        int_to_binary_31(-n, &out[1]);
    }
    out[32] = '\0';
}

// Function 5: Convert to one's complement representation
void to_ones_complement(int32_t n, char *out) {
    uint32_t val = (n >= 0) ? n : ~(-n);
    for (int i = 0; i < 32; ++i) {
        out[31 - i] = ((val >> i) & 1) ? '1' : '0';
    }
    out[32] = '\0';
}

// Function 6: Convert to two's complement representation
void to_twos_complement(int32_t n, char *out) {
    uint32_t val = (uint32_t)n;
    for (int i = 0; i < 32; ++i) {
        out[31 - i] = ((val >> i) & 1) ? '1' : '0';
    }
    out[32] = '\0';
}

