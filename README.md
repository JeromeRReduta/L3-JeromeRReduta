# System Calls

The `strace` utility allows us to trace system calls on running programs. We can learn quite a bit about a program just by inspecting its system calls.

(if you don't have strace installed, then do `sudo pacman -Sy strace`)

Here are a few example usages of `strace`:

```bash
# Trace a run of 'ls':
$ strace ls

# Trace only file-related system calls
$ strace -e trace=file ls

# Get a nice summary of unique system calls used
$ strace -c ls

# Search for a specific system call (stat in this case):
$ strace ls 2>&1 | grep '^stat'
# Note that we search the start of the string (^) because the system call's
# name comes first, followed by its parameters and return value.
```


When you run a command, such as `strace cat`, each system call will be printed interactively to your terminal. So the general workflow is: run **strace** on a command, which will then print a list of **system calls**. You can run `strace` on any binary file; if you compile your own C code,  `strace a.out` will display the system calls being used by your code (most likely the calls are invoked by the C library, not your code directly).

## Part I: Tracing System Calls

For the first part of this lab, you will trace several programs and record the results. See detailed instructions below.

1. First, run a trace on `ls`. Record all of the unique system calls (just their names) used by `ls`. To avoid doing a lot of tedious work, you could probably automate most of this with a shell pipeline or command line flag.

(list the syscalls here, use '*' to create a bulleted list in Markdown format)

* read
* write
* close
* stat
* fstat
* mmap
* mprotect
* munmap
* brk
* rt_sigaction
* rt_sigprocmask
* ioctl
* access
* execve
* getdents
* statfs
* arch_prctl
* set_tid_address
* openat
* set_robust_list
* prlimit64

2. How many unique system calls are in your list?

There are 21 system calls in the list.

3. Next, get the examples for `fork` and `readdir` from the schedule page. Go through the code an understand the logic. Then compile them and list their system calls below. Were there any unexpected or interesting results, or any differences in the output?

Fork:
       Thought child would run (though no code in the child block would run below execl()), then parent would run
       The program more or less did that

Fork System Calls (also in forkTrace.txt)

execve("./fork", ["./fork"], 0x7fff9a3d33e0 /* 23 vars */) = 0
brk(NULL)                               = 0x56481c3bb000
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/local/cuda-8.0/lib64/tls/x86_64/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
stat("/usr/local/cuda-8.0/lib64/tls/x86_64/x86_64", 0x7ffc0d36bb10) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/local/cuda-8.0/lib64/tls/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
stat("/usr/local/cuda-8.0/lib64/tls/x86_64", 0x7ffc0d36bb10) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/local/cuda-8.0/lib64/tls/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
stat("/usr/local/cuda-8.0/lib64/tls/x86_64", 0x7ffc0d36bb10) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/local/cuda-8.0/lib64/tls/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
stat("/usr/local/cuda-8.0/lib64/tls", 0x7ffc0d36bb10) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/local/cuda-8.0/lib64/x86_64/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
stat("/usr/local/cuda-8.0/lib64/x86_64/x86_64", 0x7ffc0d36bb10) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/local/cuda-8.0/lib64/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
stat("/usr/local/cuda-8.0/lib64/x86_64", 0x7ffc0d36bb10) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/local/cuda-8.0/lib64/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
stat("/usr/local/cuda-8.0/lib64/x86_64", 0x7ffc0d36bb10) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/local/cuda-8.0/lib64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
stat("/usr/local/cuda-8.0/lib64", {st_mode=S_IFDIR|0755, st_size=4096, ...}) = 0
openat(AT_FDCWD, "tls/x86_64/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "tls/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "tls/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "tls/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "x86_64/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=128788, ...}) = 0
mmap(NULL, 128788, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7fe82e7db000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\260\34\2\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=2030544, ...}) = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fe82e7d9000
mmap(NULL, 4131552, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7fe82e1e3000
mprotect(0x7fe82e3ca000, 2097152, PROT_NONE) = 0
mmap(0x7fe82e5ca000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1e7000) = 0x7fe82e5ca000
mmap(0x7fe82e5d0000, 15072, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7fe82e5d0000
close(3)                                = 0
arch_prctl(ARCH_SET_FS, 0x7fe82e7da4c0) = 0
mprotect(0x7fe82e5ca000, 16384, PROT_READ) = 0
mprotect(0x56481a60b000, 4096, PROT_READ) = 0
mprotect(0x7fe82e7fb000, 4096, PROT_READ) = 0
munmap(0x7fe82e7db000, 128788)          = 0
getpid()                                = 7704
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 0), ...}) = 0
brk(NULL)                               = 0x56481c3bb000
brk(0x56481c3dc000)                     = 0x56481c3dc000
write(1, "Starting up, my PID is 7704\n", 28) = 28
clone(child_stack=NULL, flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD, child_tidptr=0x7fe82e7da790) = 7705
getpid()                                = 7704
write(1, "Hello from the parent! PID = 770"..., 34) = 34
write(1, "PID 7704 waiting for its child ("..., 39) = 39
wait4(-1, [{WIFEXITED(s) && WEXITSTATUS(s) == 0}], 0, NULL) = 7705
--- SIGCHLD {si_signo=SIGCHLD, si_code=CLD_EXITED, si_pid=7705, si_uid=1419, si_status=0, si_utime=0, si_stime=0} ---
write(1, "Child finished executing. Parent"..., 42) = 42
exit_group(0)                           = ?
+++ exited with 0 +++

