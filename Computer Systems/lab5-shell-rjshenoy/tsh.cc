// 
// tsh - A tiny shell program with job control
// 
// <Put your name and login ID here>
// Rahul Shenoy

using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string>

#include "globals.h"
#include "jobs.h"
#include "helper-routines.h"

//
// Needed global variable definitions
//

static char prompt[] = "tsh> ";
int verbose = 0;

//
// You need to implement the functions eval, builtin_cmd, do_bgfg,
// waitfg, sigchld_handler, sigstp_handler, sigint_handler
//
// The code below provides the "prototypes" for those functions
// so that earlier code can refer to them. You need to fill in the
// function bodies below.
// 

void eval(char *cmdline);
int builtin_cmd(char **argv);
void do_bgfg(char **argv);
void waitfg(pid_t pid);

void sigchld_handler(int sig);
void sigtstp_handler(int sig);
void sigint_handler(int sig);

//
// main - The shell's main routine 
//
int main(int argc, char **argv) 
{
  int emit_prompt = 1; // emit prompt (default)

  //
  // Redirect stderr to stdout (so that driver will get all output
  // on the pipe connected to stdout)
  //
  dup2(1, 2);

  /* Parse the command line */
  char c;
  while ((c = getopt(argc, argv, "hvp")) != EOF) {
    switch (c) {
    case 'h':             // print help message
      usage();
      break;
    case 'v':             // emit additional diagnostic info
      verbose = 1;
      break;
    case 'p':             // don't print a prompt
      emit_prompt = 0;  // handy for automatic testing
      break;
    default:
      usage();
    }
  }

  //
  // Install the signal handlers
  //

  //
  // These are the ones you will need to implement
  //
  Signal(SIGINT,  sigint_handler);   // ctrl-c
  Signal(SIGTSTP, sigtstp_handler);  // ctrl-z
  Signal(SIGCHLD, sigchld_handler);  // Terminated or stopped child

  //
  // This one provides a clean way to kill the shell
  //
  Signal(SIGQUIT, sigquit_handler); 

  //
  // Initialize the job list
  //
  initjobs(jobs);

  //
  // Execute the shell's read/eval loop
  //
  for(;;) {
    //
    // Read command line
    //
    if (emit_prompt) {
      printf("%s", prompt);
      fflush(stdout);
    }

    char cmdline[MAXLINE];
      
    if ((fgets(cmdline, MAXLINE, stdin) == NULL) && ferror(stdin)) {
      app_error("fgets error");
    }
    //
    // End of file? (did user type ctrl-d?)
    //
    if (feof(stdin)) {
      fflush(stdout);
      exit(0);
    }

    //
    // Evaluate command line
    //
    eval(cmdline);
    fflush(stdout);
    fflush(stdout);
  } 

  exit(0); //control never reaches here
}

