# soal-shift-sisop-modul-2-I04-2021

## MEMBER 
	Hika Pasya Mustofa		          05111942000015
	Farah Dhiah Qorirah		          05111942000018
	Nadhif Bhagawanta Hadiprayitno		  05111942000029
  
## NO 1
# QUESTION :
Once upon a time, there was a steven who lived a mediocre live. Steven had a girlfriend, but they have broken up before getting together. When he was thinking about his ex, he always watches https://www.youtube.com/watch?v=568DH_9CMKI to relieve his sadness. 

In the meantime, Steven hates SISOP Course very much like no other, Few hours after breaking up with his girlfriend, he found another  woman named Stevany, but Stevany is the opposite of him because she likes SISOP course very much. Steven wanted to look good at SISOP course to impress her.

On her birthday, he wanted to give her a zip file containing all things that she likes. He wanted the zip to be organized by making a new folder for each file extension. 
(a) Because she likes the letter Y so much, He wanted the name of the folder as Musyik for mp3, Fylm for mp4, and Pyoto for jpg 
(b) For music, he downloads it from the link below, so are the cases for films and photos. 
(c) he didn’t want the folder to contain the zip files so he extracts the files first after downloading it. 
(d) moving it to the folder that has been made (only the files).
(e) When it’s her birthday, all folder will be zipped with the name Lopyu_Stevany.zip and all the folders will be deleted. (Only the zip remains).
(f) To make his life easier, he wants all of the above to run automatically 6 hours before her birthday (except for point e of course)
Steven is asking your help who is the greatest of the greats of sisop master to help get her heart. Help him!!!

Note:
Stevany’s birthday : 09 April Pukul 22.22 WIB
All points are run by 1 script on the background, that includes downloading the zip file. So you just need to run 1 script and change the time and date to check the result.

# ANSWER
	void downloadfile(char download_link[],char filename[]) {
   	char*argv[] = {"wget","--no-check-certificate", download_link, "-O", filename, "-q", NULL};
    	execv("/bin/wget",argv);
    	}
this function will execute wget to download file, the file will downloaded from 'download_link'
	
	void unzipfile(char filename[]){
    	char*argv[] = {"unzip", "-qq", filename,NULL};
    	execv ("/bin/unzip",argv);
    	}
this function will unzip to extract the file

	void downloadandunzipfiles(pid_t child_id, int*status, char*filename[]){
    	char*download_links[] = {"https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download","https://drive.google.com/uc?		id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download","https://drive.google.com/uc?id=ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"};
    	for(int i=0; i<total_folder;i++){
    	if((child_id = fork()) == 0)
   	 downloadfile(download_links[i], filename[i]);
   	while(wait(status)>0);
    	if((child_id = fork()) == 0)
   	 unzipfile(filename[i]);
   	 while(wait(status)>0);
    	 }
	}
this function will loop 3 times to download file in array 'download_link'. in every loop will fork 2 times. every child call downloadfile() function and unzip() function.

	void removeExtractedFolder(pid_t child_id, int*status, char*foldername[]) {
    	if((child_id = fork()) == 0){
   	 char*argv[] = {"rm", "-rf", foldername[0], foldername[1], foldername[2], NULL};
   	 execv("/bin/rm",argv);
   	 }
   	 while(wait(status)>0);
    	}
this function will do fork so the child execute remove folder. after the file being extracted, the folder become empty.

	void browserFolderthenMoveFiles(int*status,char foldername[],char stevany_foldername[]){
    	DIR*dir=opendir(foldername);
    	struct dirent*drent;
    	if (dir != NULL) {
   	while ((drent=readdir(dir)))
	moveFile(drent,status,foldername,stevany_foldername);
   	 (void)closedir (dir);
   	 } else perror ("Couldn't open the directory");
    	}
this function do the iteration foe every file in the directory. every file is called by movefile()function. 

	void moveFile(struct dirent*drent, int*status, char foldername[], char stevany_foldername[]) {
    	pid_t child_move=fork();
    	if (child_move == 0 && (strcmp(drent->d_name, ".") ==0||strcmp(drent->d_name,"..")==0))
    	exit(EXIT_SUCCESS);
    	if(child_move == 0){
   	 char filepath[256];
   	 strcpy(filepath,foldername);
   	 strcat(filepath,"/");
   	 strcat(filepath,drent->d_name);
   	 char*argv[]={"mv",filepath,stevany_foldername,NULL};
   	 execv("/bin/mv",argv);
   	 }
    	 while(wait(status)>0);
    	 }
