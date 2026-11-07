
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MIN_LENGTH 8
#define MAX_LENGTH 255

// Function to check common passwords
int isCommonPassword(const char password[]) {

    const char *common_passwords[] = {
        "password",
        "password123",
        "12345678",
        "qwerty123",
        "admin123",
        "root123",
        "abcdefgh",
        "123456789",
        "P@ssw0rd"
    };

    size_t count = sizeof(common_passwords) /
                   sizeof(common_passwords[0]);

    for (size_t i = 0; i < count; i++) {
        if (strcmp(password, common_passwords[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

// Function to check password strength
void checkPassword(const char password[]) {

    size_t length = strlen(password);

    int has_upper = 0;
    int has_lower = 0;
    int has_digit = 0;
    int has_symbol = 0;

    int score = 0;

    // Check password length
    if (length >= MIN_LENGTH) {
        score++;
    }

    // Analyze every character
    for (size_t i = 0; i < length; i++) {

        unsigned char ch = (unsigned char)password[i];

        if (isupper(ch)) {
            has_upper = 1;
        }
        else if (islower(ch)) {
            has_lower = 1;
        }
        else if (isdigit(ch)) {
            has_digit = 1;
        }
        else if (ispunct(ch)) {
            has_symbol = 1;
        }
    }

    // Calculate score
    score += has_upper;
    score += has_lower;
    score += has_digit;
    score += has_symbol;

    // Print password report
    printf("\n========== Password Report ==========\n");

    printf("Password Length: %zu\n", length);

    printf("Minimum Length (8): %s\n",
           length >= MIN_LENGTH ? "PASS" : "FAIL");

    printf("Uppercase Letters: %s\n",
           has_upper ? "PASS" : "FAIL");

    printf("Lowercase Letters: %s\n",
           has_lower ? "PASS" : "FAIL");

    printf("Digits: %s\n",
           has_digit ? "PASS" : "FAIL");

    printf("Special Symbols: %s\n",
           has_symbol ? "PASS" : "FAIL");

    printf("Score: %d/5\n", score);

    // Check common passwords
    int common = isCommonPassword(password);

    if (common) {
        printf("Common Password: DETECTED\n");
        printf("Final Result: WEAK\n");
    }
    else if (length < MIN_LENGTH || score <= 2) {
        printf("Common Password: NOT DETECTED\n");
        printf("Final Result: WEAK\n");
    }
    else if (score == 3 || score == 4) {
        printf("Common Password: NOT DETECTED\n");
        printf("Final Result: ACCEPTABLE\n");
    }
    else {
        printf("Common Password: NOT DETECTED\n");
        printf("Final Result: STRONG\n");
    }

    printf("=====================================\n");
}

int main(void) {

    char password[MAX_LENGTH + 1];

    printf("Enter your password: ");

    // Safely read password
    if (fgets(password, sizeof(password), stdin) == NULL) {
        printf("Error reading password.\n");
        return 1;
    }

    // Check if input exceeds buffer
    if (strchr(password, '\n') == NULL) {

        int ch;
        int too_long = 0;

        while ((ch = getchar()) != '\n' && ch != EOF) {
            too_long = 1;
        }

        if (too_long || strlen(password) == MAX_LENGTH) {
            printf("Error: Password is too long.\n");
            return 1;
        }
    }

    // Remove newline
    password[strcspn(password, "\n")] = '\0';

    // Check password
    checkPassword(password);

    return 0;
}