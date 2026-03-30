#include <stdio.h>

int main(int argc, char *argv[])
{
    if(argc != 2) {
        printf("ERROR: You need one argument.\n");
        // this is how you abort a program
        return 1;
    }

    int i = 0;
    char letter;
    for(i = 0,letter = argv[1][i]; argv[1][i] != '\0'; i++) {
        letter = argv[1][i];
        switch(letter) {
            case 'a':
                printf("%d: %c\n", i,'A'+32);
                break;

            case 'e':
                printf("%d: %c\n", i,'E'+32);
                break;

            case 'i':
                printf("%d: %c\n", i,'I'+32);
                break;

            case 'o':
                printf("%d: %c\n", i,'O'+32);
                break;

            case 'u':
                printf("%d: %c\n", i,'U'+32);
                break;

            case 'y':
                if(i > 2) {
                    // it's only sometimes Y
                    printf("%d: %c\n", i,'Y'+32);
                }
                break;

            default:
                printf("%d: %c is not a vowel\n", i, letter);
        }
    }
    //  if(argc != 2) return 1;

    // for(int i = 0; argv[1][i] != '\0'; i++) {
    //     char letter = tolower(argv[1][i]);

    //     if(letter == 'a' || letter == 'e' || letter == 'i' || 
    //        letter == 'o' || letter == 'u') {
    //         printf("%d: '%c'\n", i, toupper(letter));
    //     }
    //     else if(letter == 'y' && i > 2) {
    //         printf("%d: 'Y'\n", i);
    //     }
    //     else {
    //         printf("%d: %c is not a vowel\n", i, letter);
    //     }
    // }

    return 0;
}