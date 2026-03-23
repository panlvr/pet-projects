#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string rotate(int key, string plaintext);

int main(int argc, string argv[])
{

    // Check the number of command-line arguements

    if (argc != 2)
    {
        printf("Ooops, missing a value. Please indicate a key.\n");
        return 1;
    }

    // Check if the CLA is a digit

    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Make the roration

    int key = atoi(argv[1]);
    string plaintext = get_string("plaintext:  ");
    string ciphertext = rotate(key, plaintext);
    if (ciphertext == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    printf("ciphertext: %s\n", ciphertext);
    free(ciphertext);
    return 0;
}

string rotate(int key, string plaintext)
{
    int n = strlen(plaintext);
    string ciphertext = malloc(n + 1);
  
    for (int i = 0; i < n; i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                ciphertext[i] = ((plaintext[i] - 65 + key) % 26) + 'A';
            }
            else
            {
                ciphertext[i] = ((plaintext[i] - 97 + key) % 26) + 'a';
            }
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[n] = '\0';
    return ciphertext;
}
