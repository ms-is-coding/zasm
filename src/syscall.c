#include "zasm.h"
#include <syscall.h>

int get_syscall(zasm_token t) {
  const char *s = t.start;

#define NODE(i, ...) switch (s[i]) { __VA_ARGS__ };
#define EDGE(ch, ...) case ch: __VA_ARGS__; break;
#define LEAF(i, str, n) if (__builtin_strncmp(s+(i), (str)+(i), t.len-i) == 0) return (n);

  NODE(0,
    EDGE('a',
      NODE(1,
        EDGE('c',
          LEAF(2, "access", SYS_access)
          LEAF(2, "accept", SYS_accept)
          LEAF(2, "acct", SYS_acct)
          LEAF(2, "accept4", SYS_accept4)
        )
        EDGE('d',
          LEAF(2, "adjtimex", SYS_adjtimex)
          LEAF(2, "add_key", SYS_add_key)
        )
        EDGE('f',
          LEAF(2, "afs_syscall", SYS_afs_syscall)
        )
        EDGE('l',
          LEAF(2, "alarm", SYS_alarm)
        )
        EDGE('r',
          LEAF(2, "arch_prctl", SYS_arch_prctl)
        )
      )
    );
    EDGE('b',
      LEAF(1, "brk", SYS_brk)
      LEAF(1, "bind", SYS_bind)
      LEAF(1, "bpf", SYS_bpf)
    );
    EDGE('c',
      NODE(1, 
        EDGE('a',
          LEAF(2, "cachestat", SYS_cachestat)
          LEAF(2, "capget", SYS_capget)
          LEAF(2, "capset", SYS_capset)
        ) EDGE('h',
          LEAF(2, "chdir", SYS_chdir)
          LEAF(2, "chmod", SYS_chmod)
          LEAF(2, "chown", SYS_chown)
          LEAF(2, "chroot", SYS_chroot)
        ) EDGE('l',
          LEAF(2, "clock_adjtime", SYS_clock_adjtime)
          LEAF(2, "clock_getres", SYS_clock_getres)
          LEAF(2, "clock_gettime", SYS_clock_gettime)
          LEAF(2, "clock_nanosleep", SYS_clock_nanosleep)
          LEAF(2, "clock_settime", SYS_clock_settime)
          LEAF(2, "clone", SYS_clone)
          LEAF(2, "clone3", SYS_clone3)
          LEAF(2, "close", SYS_close)
          LEAF(2, "close_range", SYS_close_range)
        ) EDGE('o',
          LEAF(2, "connect", SYS_connect)
          LEAF(2, "copy_file_range", SYS_copy_file_range)
        ) EDGE('r',
          LEAF(2, "creat", SYS_creat)
          LEAF(2, "create_module", SYS_create_module)
        )
      )
    )
    EDGE('d',
      LEAF(1, "delete_module", SYS_delete_module)
      LEAF(1, "dup", SYS_dup)
      LEAF(1, "dup2", SYS_dup2)
      LEAF(1, "dup3", SYS_dup3)
    );
    EDGE('e',
      NODE(1,
        EDGE('p',
          LEAF(2, "epoll_create", SYS_epoll_create)
          LEAF(2, "epoll_create1", SYS_epoll_create1)
          LEAF(2, "epoll_ctl", SYS_epoll_ctl)
          LEAF(2, "epoll_ctl_old", SYS_epoll_ctl_old)
          LEAF(2, "epoll_pwait", SYS_epoll_pwait)
          LEAF(2, "epoll_pwait2", SYS_epoll_pwait2)
          LEAF(2, "epoll_wait", SYS_epoll_wait)
          LEAF(2, "epoll_wait_old", SYS_epoll_wait_old)
        )
        EDGE('v',
          LEAF(2, "eventfd", SYS_eventfd)
          LEAF(2, "eventfd2", SYS_eventfd2)
        )
        EDGE('x',
          LEAF(2, "execve", SYS_execve)
          LEAF(2, "execveat", SYS_execveat)
          LEAF(2, "exit", SYS_exit)
          LEAF(2, "exit_group", SYS_exit_group)
        )
      )
    );
    EDGE('f',
      NODE(1,
        EDGE('a',
          LEAF(2, "fadvise64", SYS_fadvise64)
          LEAF(2, "faccessat", SYS_faccessat)
          LEAF(2, "fallocate", SYS_fallocate)
          LEAF(2, "fanotify_init", SYS_fanotify_init)
          LEAF(2, "fanotify_mark", SYS_fanotify_mark)
          LEAF(2, "faccessat2", SYS_faccessat2)
        )
        EDGE('c',
          LEAF(2, "fchdir", SYS_fchdir)
          LEAF(2, "fchmod", SYS_fchmod)
          LEAF(2, "fchmodat", SYS_fchmodat)
          LEAF(2, "fchmodat2", SYS_fchmodat2)
          LEAF(2, "fchown", SYS_fchown)
          LEAF(2, "fchownat", SYS_fchownat)
          LEAF(2, "fcntl", SYS_fcntl)
        )
        EDGE('d',
          LEAF(2, "fdatasync", SYS_fdatasync)
        )
        EDGE('g',
          LEAF(2, "fgetxattr", SYS_fgetxattr)
        )
        EDGE('i',
          LEAF(2, "finit_module", SYS_finit_module)
          //LEAF(2, "file_getattr", SYS_file_getattr)
          //LEAF(2, "file_setattr", SYS_file_setattr)
        )
        EDGE('l',
          LEAF(2, "flock", SYS_flock)
          LEAF(2, "flistxattr", SYS_flistxattr)
        )
        EDGE('o',
          LEAF(2, "fork", SYS_fork)
        )
        EDGE('r',
          LEAF(2, "fremovexattr", SYS_fremovexattr)
        )
        EDGE('s',
          LEAF(2, "fsconfig", SYS_fsconfig)
          LEAF(2, "fsetxattr", SYS_fsetxattr)
          LEAF(2, "fsmount", SYS_fsmount)
          LEAF(2, "fsopen", SYS_fsopen)
          LEAF(2, "fspick", SYS_fspick)
          LEAF(2, "fstat", SYS_fstat)
          LEAF(2, "fstatfs", SYS_fstatfs)
          LEAF(2, "fsync", SYS_fsync)
        )
        EDGE('t',
          LEAF(2, "ftruncate", SYS_ftruncate)
        )
        EDGE('u',
          LEAF(2, "futex", SYS_futex)
          LEAF(2, "futex_requeue", SYS_futex_requeue)
          LEAF(2, "futex_wait", SYS_futex_wait)
          LEAF(2, "futex_waitv", SYS_futex_waitv)
          LEAF(2, "futex_wake", SYS_futex_wake)
          LEAF(2, "futimesat", SYS_futimesat)
        )
      )
    );
    EDGE('g',
      if (s[1] != 'e' || s[2] != 't') return -1;
      NODE(3,
        EDGE('c',
          LEAF(4, "getcpu", SYS_getcpu)
          LEAF(4, "getcwd", SYS_getcwd)
        )
        EDGE('d',
          LEAF(4, "getdents64", SYS_getdents64)
          LEAF(4, "getdents", SYS_getdents)
        )
        EDGE('e',
          LEAF(4, "getegid", SYS_getegid)
          LEAF(4, "geteuid", SYS_geteuid)
        )
        EDGE('g',
          LEAF(4, "getgid", SYS_getgid)
          LEAF(4, "getgroups", SYS_getgroups)
        )
        EDGE('i',
          LEAF(4, "getitimer", SYS_getitimer)
        )
        EDGE('_',
          LEAF(4, "get_kernel_syms", SYS_get_kernel_syms)
          LEAF(4, "get_mempolicy", SYS_get_mempolicy)
          LEAF(4, "get_robust_list", SYS_get_robust_list)
          LEAF(4, "get_thread_area", SYS_get_thread_area)
        )
        EDGE('p',
          LEAF(4, "getpeername", SYS_getpeername)
          LEAF(4, "getpgid", SYS_getpgid)
          LEAF(4, "getpgrp", SYS_getpgrp)
          LEAF(4, "getpid", SYS_getpid)
          LEAF(4, "getpmsg", SYS_getpmsg)
          LEAF(4, "getppid", SYS_getppid)
          LEAF(4, "getpriority", SYS_getpriority)
        )
        EDGE('r',
          LEAF(4, "getrandom", SYS_getrandom)
          LEAF(4, "getresgid", SYS_getresgid)
          LEAF(4, "getresuid", SYS_getresuid)
          LEAF(4, "getrlimit", SYS_getrlimit)
          LEAF(4, "getrusage", SYS_getrusage)
        )
        EDGE('s',
          LEAF(4, "getsid", SYS_getsid)
          LEAF(4, "getsockname", SYS_getsockname)
          LEAF(4, "getsockopt", SYS_getsockopt)
        )
        EDGE('t',
          LEAF(4, "gettid", SYS_gettid)
          LEAF(4, "gettimeofday", SYS_gettimeofday)
        )
        EDGE('u',
          LEAF(4, "getuid", SYS_getuid)
        )
        EDGE('x',
          LEAF(4, "getxattr", SYS_getxattr)
          LEAF(4, "getxattrat", SYS_getxattrat)
        )
      )
    );
    EDGE('i',
      NODE(1,
        EDGE('n',
          LEAF(2, "init_module", SYS_init_module)
          LEAF(2, "inotify_add_watch", SYS_inotify_add_watch)
          LEAF(2, "inotify_init", SYS_inotify_init)
          LEAF(2, "inotify_init1", SYS_inotify_init1)
          LEAF(2, "inotify_rm_watch", SYS_inotify_rm_watch)
        );
        EDGE('o',
          NODE(2,
            EDGE('_',
              NODE(3,
                EDGE('u',
                  LEAF(4, "io_uring_enter", SYS_io_uring_enter)
                  LEAF(4, "io_uring_register", SYS_io_uring_register)
                  LEAF(4, "io_uring_setup", SYS_io_uring_setup)
                );
                EDGE('s',
                  LEAF(4, "io_setup", SYS_io_setup)
                  LEAF(4, "io_submit", SYS_io_submit)
                );
              );
              LEAF(3, "io_cancel", SYS_io_cancel)
              LEAF(3, "io_destroy", SYS_io_destroy)
              LEAF(3, "io_getevents", SYS_io_getevents)
              LEAF(3, "io_pgetevents", SYS_io_pgetevents)
            )
          );
          LEAF(2, "ioctl", SYS_ioctl)
          LEAF(2, "ioperm", SYS_ioperm)
          LEAF(2, "iopl", SYS_iopl)
          LEAF(2, "ioprio_get", SYS_ioprio_get)
          LEAF(2, "ioprio_set", SYS_ioprio_set)
        );
      )
    );
    EDGE('k',
      LEAF(1, "kcmp", SYS_kcmp)
      LEAF(1, "kexec_file_load", SYS_kexec_file_load)
      LEAF(1, "kexec_load", SYS_kexec_load)
      LEAF(1, "keyctl", SYS_keyctl)
      LEAF(1, "kill", SYS_kill)
    );
    EDGE('l',
      NODE(1,
        EDGE('a',
          LEAF(1, "landlock_add_rule", SYS_landlock_add_rule)
          LEAF(1, "landlock_create_ruleset", SYS_landlock_create_ruleset)
          LEAF(1, "landlock_restrict_self", SYS_landlock_restrict_self)
        );
        EDGE('i',
          LEAF(1, "link", SYS_link)
          LEAF(1, "linkat", SYS_linkat)
          LEAF(1, "listen", SYS_listen)
          LEAF(1, "listmount", SYS_listmount)
          LEAF(1, "listxattr", SYS_listxattr)
          LEAF(1, "listxattrat", SYS_listxattrat)
        );
        EDGE('s',
          LEAF(1, "lseek", SYS_lseek)
          LEAF(1, "lsetxattr", SYS_lsetxattr)
          LEAF(1, "lsm_get_self_attr", SYS_lsm_get_self_attr)
          LEAF(1, "lsm_list_modules", SYS_lsm_list_modules)
          LEAF(1, "lsm_set_self_attr", SYS_lsm_set_self_attr)
          LEAF(1, "lstat", SYS_lstat)
        );
      );
      LEAF(1, "lchown", SYS_lchown)
      LEAF(1, "lgetxattr", SYS_lgetxattr)
      LEAF(1, "llistxattr", SYS_llistxattr)
      LEAF(1, "lookup_dcookie", SYS_lookup_dcookie)
      LEAF(1, "lremovexattr", SYS_lremovexattr)
    );
    EDGE('m',
      NODE(1,
        EDGE('a',
          LEAF(2, "madvise", SYS_madvise)
          LEAF(2, "map_shadow_stack", SYS_map_shadow_stack)
        );
        EDGE('e',
          LEAF(2, "membarrier", SYS_membarrier)
          LEAF(2, "memfd_create", SYS_memfd_create)
          LEAF(2, "memfd_secret", SYS_memfd_secret)
        );
        EDGE('i',
          LEAF(2, "migrate_pages", SYS_migrate_pages)
          LEAF(2, "mincore", SYS_mincore)
        );
        EDGE('k',
          LEAF(2, "mkdir", SYS_mkdir)
          LEAF(2, "mkdirat", SYS_mkdirat)
          LEAF(2, "mknod", SYS_mknod)
          LEAF(2, "mknodat", SYS_mknodat)
        );
        EDGE('l',
          LEAF(2, "mlock", SYS_mlock)
          LEAF(2, "mlock2", SYS_mlock2)
          LEAF(2, "mlockall", SYS_mlockall)
        );
        EDGE('o',
          LEAF(2, "modify_ldt", SYS_modify_ldt)
          LEAF(2, "mount", SYS_mount)
          LEAF(2, "mount_setattr", SYS_mount_setattr)
          LEAF(2, "move_mount", SYS_move_mount)
          LEAF(2, "move_pages", SYS_move_pages)
        );
        EDGE('q',
          LEAF(2, "mq_getsetattr", SYS_mq_getsetattr)
          LEAF(2, "mq_notify", SYS_mq_notify)
          LEAF(2, "mq_open", SYS_mq_open)
          LEAF(2, "mq_timedreceive", SYS_mq_timedreceive)
          LEAF(2, "mq_timedsend", SYS_mq_timedsend)
          LEAF(2, "mq_unlink", SYS_mq_unlink)
        );
        EDGE('s',
          LEAF(2, "mseal", SYS_mseal)
          LEAF(2, "msgctl", SYS_msgctl)
          LEAF(2, "msgget", SYS_msgget)
          LEAF(2, "msgrcv", SYS_msgrcv)
          LEAF(2, "msgsnd", SYS_msgsnd)
          LEAF(2, "msync", SYS_msync)
        );
        EDGE('u',
          LEAF(2, "munlock", SYS_munlock)
          LEAF(2, "munlockall", SYS_munlockall)
          LEAF(2, "munmap", SYS_munmap)
        );
      );
      LEAF(1, "mbind", SYS_mbind)
      LEAF(1, "mmap", SYS_mmap)
      LEAF(1, "mprotect", SYS_mprotect)
      LEAF(1, "mremap", SYS_mremap)
    );
    EDGE('n',
      LEAF(1, "name_to_handle_at", SYS_name_to_handle_at)
      LEAF(1, "nanosleep", SYS_nanosleep)
      LEAF(1, "newfstatat", SYS_newfstatat)
      LEAF(1, "nfsservctl", SYS_nfsservctl)
    );
    EDGE('o',
      LEAF(1, "open", SYS_open)
      LEAF(1, "openat", SYS_openat)
      LEAF(1, "openat2", SYS_openat2)
      LEAF(1, "open_by_handle_at", SYS_open_by_handle_at)
      LEAF(1, "open_tree", SYS_open_tree)
      LEAF(1, "open_tree_attr", SYS_open_tree_attr)
    );
    EDGE('p',
      NODE(1,
        EDGE('a',
          LEAF(2, "pause", SYS_pause)
        );
        EDGE('e',
          LEAF(2, "perf_event_open", SYS_perf_event_open)
          LEAF(2, "personality", SYS_personality)
        );
        EDGE('i',
          LEAF(2, "pidfd_getfd", SYS_pidfd_getfd)
          LEAF(2, "pidfd_open", SYS_pidfd_open)
          LEAF(2, "pidfd_send_signal", SYS_pidfd_send_signal)
          LEAF(2, "pipe", SYS_pipe)
          LEAF(2, "pipe2", SYS_pipe2)
          LEAF(2, "pivot_root", SYS_pivot_root)
        );
        EDGE('k',
          LEAF(2, "pkey_alloc", SYS_pkey_alloc)
          LEAF(2, "pkey_free", SYS_pkey_free)
          LEAF(2, "pkey_mprotect", SYS_pkey_mprotect)
        );
        EDGE('o',
          LEAF(2, "poll", SYS_poll)
        );
        EDGE('p',
          LEAF(2, "ppoll", SYS_ppoll)
        );
        EDGE('r',
          LEAF(2, "prctl", SYS_prctl)
           //LEAF(2, "pread", SYS_pread)
          LEAF(2, "preadv", SYS_preadv)
          LEAF(2, "preadv2", SYS_preadv2)
          LEAF(2, "prlimit64", SYS_prlimit64)
          LEAF(2, "process_madvise", SYS_process_madvise)
          LEAF(2, "process_mrelease", SYS_process_mrelease)
          LEAF(2, "process_vm_readv", SYS_process_vm_readv)
          LEAF(2, "process_vm_writev", SYS_process_vm_writev)
        );
        EDGE('s',
          LEAF(2, "pselect6", SYS_pselect6)
        );
        EDGE('t',
          LEAF(2, "ptrace", SYS_ptrace)
        );
        EDGE('u',
          LEAF(2, "putpmsg", SYS_putpmsg)
        );
        EDGE('w',
          //LEAF(2, "pwrite", SYS_pwrite)
          LEAF(2, "pwritev", SYS_pwritev)
          LEAF(2, "pwritev2", SYS_pwritev2)
        );
      )
    );
    EDGE('q',
      LEAF(1, "query_module", SYS_query_module)
      LEAF(1, "quotactl", SYS_quotactl)
      LEAF(1, "quotactl_fd", SYS_quotactl_fd)
    );
    EDGE('r',
      LEAF(1, "read", SYS_read)
      LEAF(1, "readahead", SYS_readahead)
      LEAF(1, "readlink", SYS_readlink)
      LEAF(1, "readlinkat", SYS_readlinkat)
      LEAF(1, "readv", SYS_readv)
      LEAF(1, "reboot", SYS_reboot)
      LEAF(1, "recvfrom", SYS_recvfrom)
      LEAF(1, "recvmmsg", SYS_recvmmsg)
      LEAF(1, "recvmsg", SYS_recvmsg)
      LEAF(1, "remap_file_pages", SYS_remap_file_pages)
      LEAF(1, "removexattr", SYS_removexattr)
      LEAF(1, "removexattrat", SYS_removexattrat)
      LEAF(1, "rename", SYS_rename)
      LEAF(1, "renameat", SYS_renameat)
      LEAF(1, "renameat2", SYS_renameat2)
      LEAF(1, "request_key", SYS_request_key)
      LEAF(1, "restart_syscall", SYS_restart_syscall)
      LEAF(1, "rmdir", SYS_rmdir)
      LEAF(1, "rseq", SYS_rseq)
      LEAF(1, "rt_sigaction", SYS_rt_sigaction)
      LEAF(1, "rt_sigpending", SYS_rt_sigpending)
      LEAF(1, "rt_sigprocmask", SYS_rt_sigprocmask)
      LEAF(1, "rt_sigqueueinfo", SYS_rt_sigqueueinfo)
      LEAF(1, "rt_sigreturn", SYS_rt_sigreturn)
      LEAF(1, "rt_sigsuspend", SYS_rt_sigsuspend)
      LEAF(1, "rt_sigtimedwait", SYS_rt_sigtimedwait)
      LEAF(1, "rt_tgsigqueueinfo", SYS_rt_tgsigqueueinfo)
    );
    EDGE('s',
      LEAF(1, "_sysctl", SYS__sysctl)
      LEAF(1, "sched_get_priority_max", SYS_sched_get_priority_max)
      LEAF(1, "sched_get_priority_min", SYS_sched_get_priority_min)
      LEAF(1, "sched_getaffinity", SYS_sched_getaffinity)
      LEAF(1, "sched_getattr", SYS_sched_getattr)
      LEAF(1, "sched_getparam", SYS_sched_getparam)
      LEAF(1, "sched_getscheduler", SYS_sched_getscheduler)
      LEAF(1, "sched_rr_get_interval", SYS_sched_rr_get_interval)
      LEAF(1, "sched_setaffinity", SYS_sched_setaffinity)
      LEAF(1, "sched_setattr", SYS_sched_setattr)
      LEAF(1, "sched_setparam", SYS_sched_setparam)
      LEAF(1, "sched_setscheduler", SYS_sched_setscheduler)
      LEAF(1, "sched_yield", SYS_sched_yield)
      LEAF(1, "seccomp", SYS_seccomp)
      LEAF(1, "security", SYS_security)
      LEAF(1, "select", SYS_select)
      LEAF(1, "semctl", SYS_semctl)
      LEAF(1, "semget", SYS_semget)
      LEAF(1, "semop", SYS_semop)
      LEAF(1, "semtimedop", SYS_semtimedop)
      LEAF(1, "sendfile", SYS_sendfile)
      LEAF(1, "sendmmsg", SYS_sendmmsg)
      LEAF(1, "sendmsg", SYS_sendmsg)
      LEAF(1, "sendto", SYS_sendto)
      LEAF(1, "set_mempolicy", SYS_set_mempolicy)
      LEAF(1, "set_mempolicy_home_node", SYS_set_mempolicy_home_node)
      LEAF(1, "set_robust_list", SYS_set_robust_list)
      LEAF(1, "set_thread_area", SYS_set_thread_area)
      LEAF(1, "set_tid_address", SYS_set_tid_address)
      LEAF(1, "setdomainname", SYS_setdomainname)
      LEAF(1, "setfsgid", SYS_setfsgid)
      LEAF(1, "setfsuid", SYS_setfsuid)
      LEAF(1, "setgid", SYS_setgid)
      LEAF(1, "setgroups", SYS_setgroups)
      LEAF(1, "sethostname", SYS_sethostname)
      LEAF(1, "setitimer", SYS_setitimer)
      LEAF(1, "setns", SYS_setns)
      LEAF(1, "setpgid", SYS_setpgid)
      LEAF(1, "setpriority", SYS_setpriority)
      LEAF(1, "setregid", SYS_setregid)
      LEAF(1, "setresgid", SYS_setresgid)
      LEAF(1, "setresuid", SYS_setresuid)
      LEAF(1, "setreuid", SYS_setreuid)
      LEAF(1, "setrlimit", SYS_setrlimit)
      LEAF(1, "setsid", SYS_setsid)
      LEAF(1, "setsockopt", SYS_setsockopt)
      LEAF(1, "settimeofday", SYS_settimeofday)
      LEAF(1, "setuid", SYS_setuid)
      LEAF(1, "setxattr", SYS_setxattr)
      LEAF(1, "setxattrat", SYS_setxattrat)
      LEAF(1, "shmat", SYS_shmat)
      LEAF(1, "shmctl", SYS_shmctl)
      LEAF(1, "shmdt", SYS_shmdt)
      LEAF(1, "shmget", SYS_shmget)
      LEAF(1, "shutdown", SYS_shutdown)
      LEAF(1, "sigaltstack", SYS_sigaltstack)
      LEAF(1, "signalfd", SYS_signalfd)
      LEAF(1, "signalfd4", SYS_signalfd4)
      LEAF(1, "socket", SYS_socket)
      LEAF(1, "socketpair", SYS_socketpair)
      LEAF(1, "splice", SYS_splice)
      LEAF(1, "stat", SYS_stat)
      LEAF(1, "statfs", SYS_statfs)
      LEAF(1, "statmount", SYS_statmount)
      LEAF(1, "statx", SYS_statx)
      LEAF(1, "swapoff", SYS_swapoff)
      LEAF(1, "swapon", SYS_swapon)
      LEAF(1, "symlink", SYS_symlink)
      LEAF(1, "symlinkat", SYS_symlinkat)
      LEAF(1, "sync", SYS_sync)
      LEAF(1, "sync_file_range", SYS_sync_file_range)
      LEAF(1, "syncfs", SYS_syncfs)
      LEAF(1, "sysfs", SYS_sysfs)
      LEAF(1, "sysinfo", SYS_sysinfo)
      LEAF(1, "syslog", SYS_syslog)
    );
    EDGE('t',
      LEAF(1, "tee", SYS_tee)
      LEAF(1, "tgkill", SYS_tgkill)
      LEAF(1, "time", SYS_time)
      LEAF(1, "timer_create", SYS_timer_create)
      LEAF(1, "timer_delete", SYS_timer_delete)
      LEAF(1, "timerfd_create", SYS_timerfd_create)
      LEAF(1, "timerfd_gettime", SYS_timerfd_gettime)
      LEAF(1, "timerfd_settime", SYS_timerfd_settime)
      LEAF(1, "timer_getoverrun", SYS_timer_getoverrun)
      LEAF(1, "timer_gettime", SYS_timer_gettime)
      LEAF(1, "timer_settime", SYS_timer_settime)
      LEAF(1, "times", SYS_times)
      LEAF(1, "tkill", SYS_tkill)
      LEAF(1, "truncate", SYS_truncate)
      LEAF(1, "tuxcall", SYS_tuxcall)
    );
    EDGE('u',
      LEAF(1, "umask", SYS_umask)
      LEAF(1, "umount2", SYS_umount2)
      LEAF(1, "uname", SYS_uname)
      LEAF(1, "unlink", SYS_unlink)
      LEAF(1, "unlinkat", SYS_unlinkat)
      LEAF(1, "unshare", SYS_unshare)
      LEAF(1, "uselib", SYS_uselib)
      LEAF(1, "userfaultfd", SYS_userfaultfd)
      LEAF(1, "ustat", SYS_ustat)
      LEAF(1, "utime", SYS_utime)
      LEAF(1, "utimensat", SYS_utimensat)
      LEAF(1, "utimes", SYS_utimes)
    );
    EDGE('v',
      LEAF(1, "vfork", SYS_vfork)
      LEAF(1, "vhangup", SYS_vhangup)
      LEAF(1, "vmsplice", SYS_vmsplice)
      LEAF(1, "vserver", SYS_vserver)
    );
    EDGE('w',
      LEAF(1, "wait4", SYS_wait4)
      LEAF(1, "waitid", SYS_waitid)
      LEAF(1, "write", SYS_write)
      LEAF(1, "writev", SYS_writev)
    );
  )
  return -1;
}
