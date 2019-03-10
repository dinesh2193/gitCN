#include<stdio.h>
#include<stdlib.h>
int compare_upto_colon(char *a,char *b)
{
	int i=0;
	while(b[i]!=':')
	{
		if(a[i]!=b[i])
		{
			return 0;
		}
		i++;
	}
	return 1;
}
int main()
{
	char a[10]="2345";
	int b = atoi(a);
	printf("%d\n",b);
	return 0;
}