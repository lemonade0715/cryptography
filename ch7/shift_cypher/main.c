#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PLAINTEXT_FILENAME "plaintext.txt"
#define CIPHERTEXT_FILENAME "ciphertext.txt"

int my_encrypt(int shift);
int my_decrypt(int shift);
extern char *optarg;

int main(int argc, char *argv[])
{
    int shift = 0;
    char opt = 0;
    
    /* Get Command Line Options */
    while ((opt = getopt(argc, argv, "e:d:")) != -1)
    {
        switch (opt)
        {
            case 'e':
                shift = atoi(optarg);
                if (shift >= 0 && shift < 26)
                    my_encrypt(shift);
                return 0;
                
            case 'd':
                shift = atoi(optarg);
                if (shift >= 0 && shift < 26)
                    my_decrypt(shift);
                return 0;
        }
    }
}

int my_encrypt(int shift)
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
        {
            c += shift;
            if (c > 'Z')
                c -= 'Z' - 'A';
        }
        else if (c >= 'a' && c <= 'z')
        {
            c += shift;
            if (c > 'z')
                c -= 'z' - 'a';
        }
        
        /* Input Character */
        fputc(c, ciphertext_fp);
    }
    
    /* Close Files */
    fclose(plaintext_fp);
    fclose(ciphertext_fp);
    
    return 0;
}

int my_decrypt(int shift)
{
    /* Open Files */
    FILE *plaintext_fp = fopen(PLAINTEXT_FILENAME, "w");
    FILE *ciphertext_fp = fopen(CIPHERTEXT_FILENAME, "r");
    
    /* Decrypt */
    char c = 0;
    while ((c = fgetc(ciphertext_fp)) != EOF)
    {
        /* Convert Character */
        if (c >= 'A' && c <= 'Z')
        {
            c -= shift;
            if (c < 'A')
                c += 'Z' - 'A';
        }
        else if (c >= 'a' && c <= 'z')
        {
            c -= shift;
            if (c < 'a')
                c += 'z' - 'a';
        }
        
        /* Input Character */
        fputc(c, plaintext_fp);
    }
    
    /* Close Files */
    fclose(plaintext_fp);
    fclose(ciphertext_fp);
    
    return 0;
}
