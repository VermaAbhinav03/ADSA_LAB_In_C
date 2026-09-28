#include <stdio.h>
#include <string.h>

void KMP(char text[], char pat[])
{
    int n = strlen(text), m = strlen(pat);
    int lps[m], i, j = 0, len = 0;

    lps[0] = 0;
    for (i = 1; i < m; ) {
        if (pat[i] == pat[len])
            lps[i++] = ++len;
        else if (len)
            len = lps[len - 1];
        else
            lps[i++] = 0;
    }

    i = 0;
    while (i < n) {
        if (text[i] == pat[j]) {
            i++;
            j++;
        }
        if (j == m) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        }
        else if (i < n && text[i] != pat[j]) {
            if (j) j = lps[j - 1];
            else i++;
        }
    }
}

int main()
{
    char text[] = "ABABDABACDABABCABAB";
    char pat[] = "ABABCABAB";

    KMP(text, pat);
    return 0;
}