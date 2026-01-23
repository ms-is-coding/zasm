#include "zasm.h"
#include <string.h>
#include <syscall.h>

int get_syscall(zasm_token t) {
  const char *name = t.start;
  switch (name[0]) {
    case 'a':
      if (strcmp(name + 1, "ccess")) return SYS_access;
      else if (strcmp(name + 1, "larm")) return SYS_alarm;
      else if (strcmp(name + 1, "ccept")) return SYS_accept;
      else if (strcmp(name + 1, "rch_prctl")) return SYS_arch_prctl;
      else if (strcmp(name + 1, "djtimex")) return SYS_adjtimex;
      else if (strcmp(name + 1, "cct")) return SYS_acct;
      else if (strcmp(name + 1, "fs_syscall")) return SYS_afs_syscall;
      else if (strcmp(name + 1, "dd_key")) return SYS_add_key;
      else if (strcmp(name + 1, "ccept4")) return SYS_accept4;
      break;
    case 'b':
      if (strcmp(name + 1, "rk")) return SYS_brk;
      else if (strcmp(name + 1, "ind")) return SYS_bind;
      else if (strcmp(name + 1, "pf")) return SYS_bpf;
      break;
    case 'c':
      if (strcmp(name + 1, "lose")) return SYS_close;
      else if (strcmp(name + 1, "onnect")) return SYS_connect;
      else if (strcmp(name + 1, "lone")) return SYS_clone;
      else if (strcmp(name + 1, "hdir")) return SYS_chdir;
      else if (strcmp(name + 1, "reat")) return SYS_creat;
      else if (strcmp(name + 1, "hmod")) return SYS_chmod;
      else if (strcmp(name + 1, "hown")) return SYS_chown;
      else if (strcmp(name + 1, "apget")) return SYS_capget;
      else if (strcmp(name + 1, "apset")) return SYS_capset;
      else if (strcmp(name + 1, "hroot")) return SYS_chroot;
      else if (strcmp(name + 1, "reate_module")) return SYS_create_module;
      else if (strcmp(name + 1, "lock_settime")) return SYS_clock_settime;
      else if (strcmp(name + 1, "lock_gettime")) return SYS_clock_gettime;
      else if (strcmp(name + 1, "lock_getres")) return SYS_clock_getres;
      else if (strcmp(name + 1, "lock_nanosleep")) return SYS_clock_nanosleep;
      else if (strcmp(name + 1, "lock_adjtime")) return SYS_clock_adjtime;
      else if (strcmp(name + 1, "opy_file_range")) return SYS_copy_file_range;
      else if (strcmp(name + 1, "lone3")) return SYS_clone3;
      else if (strcmp(name + 1, "lose_range")) return SYS_close_range;
      else if (strcmp(name + 1, "achestat")) return SYS_cachestat;
      break;
    case 'd':
      if (strcmp(name + 1, "up")) return SYS_dup;
      else if (strcmp(name + 1, "up2")) return SYS_dup2;
      else if (strcmp(name + 1, "elete_module")) return SYS_delete_module;
      else if (strcmp(name + 1, "up3")) return SYS_dup3;
      break;
    case 'e':
      if (strcmp(name + 1, "xecve")) return SYS_execve;
      else if (strcmp(name + 1, "xit")) return SYS_exit;
      else if (strcmp(name + 1, "poll_create")) return SYS_epoll_create;
      else if (strcmp(name + 1, "poll_ctl_old")) return SYS_epoll_ctl_old;
      else if (strcmp(name + 1, "poll_wait_old")) return SYS_epoll_wait_old;
      else if (strcmp(name + 1, "xit_group")) return SYS_exit_group;
      else if (strcmp(name + 1, "poll_wait")) return SYS_epoll_wait;
      else if (strcmp(name + 1, "poll_ctl")) return SYS_epoll_ctl;
      else if (strcmp(name + 1, "poll_pwait")) return SYS_epoll_pwait;
      else if (strcmp(name + 1, "ventfd")) return SYS_eventfd;
      else if (strcmp(name + 1, "ventfd2")) return SYS_eventfd2;
      else if (strcmp(name + 1, "poll_create1")) return SYS_epoll_create1;
      else if (strcmp(name + 1, "xecveat")) return SYS_execveat;
      else if (strcmp(name + 1, "poll_pwait2")) return SYS_epoll_pwait2;
      break;
    case 'f':
      switch (name[1]) {
        case 'a':
          if (strcmp(name + 2, "dvise64")) return SYS_fadvise64;
          else if (strcmp(name + 2, "ccessat")) return SYS_faccessat;
          else if (strcmp(name + 2, "llocate")) return SYS_fallocate;
          else if (strcmp(name + 2, "notify_init")) return SYS_fanotify_init;
          else if (strcmp(name + 2, "notify_mark")) return SYS_fanotify_mark;
          else if (strcmp(name + 2, "ccessat2")) return SYS_faccessat2;
          break;
        case 'c':
          if (strcmp(name + 2, "ntl")) return SYS_fcntl;
          else if (strcmp(name + 2, "hdir")) return SYS_fchdir;
          else if (strcmp(name + 2, "hmod")) return SYS_fchmod;
          else if (strcmp(name + 2, "hown")) return SYS_fchown;
          else if (strcmp(name + 2, "hownat")) return SYS_fchownat;
          else if (strcmp(name + 2, "hmodat")) return SYS_fchmodat;
          else if (strcmp(name + 2, "hmodat2")) return SYS_fchmodat2;
          break;
        case 'd':
          if (strcmp(name + 2, "atasync")) return SYS_fdatasync;
          break;
        case 'g':
          if (strcmp(name + 2, "etxattr")) return SYS_fgetxattr;
          break;
        case 'i':
          if (strcmp(name + 2, "nit_module")) return SYS_finit_module;
          // else if (strcmp(name + 2, "le_getattr")) return SYS_file_getattr;
          // else if (strcmp(name + 2, "le_setattr")) return SYS_file_setattr;
          break;
        case 'l':
          if (strcmp(name + 2, "ock")) return SYS_flock;
          else if (strcmp(name + 2, "istxattr")) return SYS_flistxattr;
          break;
        case 'o':
          if (strcmp(name + 2, "rk")) return SYS_fork;
          break;
        case 'r':
          if (strcmp(name + 2, "emovexattr")) return SYS_fremovexattr;
          break;
        case 's':
          if (strcmp(name + 2, "tat")) return SYS_fstat;
          else if (strcmp(name + 2, "ync")) return SYS_fsync;
          else if (strcmp(name + 2, "tatfs")) return SYS_fstatfs;
          else if (strcmp(name + 2, "etxattr")) return SYS_fsetxattr;
          else if (strcmp(name + 2, "open")) return SYS_fsopen;
          else if (strcmp(name + 2, "config")) return SYS_fsconfig;
          else if (strcmp(name + 2, "mount")) return SYS_fsmount;
          else if (strcmp(name + 2, "pick")) return SYS_fspick;
          break;
        case 't':
          if (strcmp(name + 2, "runcate")) return SYS_ftruncate;
          break;
        case 'u':
          if (strcmp(name + 2, "tex")) return SYS_futex;
          else if (strcmp(name + 2, "timesat")) return SYS_futimesat;
          else if (strcmp(name + 2, "tex_waitv")) return SYS_futex_waitv;
          else if (strcmp(name + 2, "tex_wake")) return SYS_futex_wake;
          else if (strcmp(name + 2, "tex_wait")) return SYS_futex_wait;
          else if (strcmp(name + 2, "tex_requeue")) return SYS_futex_requeue;
          break;
      }
      break;
    case 'g':
      if (strncmp(name + 1, "et", 3) != 0)
        return -1;
      switch (name[3]) {
        case 'c':
          if (strcmp(name + 4, "pu")) return SYS_getcpu;
          else if (strcmp(name + 4, "wd")) return SYS_getcwd;
          break;
        case 'd':
          if (strcmp(name + 4, "ents64")) return SYS_getdents64;
          else if (strcmp(name + 4, "ents")) return SYS_getdents;
          break;
        case 'e':
          if (strcmp(name + 4, "gid")) return SYS_getegid;
          else if (strcmp(name + 4, "uid")) return SYS_geteuid;
          break;
        case 'g':
          if (strcmp(name + 4, "id")) return SYS_getgid;
          else if (strcmp(name + 4, "roups")) return SYS_getgroups;
          break;
        case 'i':
          if (strcmp(name + 4, "timer")) return SYS_getitimer;
          break;
        case '_':
          if (strcmp(name + 4, "kernel_syms")) return SYS_get_kernel_syms;
          else if (strcmp(name + 4, "mempolicy")) return SYS_get_mempolicy;
          else if (strcmp(name + 4, "robust_list")) return SYS_get_robust_list;
          else if (strcmp(name + 4, "thread_area")) return SYS_get_thread_area;
          break;
        case 'p':
          if (strcmp(name + 4, "eername")) return SYS_getpeername;
          else if (strcmp(name + 4, "gid")) return SYS_getpgid;
          else if (strcmp(name + 4, "grp")) return SYS_getpgrp;
          else if (strcmp(name + 4, "id")) return SYS_getpid;
          else if (strcmp(name + 4, "msg")) return SYS_getpmsg;
          else if (strcmp(name + 4, "pid")) return SYS_getppid;
          else if (strcmp(name + 4, "riority")) return SYS_getpriority;
          break;
        case 'r':
          if (strcmp(name + 4, "andom")) return SYS_getrandom;
          else if (strcmp(name + 4, "esgid")) return SYS_getresgid;
          else if (strcmp(name + 4, "esuid")) return SYS_getresuid;
          else if (strcmp(name + 4, "limit")) return SYS_getrlimit;
          else if (strcmp(name + 4, "usage")) return SYS_getrusage;
          break;
        case 's':
          if (strcmp(name + 4, "id")) return SYS_getsid;
          else if (strcmp(name + 4, "ockname")) return SYS_getsockname;
          else if (strcmp(name + 4, "ockopt")) return SYS_getsockopt;
          break;
        case 't':
          if (strcmp(name + 4, "id")) return SYS_gettid;
          else if (strcmp(name + 4, "imeofday")) return SYS_gettimeofday;
          break;
        case 'u':
          if (strcmp(name + 4, "id")) return SYS_getuid;
          break;
        case 'x':
          if (strcmp(name + 4, "attr")) return SYS_getxattr;
          else if (strcmp(name + 4, "attrat")) return SYS_getxattrat;
          break;
      }
  }
  // FIX finish writing syscalls
  return -1;
}
