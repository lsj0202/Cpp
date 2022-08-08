#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

void scan_dir(char *path){
	DIR *d;
	struct dirent* ent;
	struct stat st;
	char buf[256];
	
	printf("*** OPEN %s\n",path);
	
	d=opendir(path);
	
	while((ent =readdir(d)) != NULL){
		printf("%s",ent->d_name);
		
		//ent ->d_name��, "." �̰ų� ".."�̸�, "skip" ���. strcmp �̿�. 
		if(strcmp(ent->d_name,".")==0||strcmp(ent->d_name,"..")==0) //�Լ� ����ü ���ڿ�  
			continue;
			//printf("<<--skip");
		printf("%s\n", ent->d_name);
		
		stat(ent->d_name, &st);
		if(S_ISDIR(st.st_mode)){   //���͸�  
			sprintf(buf, "%s\n %s\n", path, ent ->d_name);
			scan_dir(buf); //���ο� ���, ���� ��� + ���͸� �̸�. 
		}else if(S_ISREG(st.st_mode)){
			// ���� �� Ȯ���ڰ� ".exe" ������ ����"<<--" ǥ�� 
			if(strcmp(ent->d_name,".exe")==0)
				printf("<<--");
			printf("%s \n",ent->d_name);
		}
			
		printf("\n");
	}
	closedir(d);
}
int main(int argc,char * argv){
	scan_dir(".");
	return 0;
}
