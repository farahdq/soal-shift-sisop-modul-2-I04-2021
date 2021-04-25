#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

//Number 3a
int main() {
  pid_t pid, sid;        // Variabel for PID

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while (1) {
   
    // Write Stuff here for 3a
        time_t rawtime;
        struct tm *information;
    
        char buffer[80];
        time(&rawtime);
    
        information = localtime(&rawtime);
    
        strftime(buffer, sizeof(buffer), "%Y-%m-%d_%X", information);

        pid_t child_id;
        child_id = fork();

        if(child_id == 0) 
        {
            char* arg[] = {"mkdir", "-p", buffer, NULL};
            execv("/bin/mkdir", arg);
    
    
    
    sleep(40);
  }
}
