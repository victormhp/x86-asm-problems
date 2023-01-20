// 1.6 Exercises

#include <stdio.h>
#include <stdlib.h>

void reverseString(char* string, int len) {
   int middle = len / 2;
   char temp;
   for (int i = 0; i < middle; i++) {
      temp = string[i];
      string[i] = string[len - i - 1];
      string[len - i -1] = temp;
   }
}

unsigned int binaryToDecimal(char* bin, int len) {
    unsigned int decimal = 0;

    for (int i = 0; i < len; i++) {
        if (bin[i] == '1') {
            decimal += 1 << (len - i - 1);
        }
    }

    return decimal;
}

char* intToBinary(int n) {
    char *bin = malloc (sizeof(char) * 32);

    int i = 0;
    while (n > 0) {
        bin[i] = (n % 2) ? '1' : '0';
        n /= 2;
        i++;
    }
    
    reverseString(bin, i);
    return bin;
}

char* intToHexadecimal(int n) {
    char *hex = malloc (sizeof(char) * 8);
    char hex_chars[] = "0123456789ABCDEF";

    int i = 0;
    while (n > 0) {
        hex[i] = hex_chars[n % 16];
        n /= 16;
        i++;
    }
    
    reverseString(hex, i);
    return hex;
}

char* binarySubstraction(char *first, char *second, int len) {
    int n1 = binaryToDecimal(first, len);
    int n2 = binaryToDecimal(second, len);
    int substraction = n1 - n2;

    return intToBinary(substraction);
}

char* binarySubstraction2(char* bin1, int len1, char* bin2, int len2) {
    // Make the two strings the same size.
    char* larger_bin = len1 > len2 ? bin1 : bin2;
    char* shorter_bin = len1 > len2 ? bin2 : bin1;
    
    int larger_len = len1 > len2 ? len1 : len2;
    int shorter_len = len1 > len2 ? len2 : len1;
    int len_diff = larger_len - shorter_len;  

    char* new_bin = malloc(sizeof(char) * (shorter_len + len_diff));
    
    for (int i = 0; i < len_diff; i++) {
        new_bin[i] = '0';
    }
    for (int i = 0; i < shorter_len; i++) {
        new_bin[len_diff + i] = shorter_bin[i];
    }

    // Do the substraction once the strings are the same length.
    char* result = malloc (sizeof(char) * larger_len);
    int carry = 0;

    for (int i = larger_len - 1; i >= 0; i--) {
        int num = (larger_bin[i] - '0') - (new_bin[i] - '0') - carry;
        if (num < 0) {
            carry = 1;
            num += 2;
        } else {
            carry = 0;
        }
        
        result[i] = num + '0';
    }

    free(new_bin);
    return result;
}

int main() {
    char b1[] = "10001000";
    char b2[] = "00101";

    int b1_len = sizeof(b1) - 1;
    int b2_len = sizeof(b2) - 1;
    
    char* x = binarySubstraction2(b1, b1_len, b2, b2_len);
    printf("Result: %s\n", x);
    free(x);
}