Readdir:
       Expected readdir to check if the directory exists, and if it does print out all the entries (subdirectories).
       This more or less went that way exactly.

Readdir system calls (also in readdirTrace.txt):

execve("./readdir", ["./readdir"], 0x7ffebe4ab540 /* 23 vars */) = 0
brk(NULL)                               = 0x5612de2a6000
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/local/cuda-8.0/lib64/tls/x86_64/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
stat("/usr/local/cuda-8.0/lib64/tls/x86_64/x86_64", 0x7fff3d09c890) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/local/cuda-8.0/lib64/tls/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
stat("/usr/local/cuda-8.0/lib64/tls/x86_64", 0x7fff3d09c890) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/local/cuda-8.0/lib64/tls/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
stat("/usr/local/cuda-8.0/lib64/tls/x86_64", 0x7fff3d09c890) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/local/cuda-8.0/lib64/tls/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
stat("/usr/local/cuda-8.0/lib64/tls", 0x7fff3d09c890) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/local/cuda-8.0/lib64/x86_64/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
stat("/usr/local/cuda-8.0/lib64/x86_64/x86_64", 0x7fff3d09c890) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/local/cuda-8.0/lib64/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
stat("/usr/local/cuda-8.0/lib64/x86_64", 0x7fff3d09c890) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/local/cuda-8.0/lib64/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
stat("/usr/local/cuda-8.0/lib64/x86_64", 0x7fff3d09c890) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/local/cuda-8.0/lib64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
stat("/usr/local/cuda-8.0/lib64", {st_mode=S_IFDIR|0755, st_size=4096, ...}) = 0
openat(AT_FDCWD, "tls/x86_64/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "tls/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "tls/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "tls/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "x86_64/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=128788, ...}) = 0
mmap(NULL, 128788, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7fa88a9b2000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\260\34\2\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=2030544, ...}) = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fa88a9b0000
mmap(NULL, 4131552, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7fa88a3ba000
mprotect(0x7fa88a5a1000, 2097152, PROT_NONE) = 0
mmap(0x7fa88a7a1000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1e7000) = 0x7fa88a7a1000
mmap(0x7fa88a7a7000, 15072, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7fa88a7a7000
close(3)                                = 0
arch_prctl(ARCH_SET_FS, 0x7fa88a9b14c0) = 0
mprotect(0x7fa88a7a1000, 16384, PROT_READ) = 0
mprotect(0x5612dc881000, 4096, PROT_READ) = 0
mprotect(0x7fa88a9d2000, 4096, PROT_READ) = 0
munmap(0x7fa88a9b2000, 128788)          = 0
openat(AT_FDCWD, ".", O_RDONLY|O_NONBLOCK|O_CLOEXEC|O_DIRECTORY) = 3
fstat(3, {st_mode=S_IFDIR|0755, st_size=4096, ...}) = 0
brk(NULL)                               = 0x5612de2a6000
brk(0x5612de2c7000)                     = 0x5612de2c7000
getdents(3, /* 21 entries */, 32768)    = 664
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 0), ...}) = 0
write(1, "-> .\n", 5)                   = 5
write(1, "-> ..\n", 6)                  = 6
write(1, "-> .git\n", 8)                = 8
write(1, "-> Makefile\n", 12)           = 12
write(1, "-> README.md\n", 13)          = 13
write(1, "-> bonus\n", 9)               = 9
write(1, "-> dirent.h\n", 12)           = 12
write(1, "-> dirstream.h\n", 15)        = 15
write(1, "-> libc-lock.h\n", 15)        = 15
write(1, "-> open-log.c\n", 14)         = 14
write(1, "-> rick-ropen.c\n", 16)       = 16
write(1, "-> roll.txt\n", 12)           = 12
write(1, "-> syscall_32.tbl\n", 18)     = 18
write(1, "-> fork.c\n", 10)             = 10
write(1, "-> .vscode\n", 11)            = 11
write(1, "-> a.out\n", 9)               = 9
write(1, "-> fork\n", 8)                = 8
write(1, "-> forkTrace.txt\n", 17)      = 17
write(1, "-> readdir.c\n", 13)          = 13
write(1, "-> readdir\n", 11)            = 11
write(1, "-> readdirTrace.txt\n", 20)   = 20
getdents(3, /* 0 entries */, 32768)     = 0
close(3)                                = 0
exit_group(0)                           = ?
+++ exited with 0 +++



