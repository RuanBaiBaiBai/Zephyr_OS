#include <stdio.h>


int main()
{
	int i, j, n;
	printf("\nPlease Enter n:");
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= 2 * n + i - 3; j++)
			if (j == n - i + 1 || j > n - i + 1 && (i == 1 || i == n))
				printf("*");
			else
				printf(" ");
		printf("*\n");
	}
}
