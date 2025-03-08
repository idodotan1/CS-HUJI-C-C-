#include "cipher.h"
#define NUM_LETTERS 26
/// IN THIS FILE, IMPLEMENT EVERY FUNCTION THAT'S DECLARED IN cipher.h


// See full documentation in header file
void cipher (char s[], int k)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            s[i] = (((s[i] - 'A' + k) % NUM_LETTERS) + 'A');
            if (s[i] < 'A')
            {
                s[i] += NUM_LETTERS;
            }
        } else if (s[i] >= 'a' && s[i] <= 'z')
        {
            s[i] = (((s[i] - 'a' + k) % NUM_LETTERS) + 'a');
            if (s[i] < 'a')
            {
                s[i] += NUM_LETTERS;
            }
        }
    }
}

// See full documentation in header file
void decipher (char s[], int k)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            s[i] = ((s[i] - 'A' - k) % NUM_LETTERS) + 'A';
            if (s[i] < 'A')
            {
                s[i] += NUM_LETTERS;
            }
        } else if (s[i] >= 'a' && s[i] <= 'z')
        {
            s[i] = ((s[i] - 'a' - k) % NUM_LETTERS) + 'a';
            if (s[i] < 'a')
            {
                s[i] += NUM_LETTERS;
            }
        }
    }
}
