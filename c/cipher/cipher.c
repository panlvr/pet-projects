#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool validation(string key);
string cipher(string key, string plaintext);

int main(int argc, string argv[])
{

    // Validate the command-line arguements

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];
    if (!validation(key))
    {
        return 1;
    }

    // Get the plaintext and cipher it

    string plaintext = get_string("plaintext:  ");
    string ciphertext = cipher(key, plaintext);
    printf("ciphertext: %s\n", ciphertext);
}

bool validation(string key)
{
    int n = strlen(key);

    if (n != 26)
    {
        printf("The key must be 26 letters\n");
        return false;
    }

    for (int i = 0; i < n; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("The key must be alphabetical\n");
            return false;
        }
        for (int j = i + 1; j < n; j++)
        {
            if (tolower(key[i]) == tolower(key[j]))
            {
                printf("All the characters must be unique\n");
                return false;
            }
        }
    }
    return true;
}

string cipher(string key, string plaintext)
{
    int n = strlen(plaintext);
    string ciphertext = malloc(n + 1);

    for (int i = 0; i < n; i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (islower(plaintext[i]))
            {
                int index = plaintext[i] - 'a';
                ciphertext[i] = tolower(key[index]);
            }
            else
            {
                int index = plaintext[i] - 'A';
                ciphertext[i] = toupper(key[index]);
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