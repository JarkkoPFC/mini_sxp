#ifndef HEADER_CURL_CONFIG_LINUX_H
#define HEADER_CURL_CONFIG_LINUX_H
/***************************************************************************
 * Hand-crafted libcurl configuration for GCC/Linux builds.
 *
 * This file intentionally contains feature-test results only.  It is
 * included by the GCC external-library makefile before curl_setup.h, so the
 * libcurl sources can be built without running configure.
 ***************************************************************************/

#define STDC_HEADERS 1
#define _GNU_SOURCE 1
#define OS "linux"

#define HAVE_ALARM 1
#define HAVE_ARPA_INET_H 1
#define HAVE_BASENAME 1
#define HAVE_BOOL_T 1
#define HAVE_CLOCK_GETTIME_MONOTONIC 1
#define HAVE_FCNTL 1
#define HAVE_FCNTL_H 1
#define HAVE_FCNTL_O_NONBLOCK 1
#define HAVE_LIBGEN_H 1
#define HAVE_FREEADDRINFO 1
#define HAVE_FTRUNCATE 1
#define HAVE_GETADDRINFO 1
#define HAVE_GETADDRINFO_THREADSAFE 1
#define HAVE_GETEUID 1
#define HAVE_GETHOSTNAME 1
#define HAVE_GETPEERNAME 1
#define HAVE_GETPPID 1
#define HAVE_GETPWUID 1
#define HAVE_GETSOCKNAME 1
#define HAVE_GETTIMEOFDAY 1
#define HAVE_GMTIME_R 1
#define HAVE_GLIBC_STRERROR_R 1
#define HAVE_INET_NTOP 1
#define HAVE_INET_PTON 1
#define HAVE_LINUX_TCP_H 1
#define HAVE_LOCALE_H 1
#define HAVE_MSG_NOSIGNAL 1
#define HAVE_NETDB_H 1
#define HAVE_NETINET_IN_H 1
#define HAVE_NETINET_TCP_H 1
#define HAVE_PIPE 1
#define HAVE_POLL_FINE 1
#define HAVE_POLL_H 1
#define HAVE_PWD_H 1
#define HAVE_PTHREAD_H 1
#define HAVE_SELECT 1
#define HAVE_SETLOCALE 1
#define HAVE_SIGACTION 1
#define HAVE_SIGNAL 1
#define HAVE_SIGSETJMP 1
#define HAVE_SNPRINTF 1
#define HAVE_SOCKADDR_IN6_SIN6_SCOPE_ID 1
#define HAVE_SOCKET 1
#define HAVE_SOCKETPAIR 1
#define HAVE_STDBOOL_H 1
#define HAVE_STRCASECMP 1
#define HAVE_STRDUP 1
#define HAVE_STRERROR_R 1
#define HAVE_STRTOK_R 1
#define HAVE_STRTOLL 1
#define HAVE_STRUCT_SOCKADDR_STORAGE 1
#define HAVE_STRUCT_TIMEVAL 1
#define HAVE_SUSECONDS_T 1
#define HAVE_SYS_IOCTL_H 1
#define HAVE_SYS_PARAM_H 1
#define HAVE_SYS_SELECT_H 1
#define HAVE_SYS_SOCKET_H 1
#define HAVE_SYS_STAT_H 1
#define HAVE_SYS_TIME_H 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_SYS_UN_H 1
#define HAVE_TERMIOS_H 1
#define HAVE_UNISTD_H 1
#define HAVE_UTIME 1
#define HAVE_UTIME_H 1

#define ENABLE_IPV6 1
/* OpenSSL is intentionally disabled for now, as it is on Windows builds. */
#define USE_THREADS_POSIX 1
#define USE_UNIX_SOCKETS 1

#define CURL_DISABLE_LDAP 1
#define HAVE_LIBZ 1

#define HAVE_LONGLONG 1
#define SIZEOF_CURL_OFF_T 8
#define SIZEOF_CURL_SOCKET_T 4
#define SIZEOF_INT 4
#define SIZEOF_LONG __SIZEOF_LONG__
#define SIZEOF_LONG_LONG 8
#define SIZEOF_SIZE_T __SIZEOF_SIZE_T__

#define SIZEOF_OFF_T 8
#if defined(__LP64__)
#  define SIZEOF_TIME_T 8
#else
#  define SIZEOF_TIME_T 4
#endif

#define HAVE_RECV 1
#define RECV_TYPE_ARG1 int
#define RECV_TYPE_ARG2 void *
#define RECV_TYPE_ARG3 size_t
#define RECV_TYPE_ARG4 int
#define RECV_TYPE_RETV ssize_t

#define HAVE_SEND 1
#define SEND_TYPE_ARG1 int
#define SEND_QUAL_ARG2 const
#define SEND_TYPE_ARG2 void *
#define SEND_TYPE_ARG3 size_t
#define SEND_TYPE_ARG4 int
#define SEND_TYPE_RETV ssize_t

#endif /* HEADER_CURL_CONFIG_LINUX_H */
