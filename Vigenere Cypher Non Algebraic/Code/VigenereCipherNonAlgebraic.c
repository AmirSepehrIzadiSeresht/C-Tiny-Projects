#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

char getSubstitution(char * txtLetter, char * keyLetter, bool mode);
void decrypt(char * inputTxt, char * key, char * const outputTxt);
void encrypt(char * inputTxt, char * key, char * const outputTxt);
bool checkKey(char * key);
bool checkInputTxt(char * inputTxt);

int main() {
    char inputTxt[1000] = {0};
    char key[1000] = {0};
    char outputTxt[1000] = {0};

    puts("Type in a text. (up to 999 characters) \n ** Type ^ to end the input **");
    printf("%s", ">> ");
    
    for (size_t i = 0 , ch = 0; i < 999 && ch != '^'; ++i) {
        scanf("%c", &ch);
        
        if (ch != '^') {
            inputTxt[i] = ch;
        } else {
            inputTxt[i] = '\0';
        }
    }
    
    puts("Type in key");
    printf("%s", ">> ");
    scanf("%999s", key);
    
    int optionIdx;
    
    void (*options[2])(char *, char *, char * const) = 
    {encrypt, decrypt};
    
    puts("Choose one option:");
    puts("0. Encrypt");
    puts("1. Decrypt");
    puts("2. Exit");
    printf("%s", ">> ");
    
    scanf("%d", &optionIdx);
    
    while(optionIdx > 2 || optionIdx < 0) {
        puts("INVALID OPTION. PLEASE INSERT A VALID OPTION \n");
        
        puts("Choose one option:");
        puts("0. Encrypt");
        puts("1. Decrypt");
        puts("2. Exit");
        printf("%s", ">> ");

        scanf("%d", &optionIdx);
    }

    if (2 == optionIdx) {

        return 0;
    }

    options[optionIdx](inputTxt, key, outputTxt);

    return 0;
}

bool checkKey(char * key) {

    for (size_t i = 0; key[i]; ++i) {

        if (!isalpha(key[i])) {
            puts("NOT VALID KEY. THE KEY MUST CONTAIN LETTERS ONLY.");
            return false;
        } else {
            key[i] = toupper(key[i]);
        }
    }

    return true;
}

bool checkInputTxt(char * inputTxt) {

    for (size_t i = 0; inputTxt[i]; ++i) {
        if (ispunct(inputTxt[i]) || inputTxt[i] == ' ' || inputTxt[i] == '\n') {
            continue;
        } else if (!isalpha(inputTxt[i])) {
            puts("NOT VALID TEXT. TEXT MUST CONTAIN ENGLISH ALPHABET AND PUNCTUATION ONLY.");
            return false;
        } else {
            inputTxt[i] = toupper(inputTxt[i]);
        }
    }

    return true;
}

char getSubstitution(char * txtLetter, char * keyLetter, bool mode) {

    static char vigenereTbl[26][26];

    for (size_t i = 'A'; i <= 'Z'; ++i) {
        for (size_t j = 'A'; j <= 'Z'; ++j) {
            vigenereTbl[i - 65][j - 65] = (i + j) % 26 + 'A';
        }
    }

    if (1 == mode) {
        // encryption logic:
        return vigenereTbl[*keyLetter - 65][*txtLetter - 65];
    } else {
        // decryption logic:
        for (size_t i = 0; i < 26; ++i) {
            if (*txtLetter == vigenereTbl[*keyLetter - 65][i]) {
                char letter = i + 'A';
                return letter;
            }
        }
    }
}

void encrypt(char * inputTxt, char * key, char * const outputTxt) {

    if (!checkKey(key) || !checkInputTxt(inputTxt)) {

        puts("ENCRYPTION OPERATION CANNOT BE DONE. EITHER KEY OR INPUT TXT ARE NOT VALID");
        return;
    } 

    for (size_t i = 0; *inputTxt; ++inputTxt) {
        if (isalpha(*inputTxt)) {

            char letter = getSubstitution(inputTxt, &key[i], 1);
            strncat(outputTxt, &letter, 1);
           
            ++i;
            i %= strlen(key);
        } 
    }

    for (size_t i = 0, j =0; i < strlen(outputTxt); ++i) {
        
        
        if (0 == i % 4) {
            printf("%c", ' ');
            
            if(0 == j % 6) {
                puts("");
            }

            ++j;
        }
        
        printf("%c", outputTxt[i]);
    }
}

void decrypt(char * inputTxt, char * key, char * const outputTxt) {

    if (!checkKey(key) || !checkInputTxt(inputTxt)) {

        puts("ENCRYPTION OPERATION CANNOT BE DONE. EITHER KEY OR INPUT TXT ARE NOT VALID");
        return;
    } 

    for (size_t i = 0; *inputTxt; ++inputTxt) {
        if (isalpha(*inputTxt)) {
            char letter = getSubstitution(inputTxt, &key[i], 0);
            strncat(outputTxt, &letter, 1);
            
            ++i;
            i %= strlen(key);
        } else {
            strncat(outputTxt, inputTxt, 1);

        }
    }

    for (size_t i =0; i < strlen(outputTxt); ++i) {
        
        printf("%c", outputTxt[i]);
    }
}