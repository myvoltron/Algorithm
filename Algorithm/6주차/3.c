#include <stdio.h>
#include <stdlib.h>

int findK(char* YNstr, int a, int b, int n);
int rFindK(char* YNstr, int a, int b, int n, int idx);

int main(void)
{
	int a, b, n, k = 0;
	scanf("%d %d %d", &a, &b, &n);
	char* YNstr = (char*)malloc(sizeof(char) * (n + 1));
	scanf("%s", YNstr);

	
	// k = findK(YNstr, a, b, n);
	k = rFindK(YNstr, a, b, n, 0);
	printf("%d", k);
	return 0;
}

/*
10 20 3
NNY
*/

int findK(char* YNstr, int a, int b, int n)
{
	for (int i = 0; i < n; i++)
	{
		int mid = (a + b) / 2;
		if (YNstr[i] == 'Y')
			a = mid + 1;
		else if (YNstr[i] == 'N')
			b = mid;

		if (a == b)
			break;
	}

	return a; 
}
int rFindK(char* YNstr, int a, int b, int n, int idx)
{
	if (a == b)
		return a;

	if (idx < n)
	{
		int mid = (a + b) / 2;
		if (YNstr[idx] == 'Y')
			return rFindK(YNstr, mid + 1, b, n, ++idx);
		else if (YNstr[idx] == 'N')
			return rFindK(YNstr, a, mid, n, ++idx);
	}
}
