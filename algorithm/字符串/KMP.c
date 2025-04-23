#include <stdio.h>
#define MAX 1000002
char s_long[MAX];
char s_mode[MAX];
int lps[MAX];

int main()
{
    int n_long, n_mode, i, len;

    // input
    gets(s_long);
    gets(s_mode);

    // lps auxitory array
    i = 1, len = 0;
    lps[0] = 0;
    while(s_mode[i] != '\0') {
        if (s_mode[i] == s_mode[len]) {
            lps[i] = len + 1;
            i ++, len ++;
        } else if (len == 0) {
            lps[i] = 0;
            i ++;
        } else {
            len = lps[len - 1];
        }
    }

    // scanning
    i = 0, len = 0;
    while (s_long[i] != '\0') {
        if (s_long[i] == s_mode[len]) {
            i ++, len ++;
            if (s_mode[len] == '\0') {
                printf("%d\n", i - len + 1);
                len = lps[len - 1];
            }
        } else if (len > 0){
            len = lps[len - 1];
        } else {
            i ++;
        }
    }

    // output
    for (i = 0; s_mode[i] != '\0'; i ++) {
        printf("%d", lps[i]);
        if (s_mode[i + 1] != '\0'){
            putchar(' ');
        }
    }
    putchar('\n');


    return 0;
}