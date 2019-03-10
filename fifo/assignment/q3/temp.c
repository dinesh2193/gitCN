#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char ch[100];
	scanf("%s",ch);
	strcat(ch,":");
	strcat(ch,"hjsd");
	printf("%s\n",ch );
}