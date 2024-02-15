#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PLAINTEXT_FILENAME "plaintext.txt"
#define CIPHERTEXT_FILENAME "ciphertext.txt"
#define KEY_FILENAME "key.txt"

int my_encrypt(char *key);
int my_decrypt(char *key);
char uppercase(char c);
char lowercase(char c);
int my_index(char c);

int main(int argc, char *argv[])
{
    char opt = 0;
    
    /* Get the Key */
    char key[27] = {0};
    FILE *key_fp = fopen(KEY_FILENAME, "r");
    fgets(key, 27, key_fp);
    
    /* Get Command Line Options */
    while ((opt = getopt(argc, argv, "ed")) != -1)
    {
        switch (opt)
        {
            case 'e':
                my_encrypt(key);
                return 0;
                
            case 'd':
                my_decrypt(key);
                return 0;
        }
    }
}

int my_encrypt(char *key)
{
    /* Open Files */
    FILE *plaintext_fp = fopen(PLAINTEXT_FILENAME, "r");
    FILE *ciphertext_fp = fopen(CIPHERTEXT_FILENAME, "w");
    
    /* Encrypt */
    char c = 0;
    while ((c = fgetc(plaintext_fp)) != EOF)
    {
        /* Convert Character */
        if (c >= 'A' && c <= 'Z')
            c = key[my_index(c)];
        else if (c >= 'a' && c <= 'z')
            c = lowercase(key[my_index(c)]);
        
        /* Input Character */
        fputc(c, ciphertext_fp);
    }
    
    /* Close Files */
    fclose(plaintext_fp);
    fclose(ciphertext_fp);
    
    return 0;
}

int my_decrypt(char *key)
{
    /* Open Files */
    FILE *plaintext_fp = fopen(PLAINTEXT_FILENAME, "w");
    FILE *ciphertext_fp = fopen(CIPHERTEXT_FILENAME, "r");
    
    /* Decrypt */
    char c = 0;
    char *position = 0;
    while ((c = fgetc(ciphertext_fp)) != EOF)
    {
        /* Convert Character */
        if (c >= 'A' && c <= 'Z')
        {
            if ((position = strchr(key, c)) == NULL)
                return 1;
            c = 'A' + (int)(position - key);
        }
        else if (c >= 'a' && c <= 'z')
        {
            if ((position = strchr(key, uppercase(c))) == NULL)
                return 1;
            c = 'a' + (int)(position - key);
        }
        
        /* Input Character */
        fputc(c, plaintext_fp);
    }
    
    /* Close Files */
    fclose(plaintext_fp);
    fclose(ciphertext_fp);
    
    return 0;
}

char uppercase(char c)
{
    if (c >= 'a' && c <= 'z')
        return (c - 'a' + 'A');
    return c;
}

char lowercase(char c)
{
    if (c >= 'A' && c <= 'Z')
        return (c - 'A' + 'a');
    return c;
}

int my_index(char c)
{
    if (c >= 'a' && c <= 'z')
        return (c - 'a');
    else if (c >= 'A' && c <= 'Z')
        return (c - 'A');
    return -1;
}