this function will do fork where the child is in the string filepath form that point path from file that will move, we use it as argument mv that will be exec. 
'.' / '..' means no need to add some file.

	void makeDirectories(pid_t child_id, int*status, char*foldername[], char*stevany_foldername[]) {
    	 if((child_id=fork())==0){
   	  char*argv[] = {"mkdir", "-p", stevany_foldername[0],stevany_foldername[1],stevany_foldername[2], NULL};
   	  execv("/bin/mkdir",argv);
   	  }
    	 while (wait(status)>0);
    	 }
this function will do fork, the child execute mkdir for every folder that desired.

	void zipstevanyfolders(pid_t child_id, int*status, char*stevany_foldername[], char zip_name[]){
    	if((child_id=fork())==0){
    	 char*argv[]={"zip","rmvq", zip_name, stevany_foldername[0], stevany_foldername[1],stevany_foldername[2],NULL};
    	 execv("/bin/zip",argv);
    	 }
    	 while(wait(status)>0);
    	}
this function will do fork, the child execute zip to archive based on the question requested.

	void stevany(pid_t child_id, char*stevany_foldername[]) {
    	int status;
    	char*filename[] = {"FILM.zip", "MUSIC.zip", "PHOTO.zip"};
    	char*foldername[] = {"FILM", "MUSIC", "PHOTO"};
	  makeDirectories(child_id, &status, foldername, stevany_foldername);
    		downloadandunzipfiles(child_id,&status,filename);
    		for(int i=0;i<total_folder;i++)
   	 	browserFolderthenMoveFiles(&status, foldername[i], stevany_foldername[i]);
   	 	removeExtractedFolder(child_id, &status, foldername);
    	}
this function will call another function to create new folder, download file then unzip file. After that will move file that already downloaded into the new folder that desired.

	int isNowStevanyBirthday(int day, int month){
    	const int stev_b_day=9;
    	const int stev_b_month = 3;
    	return stev_b_day == day&&stev_b_month==month;
    	}
this function is to set the stevany birthday date.  check is the stevany birthday is happened now or 6 hours before.

	void runDaemon(int*status){
   	 pid_t child_id;
    	 const unsigned Sleep_Interval_Seconds = 1;
   	 char*stevany_foldername[]={"Fylm", "Musyik", "Pyoto"};
    	 const int stev_b_hour = 22;
    	 const int stev_b_min = stev_b_hour;
    	 while(1){
   	 time_t now = time (NULL);
   	 struct tm*nowLocal = localtime(&now);
   	 
   	 if(isNowStevanyBirthday(nowLocal->tm_mday,nowLocal->tm_mon) && stev_b_hour == nowLocal->tm_hour && stev_b_min == nowLocal->tm_min && nowLocal->tm_sec == 0)
   	 zipstevanyfolders(child_id, status, stevany_foldername, "Lopyu_Stevany.zip");
   	 else if(isNowStevanyBirthday(nowLocal->tm_mday, nowLocal->tm_mon)&& stev_b_hour-6 == nowLocal->tm_hour && stev_b_min == nowLocal->tm_min&& nowLocal->tm_sec == 0)
   	 stevany(child_id,stevany_foldername);
   	 while(wait(status)>0);
   	 sleep (Sleep_Interval_Seconds);
   		 }
   	 }
this function will loop every second. after that it will check is the stevany birthday is happened now or 6 hours before using isNowStevanyBirthday() function. if it is 6 hours before stevany birthday it will call stevany() function. and if stevany birthday is happenened now, it will call zipstevanyfolder() function.

	int main (){
    	const char workingDir[]= "/home/farahdq/soal-shift-2/soal1";
    	pid_t child_id, sid;
    	int status;
    	if((child_id=fork())>0)
    	exit(EXIT_SUCCESS);
    	umask(0);
    	sid=setsid();
    	if(sid<0||chdir(workingDir))
    	exit(EXIT_FAILURE);
    	close (STDIN_FILENO);
    	close (STDOUT_FILENO);
    	close(STDERR_FILENO);
    	runDaemon(&status);
    	return 0;
	}
this function will do fork, kill parent, do umask(), and ask the session id. the current dir become dir repo local. and all of the output (file) after executed will placed in /home/farahdq/soal-shift-2/soal1
