#include <stdio.h>
#include <string.h>
#include <stdlib.h> 






void ngKoreExtractDigits(int num1, int num2 ) {
    int mcc0;
    int mcc1;
    int mcc2;
    int mnc0;
    int mnc1;
    int mnc2;
    // Extract digits from the first number (always 3 digits)
    mcc0 = num1 / 100;
    mcc1 = (num1 / 10) % 10;
    mcc2 = num1 % 10;

    // Extract digits from the second number (2 or 3 digits)
    if (num2 >= 10 && num2 <= 999) {
        // 2 or 3 digits
        if (num2 >= 100) {
            mnc0 = num2 / 100;   // Store the first digit
            mnc1 = (num2 / 10) % 10; // Store the second digit
            mnc2 = num2 % 10;    // Store the third digit
        } else {
            mnc0 = num2 / 10;;  // Leave the first variable untouched
            mnc1 = num2 % 10;   // Store the first digit
            mnc2 = 0;   // Store the second digit
        }
    } else {
        // Not a 2 or 3-digit number, set digits to -1 or some other default value
        mnc0 = mnc1 = mnc2 = -1;
    }

    printf("\n mcc %d %d %d\n", mcc0 , mcc1, mcc2);
    printf("\n mnc %d %d %d\n", mnc0 , mnc1, mnc2); 
}



int main() {
    int mcc = 0; // Default value
    int mnc = 0; // Default value



    FILE *config_file = fopen("config.txt", "r");
    if (config_file == NULL) {
        perror("Error opening config file");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), config_file)) {
        char key[100];
        char value[100];

        if (sscanf(line, "%99s = %99s", key, value) == 2) {
            if (strcmp(key, "mcc") == 0) {
                mcc = atoi(value);
            } else if (strcmp(key, "mnc") == 0) {
                mnc = atoi(value);
            }
        }
    }

    fclose(config_file);

    // Use configuration values
    printf("MCC :  %d\n", mcc);
    printf("MNC : %d\n", mnc);
    ngKoreExtractDigits(mcc, mnc);

    return 0;
}
