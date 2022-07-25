#include <iostream>

using namespace std;

const int MAX_N = 12;

int maze[MAX_N][MAX_N] = { 0 };

int n, m;
char w[MAX_N];

int  main() {
    scanf("%d %d", &n, &m);
    scanf("%s", &w);
    for(int i = 0; i < n; i++) {
        scanf("%s", maze[i]);
    }
    for (int i = 0; i < n; i++)
        printf("%s\n", maze[i]);

    return 0;
}
 