4. Next, trace several commands you already know and look for new system calls that you haven't seen before (or look up some new commands if you'd like). Describe three system calls below (figure out what they do), and include both the command that generated the system calls as well as the syscall parameters/return values:

syscall 1: execve("/usr/bin/mkdir", ["mkdir"], 0x7ffd6ffa6fb0 /* 20 vars */) = 0

Command used: strace mkdir 2> mkdirTrace.txt
Note: mkdir is an invalid command, as there is no argument after that to define the name of the directory
However, the resulting strace is pretty short and readable, so it still works as an example

According to an online version of the man pages, execve has the following signature:
       int execve(const char *pathname, char *const argv[], char *const envp[]);
 
and executes the program in the given pathname, with the given args and environment map. 
It only returns on failure (https://man7.org/linux/man-pages/man2/execve.2.html). 

I believe the fact that this execve = 0 means that execve returned a 0, signalling a failure. This makes sense to me, since
mkdir (no args) isn't a valid command.


syscall 2: openat(AT_FDCWD, "/usr/lib/perl5/5.32/core_perl/CORE/tls/x86_64/x86_64/libperl.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)

Command used: strace asciiquarium 2> fishTrace.txt

According to the online man pages, openat() is based on open(). The two have the following signatures:

int open(const char *pathname, int flags);
int openat(int dirfd, const char *pathname, int flags);

open() tries to find the file referenced by pathname, and returns either a non-negative int referring to the file, or -1 to signal an error.

openat() does the same, but can work with relative pathnames (https://man7.org/linux/man-pages/man2/open.2.html).

This particular openat() command has returned -1 because the file it's looking for doesn't exist. In addition, it has given an ENOENT error, which means the file doesn't exist (https://man7.org/linux/man-pages/man2/open.2.html).

According to Wikipedia for Programmers, it stands for "Error: NO ENTry/ENTity" (https://stackoverflow.com/questions/19902828/why-does-enoent-mean-no-such-file-or-directory#:~:text=It's%20an%20abbreviation%20of%20Error,than%208%20characters%20in%20symbols.).

syscall 3: write(1, "-> .\n", 5)                   = 5

Command used: strace ./readdir 2> readdirTrace.txt

According to the man pages, write() has the following signature:

 ssize_t write(int fd, const void *buf, size_t count);

 write() prints out the text in buf to a given file descriptor, up to count bytes. Write() returns the number of bytes written, or -1 for an error. If there's no error, write() usually returns the same number as count (i.e. it wrote everything it intended to write), but it may be less if write() is interrupted for some reason.

 In this case, the count arg and the return value are both 5, meaning this write() call wrote the full message. When I ran this command, all the messages I saw seemed complete, too.



5. For your next mission, you are going to try to predict the purpose of a program simply by inspecting its system calls. Go into the `/bin` directory and look for a program/utility you've never used before. Trace it with `strace` and try to understand what the program is doing without reading its documentation.

(I predict program XYZ is performing task ABC...)

(After reading the documentation for program XYZ, I found its purpose is DEF)

## Part II: Intercepting System Calls

Alright, so we have a somewhat reasonable idea of what system calls are: 
privileged functions that are processed in kernel space. Let's imagine that
we want to add our own system call to Linux. The process involves adding a
new entry to the [system call table](./syscall_32.tbl), which is basically
a big list of **function pointers**. This list maps system calls (represented
internally as integers) to their corresponding function implementations. If
we wanted to add a new system call, we'd simply update the table and provide
an implementation. In the past, system calls could be added or modified at 
run time as loadable **kernel modules**, but newer versions of the Linux
kernel protect the system call table (probably a good idea from a security
standpoint).

In this portion of the lab, we will use dynamic loading to intercept user space
programs' system calls and inject code of our own. This allows us to do many
interesting things. You might be wondering how we can intercept system calls --
after all, they are handled in kernel space. While we could certainly modify
the Linux source code and recompile the kernel, we have another option:
`LD_PRELOAD`.

### LD_PRELOAD

The `LD_PRELOAD` environment variable specifies libraries that should be loaded
before a program starts. We also know that most 'system calls'  we use in
our C programs are actually C library functions that call the 'real'
system calls, so we can exploit this fact to intercept the system calls before
they even happen! Something like:

```
┌─────────────┐             ┌─────────────┐             ┌─────────────┐
│ Application │────────────▶│  C Library  │────────────▶│   Kernel    │
└─────────────┘             └─────────────┘             └─────────────┘

                             -- Becomes --

┌─────────────┐             ┌─────────────┐             ┌─────────────┐
│ Application │──┐       ┌─▶│  C Library  │────────────▶│   Kernel    │
└─────────────┘  │       │  └─────────────┘             └─────────────┘
           ┌─────┘       └─────┐
           │  ┌─────────────┐  │
           └─▶│  Our Code   │──┘
              └─────────────┘
```

To do this, we will build a shared object (.so) file, add it to the `LD_PRELOAD`
environment variable, and then intercept any system calls we are interested in.
In fact, we can intercept any call (we could inject code before `printf`, for
instance, if we wanted to).

### File Logger

For our first trick, let's build a loadable library that logs each file opened
by the user. The extra-studious folks out there are probably already thinking
about intercepting calls to `open()` -- and that's just what we'll do!

`open-log.c` logs each call to `open()`. Pay particular attention to the `dlsym()`
function: it finds the original address of `open()` and saves it so we can still
call the original version of the function once we're done messing with the
implementation of `open()`. We also pass the `RTLD_NEXT` option. From the man
pages:

```
       RTLD_NEXT
              Find the next occurrence of the desired symbol in the search order after the current
              object.   This  allows  one to provide a wrapper around a function in another shared
              object, so that, for example, the definition of a function  in  a  preloaded  shared
              object (see LD_PRELOAD in ld.so(8)) can find and invoke the "real" function provided
              in another shared object (or for that matter, the "next" definition of the  function
              in cases where there are multiple layers of preloading).
```

The weird C incantation near the top of the file creates a function pointer to the "original" `open()`:

```
int (*orig_open)(const char * pathname, int flags) = NULL;
```

It can be called like so:

```
(*orig_open)(pathname, flags);
```

Use the provided Makefile to build open-log.so. Once built, we'll add it to our `LD_PRELOAD`
and try it on a **single** command:

```
$ LD_PRELOAD=$(pwd)/open-log.so uptime
open-log.c:27:initialize(): Original open() location: 0x7f7de12d5470
open-log.c:28:initialize(): New open() location: 0x7f7de15ea1b9
open-log.c:33:open(): Opening file: /proc/uptime
open-log.c:33:open(): Opening file: /proc/loadavg
 23:12:21 up 1 day, 13:01,  9 users,  load average: 0.00, 0.00, 0.00
```

You can also make this change more permanent by exporting `LD_PRELOAD`. Then all following commands
will load your shared library:

```
export LD_PRELOAD=$(pwd)/open-log.so
```

**Hypothetically,** let's say you want to make these changes permanent for every user that logs in. To do so, you would add the following line to `/etc/environment` as root:

```
LD_PRELOAD=/full/path/to/the/shared/object.so
```

...but it probably isn't a good idea unless you **really** want your system calls intercepted all the time.

Done

### Rick Ropen()

Using the code provided for the file logger, modify it so that:

1. If the user tries to open any files that end in `.java`, report that they do not exist. Hint: think about what `open()` should return; you'll also need to set the `errno` (see `man errno.h`)

2. If the user opens a `.txt` file, you should instead redirect the request to open `roll.txt` provided in this repo. In other words, if you have a file named `hello.txt` that contains 'Hello world!', when you open it you will see the contents of `roll.txt` instead. [Some Context](https://en.wikipedia.org/wiki/Rickrolling).


## Finishing Up

Check in your lab notebook (edit this README.md file) and code changes to your repo before the deadline.

