#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char password[50];
    int upper = 0, lower = 0, digit = 0, symbol = 0;

    printf("Enter your password: ");
    
    fgets(password, sizeof(password), stdin);



    for (int i = 0; password[i] != '\0'; i++) {
        if (isupper((unsigned char)password[i]))
            upper = 1;
        else if (islower((unsigned char)password[i]))
            lower = 1;
        else if (isdigit((unsigned char)password[i]))
            digit = 1;
        else
            symbol = 1;
    }

    if (strlen(password) > 8 &&
        upper == 1 &&
        lower == 1 &&
        digit == 1 &&
        symbol == 1) {

        printf("Password is correct! It meets all requirements.\n");

    } else {
        printf("Password is incorrect! It does not meet all requirements.\n");
    }

    return 0;
}
