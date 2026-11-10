
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PASSWORD_LENGTH 100

int checkPassword(const char password[]) {
    int hasUpper = 0;
    int hasLower = 0;
    int hasDigit = 0;
    int hasSymbol = 0;
    int score = 0;

    size_t length = strlen(password);

    // Check password length
    if (length >= 8) {
        score++;
    }

    // Analyze each character
    for (size_t i = 0; i < length; i++) {
        unsigned char ch = (unsigned char)password[i];

        if (isupper(ch)) {
            hasUpper = 1;
        }

        if (islower(ch)) {
            hasLower = 1;
        }

        if (isdigit(ch)) {
            hasDigit = 1;
        }

        if (ispunct(ch)) {
            hasSymbol = 1;
        }
    }

    // Calculate total score
    score += hasUpper;
    score += hasLower;
    score += hasDigit;
    score += hasSymbol;

    // Display security report
    printf("\n========== PASSGUARD REPORT ==========\n");

    printf("Password Length : %zu characters\n", length);

    printf("Minimum Length  : %s\n",
           length >= 8 ? "PASS" : "FAIL");

    printf("Uppercase       : %s\n",
           hasUpper ? "PASS" : "FAIL");

    printf("Lowercase       : %s\n",
           hasLower ? "PASS" : "FAIL");

    printf("Numbers         : %s\n",
           hasDigit ? "PASS" : "FAIL");

    printf("Special Symbols : %s\n",
           hasSymbol ? "PASS" : "FAIL");

    printf("--------------------------------------\n");
    printf("Security Score  : %d / 5\n", score);

    if (length < 8 || score <= 2) {
        printf("Security Level  : WEAK\n");
    }
    else if (score <= 4) {
        printf("Security Level  : ACCEPTABLE\n");
    }
    else {
        printf("Security Level  : STRONG\n");
    }

    printf("======================================\n");

    return score;
}

int main(void) {
    char password[MAX_PASSWORD_LENGTH];

    printf("======================================\n");
    printf("       PASSGUARD PASSWORD CHECKER     \n");
    printf("======================================\n");

    printf("Enter your password: ");

    if (scanf("%99s", password) != 1) {
        printf("Error: Unable to read password.\n");
        return 1;
    }

    checkPassword(password);

    return 0;
}
