#include<stdio.h>
int main(){
	char *s1 = "hello";
	char *s2 = "world";
	char buf[20];
	char *s3=NULL;
	int n=10;
	
	sprintf(buf,"%s-%s---%d", s1,s2,n);
	printf("%s\n",buf);
	
	s3 =(char*)malloc(sizeof(char)*50);
	sprintf(s3,"%d - %s", n,s2);
	printf("%s\n",s3);
	free(s3);
	
	return 0;
}
