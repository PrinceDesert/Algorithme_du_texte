#include <stdio.h>
#include <string.h>

void brute_force_search(char *x, int m, char *y, int n);

int main()
{
	char *y = "ataatata";
	char *x = "ataataatataatataa";
	brute_force_search(x, strlen(x), y, strlen(y));
	return 0;
}

void brute_force_search(char *x, int m, char *y, int n) {
	int i, j;
	for (j = 0; j <= n - m; ++j) {
		for (i = 0; i < m && x[i] == y[i + j]; ++i);
		if (i >= m) {
			printf("shift : %d\n", j);
			printf("%s\n", y);
			printf("%*s%s\n", j, " ", x);
		}
	}
}
