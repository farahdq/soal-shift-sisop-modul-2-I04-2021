#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main() {
  pid_t child1_id;
  int status1;
  child1_id = fork();
  
  if (child1_id < 0) {
    exit(EXIT_FAILURE); // failing in making a process will result in stopping the program
  }

  if (child1_id == 0) {
    char *argv[] = {"mkdir", "-p", "/home/zulu/modul2/petshop", NULL};
    execv("/bin/mkdir", argv);
  } else {
    while ((wait(&status1)) > 0);
    pid_t child2_id;
    int status2;
    child2_id = fork();
    
    if (child2_id < 0){
        exit(EXIT_FAILURE);
    }
    if (child2_id == 0){
        char *argv[] = {"unzip", "pets", "-d", "/home/zulu/modul2/petshop", NULL};
        execv("/bin/unzip", argv);
    }    else {
        while ((wait(&status2)) > 0);
        /*char *argv[] = {"find", "/home/zulu/modul2/petshop", "-type", "d", "-delete", NULL};
        execv("/usr/bin/find", argv);*/
        char *argv[] = {"rm", "-r", "/home/zulu/modul2/petshop/apex_cheats","/home/zulu/modul2/petshop/musics", "/home/zulu/modul2/petshop/unimportant_files" ,NULL};
        execv("/usr/bin/rm", argv);
    }
  }
}


