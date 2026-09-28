#include <stdio.h>
#include <string.h>

#define d 256
#define q 101

void rabinKarp(char text[], char pat[])
{
    int n = strlen(text), m = strlen(pat);
    int i, j, p = 0, t = 0, h = 1;

    for (i = 0; i < m - 1; i++)
        h = (h * d) % q;

    for (i = 0; i < m; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + text[i]) % q;
    }

    for (i = 0; i <= n - m; i++) {
        if (p == t) {
            for (j = 0; j < m && text[i + j] == pat[j]; j++);
            if (j == m)
                printf("Pattern found at index %d\n", i);
        }

        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            if (t < 0) t += q;
        }
    }
}

int main()
{
    char text[] = "ABCCDDAEFG";
    char pat[] = "CDD";

    rabinKarp(text, pat);
    return 0;
}