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
		
		//ent ->d_name이, "." 이거나 ".."이면, "skip" 출력. strcmp 이용. 
		if(strcmp(ent->d_name,".")==0||strcmp(ent->d_name,"..")==0) //함수 구조체 문자열  
			continue;
			//printf("<<--skip");
		printf("%s\n", ent->d_name);
		
		stat(ent->d_name, &st);
		if(S_ISDIR(st.st_mode)){   //디렉터리  
			sprintf(buf, "%s\n %s\n", path, ent ->d_name);
			scan_dir(buf); //새로운 경로, 기존 경로 + 디렉터리 이름. 
		}else if(S_ISREG(st.st_mode)){
			// 파일 끝 확장자가 ".exe" 파일의 끝에"<<--" 표시 
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
