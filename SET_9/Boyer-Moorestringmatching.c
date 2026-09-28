#include <stdio.h>
#include <string.h>

#define NOCHARS 256

void badChar(char pat[], int m, int bad[])
{
    int i;
    for (i = 0; i < NOCHARS; i++)
        bad[i] = -1;

    for (i = 0; i < m; i++)
        bad[(unsigned char)pat[i]] = i;
}

void boyerMoore(char text[], char pat[])
{
    int n = strlen(text), m = strlen(pat);
    int bad[NOCHARS], s = 0, j;

    badChar(pat, m, bad);

    while (s <= n - m) {
        j = m - 1;

        while (j >= 0 && pat[j] == text[s + j])
            j--;

        if (j < 0) {
            printf("Pattern found at index %d\n", s);
            s += (s + m < n) ? m - bad[(unsigned char)text[s + m]] : 1;
        } else {
            int shift = j - bad[(unsigned char)text[s + j]];
            s += (shift > 1) ? shift : 1;
        }
    }
}

int main()
{
    char text[] = "ABAAABCD";
    char pat[] = "ABC";

    boyerMoore(text, pat);
    return 0;
}