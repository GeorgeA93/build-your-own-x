#include <iostream>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <sys/mount.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <fcntl.h> 
#include <fstream> 

int TRY(int status, const char *msg) {
 if(status == -1) {
    perror(msg);
    exit(EXIT_FAILURE);
 }
 return status;
}

char* stack_memory() {
  const int stackSize = 65536;
  auto *stack = new (std::nothrow) char[stackSize];

  if (stack == nullptr) {
    printf("Failed to allocate memory \n");
    exit(EXIT_FAILURE);
  }

  return stack+stackSize;
}

template <typename... P> 
int run(P... params) {
  char *args[] = {(char *)params..., (char *)0};
  
  execvp(args[0], args); 
  perror("execvp"); 
  return 0;
}

void setup_root(const char* folder) {
  chroot(folder);
  chdir("/");
}

void setup_variables() {
  clearenv();
  setenv("TERM", "xterm-256color", 0);
  setenv("PATH", "/bin/:/sbin/:usr/bin:/usr/sbin", 0);
}

template <typename Function>
void clone_process(Function&& function, int flags){
 auto pid = TRY(clone(function, stack_memory(), flags, 0), "clone");

 wait(nullptr); 
} 

void setHostName(std::string hostname) {
  sethostname(hostname.c_str(), hostname.size());
}

#define lambda(fn_body) [](void *args) ->int { fn_body; };

int jail(void *args) {
  printf("child pid: %d\n", getpid());
  setHostName("my-container");
  setup_variables();

  setup_root("./root");
  mount("proc", "/proc", "proc", 0, 0); 

  auto runnable = lambda(run("/bin/sh"))

    clone_process(runnable, SIGCHLD);

  umount("/proc");
  return EXIT_SUCCESS;
}

int main() {
  printf("parent pid: %d\n", getpid());
  clone_process(jail, CLONE_NEWPID | CLONE_NEWUTS | SIGCHLD );

  return EXIT_SUCCESS;
}
