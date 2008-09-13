#include <cstdio>
#include <cstdlib>
#include <limits.h>

#define RAND()	(rand() & 1)
#define N		21
#define M		5

int game(int n, int m)
{
	int count = 0;
	for (int i = 0; i < n; ++i)
	{
		int t = RAND();
		if (t) {
			++count;
			if (count >= m)
				return 1;
		}
		else {
			count = 0;
		}
	}
	return 0;
}

int main()
{
	int count = 0;
	int total = 0;
	for (int i = 0; i < INT_MAX; ++i) {
		count += game(N, M);
		++total;
		printf("%.5lf\t", (double)count/total);
	}
	return 0;
}