void unix_error(char *msg){
    fprintf(stdout, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

  
/////////////////////////////////////////////////////////////////////////////
//
// eval - Evaluate the command line that the user has just typed in
// 
// If the user has requested a built-in command (quit, jobs, bg or fg)
// then execute it immediately. Otherwise, fork a child process and
// run the job in the context of the child. If the job is running in
// the foreground, wait for it to terminate and then return.  Note:
// each child process must have a unique process group ID so that our
// background children don't receive SIGINT (SIGTSTP) from the kernel
// when we type ctrl-c (ctrl-z) at the keyboard.
//
void eval(char *cmdline) 
{
    /* Parse command line */
    //
    // The 'argv' vector is filled in by the parseline
    // routine below. It provides the arguments needed
    // for the execve() routine, which you'll need to
    // use below to launch a process.
    //
    char *argv[MAXARGS];

    //
    // The 'bg' variable is TRUE if the job should run
    // in background mode or FALSE if it should run in FG
    //
    
    //for signal blocking (of SIGCHLD)
    sigset_t mask;

    
    //keep track of pid
    int pid = fgpid(jobs);
    
    int bg = parseline(cmdline, argv); 
    if (argv[0] == NULL)  
        return;   /* ignore empty lines */

    struct job_t *job;
    //if its not a builtin command 
    if (builtin_cmd(argv) == 0){
        
        //block signal - to make sure job is not deleted before it is added
        sigemptyset (&mask); // cleans up sets
        sigaddset (&mask, SIGCHLD); // adds signal SIGCHLD to set
        sigprocmask ( SIG_BLOCK, &mask, NULL ); // // blocks signal in the set
        
        if((pid = fork()) < 0){
            unix_error("FORKING ERROR");
        }
        else if (pid == 0){
            //in child
            
            //unblock signal
            sigprocmask ( SIG_UNBLOCK, &mask, NULL );
            
            //change the child's process group ID to be equal to its pid
            //special case of argument 0: process ID of indicated process is used in both
            setpgid ( 0, 0 );
            
            //use -p b/c it uses the environemnt path variable to search for the executable file to execute
            execvp(argv[0], argv); //shouldn't return unless there's an error
            printf("%s: Command not found\n", argv[0]);
            exit(0);
        }
        //parent process
        addjob(jobs, pid, bg ? BG : FG, cmdline);
        
        //unblock signal after job is added
        sigprocmask ( SIG_UNBLOCK, &mask, NULL );
        //wait if its not a background process
        if (!bg){
            waitfg(pid);
        } else {
            job = getjobpid(jobs, pid);
            //status message
            printf("[%d] (%d) %s", (job->jid), job->pid, cmdline);
        }
    }

    return;
}


/////////////////////////////////////////////////////////////////////////////
//
// builtin_cmd - If the user has typed a built-in command then execute
// it immediately. The command name would be in argv[0] and
// is a C string. We've cast this to a C++ string type to simplify
// string comparisons; however, the do_bgfg routine will need 
// to use the argv array as well to look for a job number.
//
int builtin_cmd(char **argv) 
{
    string cmd(argv[0]);
    
    if (strcmp(argv[0], "quit") == 0){
        exit(0);
    }
    else if (strcmp(argv[0], "fg") == 0){
        //foreground command
        do_bgfg(argv);
        return 1;
    }
    else if (strcmp(argv[0], "bg") == 0){
        //background command
        do_bgfg(argv);
        return 1;
    }
    else if(strcmp(argv[0], "jobs") == 0){
        //jobs command
        listjobs(jobs);
        return 1;
    }

    return 0;     /* not a builtin command */
}

/////////////////////////////////////////////////////////////////////////////
//
// do_bgfg - Execute the builtin bg and fg commands
//

//
//- The bg <job> command restarts <job> by sending it a SIGCONT signal, and then runs it in
//the background. The <job> argument can be either a PID or a JID.
//- The fg <job> command restarts <job> by sending it a SIGCONT signal, and then runs it in
//the foreground. The <job> argument can be either a PID or a JID.

void do_bgfg(char **argv) 
{
    struct job_t *jobp=NULL;

    /* Ignore command if no argument */
    if (argv[1] == NULL) {
    printf("%s command requires PID or %%jobid argument\n", argv[0]);
    return;
    }

    /* Parse the required PID or %JID arg */
    if (isdigit(argv[1][0])) {
        pid_t pid = atoi(argv[1]);
        if (!(jobp = getjobpid(jobs, pid))) {
            printf("(%d): No such process\n", pid);
            return;
        }
    }
    else if (argv[1][0] == '%') {
        int jid = atoi(&argv[1][1]);
        if (!(jobp = getjobjid(jobs, jid))) {
          printf("%s: No such job\n", argv[1]);
          return;
        }
    }	    
    else {
        printf("%s: argument must be a PID or %%jobid\n", argv[0]);
        return;
    }

    //
    // You need to complete rest. At this point,
    // the variable 'jobp' is the job pointer
    // for the job ID specified as an argument.
    //
    // Your actions will depend on the specified command
    // so we've converted argv[0] to a string (cmd) for
    // your benefit.
    //
    string cmd(argv[0]);

    int pid = jobp->pid;
    kill(-pid, SIGCONT); //-pid sends its to the entire foreground process group
    
    if (!strcmp(argv[0],"fg")){
        jobp->state = FG; // change job to foreground
        waitfg(jobp->pid); // waits
    }
    else{
        jobp->state = BG; /// changes to background
        
        //print status
        printf("[%d] (%d) %s", (jobp->jid), jobp->pid, jobp->cmdline);
    }

    return;
}

/////////////////////////////////////////////////////////////////////////////
//
// waitfg - Block until process pid is no longer the foreground process
//
void waitfg(pid_t pid)
{
    struct job_t *job = getjobpid(jobs,pid); // grab job
    if (pid != 0 && job != NULL){
        while (job->state == FG){ // if job is in foreground, sleep
            sleep(1);
        }
    }
    return;
}

/////////////////////////////////////////////////////////////////////////////
//
// Signal handlers
//


/////////////////////////////////////////////////////////////////////////////
//
// sigchld_handler - The kernel sends a SIGCHLD to the shell whenever
//     a child job terminates (becomes a zombie), or stops because it
//     received a SIGSTOP or SIGTSTP signal. The handler reaps all
//     available zombie children, but doesn't wait for any other
//     currently running children to terminate.  
//
void sigchld_handler(int sig) 
{
    int pid = fgpid(jobs);
    int status;
    
    //if not a single child process has been terminated WNOHANG is true ... concurrency
    //suspends execution of process until its in wait set or it has become terminated or stopped
    //WNOHANG | WUNTRACED returns 0 if no of the child processes have been terminated or stopped, or returns PID of terminated or stopped process
    
    //waitpid checks if there is any zombie process
    while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED))>0){
        if (WIFSTOPPED(status)){ 
            //returns true if a child is stopped
            //change state if stopped
            getjobpid(jobs, pid)->state = ST;
            int jid = pid2jid(pid);
            printf("Job [%d] (%d) stopped by signal %d\n", jid, pid, WSTOPSIG(status));
        }  
        else if (WIFSIGNALED(status)){
            //returns true if a child process terminated because of a signal
            //delete is signaled
            int jid = pid2jid(pid);  
            printf("Job [%d] (%d) terminated by signal %d\n", jid, pid, WTERMSIG(status));
            deletejob(jobs, pid);
        }  
        else if (WIFEXITED(status)){
            //returns true if the child is terminated normally via exit or rtn
            //exited
            deletejob(jobs, pid);  
        }  
        
    }
    
    return;
}

/////////////////////////////////////////////////////////////////////////////
//
// sigint_handler - The kernel sends a SIGINT to the shell whenver the
//    user types ctrl-c at the keyboard.  Catch it and send it along
//    to the foreground job.  
//
void sigint_handler(int sig) 
{
    int pid = fgpid(jobs);
    
    if (pid != 0) {     
        int success = kill(-pid, sig); //-pid sends its to the entire foreground process group
        if (success < 0){
			//error
			unix_error("kill error");
        }
    }
    return;
}

/////////////////////////////////////////////////////////////////////////////
//
// sigtstp_handler - The kernel sends a SIGTSTP to the shell whenever
//     the user types ctrl-z at the keyboard. Catch it and suspend the
//     foreground job by sending it a SIGTSTP.  
//
void sigtstp_handler(int sig) 
{
  int pid = fgpid(jobs);
    
    if (pid != 0) {     
        int success = kill(-pid, sig); //-pid sends its to the entire forgrounf process group
        if (success < 0){
			//error
			unix_error("kill error");
        }
    }
    return;
}

/*********************
 * End signal handlers
 *********************/




