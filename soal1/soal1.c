#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define
void downloadfile(char download_link[],char filename[]) 
  {
	char*argv[] = {"wget","--no-check-certificate", download_link, "-O", filename, "-q", NULL};
	execv("/bin/wget",argv);
	}
void moveFile(struct dirent*drent, int*status, char foldername[],char stevany_foldername[]) {
	pid_t child_move=fork();
	if (child_move == 0 && (strcmp(drent->d_name, ".") ==0||strcmp(drent->d_name,"..")==0))
	exit(EXIT_SUCCESS);
	if(child_move == 0)
    {
		char filepath[256];
		strcpy(filepath,foldername);
		strcat(filepath,"/");
		strcat(filepath,drent->d_name);
		char*argv[]={"mv",filepath,stevany_foldername,NULL};
		execv("/bin/mv",argv);
		}
	while(wait(status)>0);
	}
void browserFolderthenMoveFiles(int*status,char foldername[],char stevany_foldername[]){
	DIR*dir=opendir(foldername);
	struct dirent*drent;
	if (dir != NULL) {
		while ((drent=readdir(dir)))
		moveFile(drent,status,foldername,stevany_foldername);
		(void)closedir (dir);
		} else perror("Couldn't open the directory");
	}
void removeExtractedFolder(pid_t child_id, int*status, char*foldername[]) 
  {
	if((child_id = fork()) == 0){
		char*argv[] = {"rm", "-rf", foldername[0], foldername[1],foldername[2], NULL};
		execv("/bin/rm",argv);
		}
		while(wait(status)>0);
	}
void unzipfile(char filename[])
  {
	char*argv[] = {"unzip", "-qq", filename,NULL};
	execv ("/bin/unzip",argv);
	}
return 0;
