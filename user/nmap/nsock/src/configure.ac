# Require autoconf 2.13 -*- mode: fundamental; -*-
AC_PREREQ(2.13)

dnl Process this file with autoconf to produce a configure script.
AC_INIT(nsock_core.c)

AC_ARG_WITH(localdirs,
  [  --with-localdirs        Explicitly ask compiler to use /usr/local/{include,libs} if they exist ],
  [ case "$with_localdirs" in
      yes)
        user_localdirs=1
        ;;
      no)
        user_localdirs=0
        ;;
    esac
    ],
  [ user_localdirs=0 ] )

if test "$user_localdirs" = 1; then
   if test -d /usr/local/lib; then
     LDFLAGS="$LDFLAGS -L/usr/local/lib"
     fi
   if test -d /usr/local/include; then
     CFLAGS="$CFLAGS -I/usr/local/include"
   fi
fi

dnl use nsock_config.h instad of -D macros
AC_CONFIG_HEADER(nsock_config.h)

dnl Checks for programs.
AC_PROG_CC
 if test -n "$GCC"; then
      CFLAGS="$CFLAGS -Wall "
 fi
AC_PROG_RANLIB
dnl AC_PROG_INSTALL
dnl AC_PATH_PROG(MAKEDEPEND, makedepend)

AC_SUBST(COMPAT_OBJS)
AC_SUBST(COMPAT_SRCS)

dnl Host specific hacks
AC_CANONICAL_HOST

dnl Checks for libraries.
dnl AC_CHECK_LIB(m, pow)

dnl If any socket libraries needed
AC_CHECK_FUNC(gethostent, , AC_CHECK_LIB(nsl, gethostent))
AC_CHECK_FUNC(setsockopt, , AC_CHECK_LIB(socket, setsockopt))

dnl need posix4/nanosleep for solaris 2.4
AC_CHECK_FUNC(nanosleep, , AC_CHECK_LIB(posix4, nanosleep))

dnl Checks for header files.
AC_HEADER_STDC

dnl Checks for typedefs, structures, and compiler characteristics.

AC_ARG_WITH(libnbase,
[  --with-libnbase=DIR     Look for nbase include/libs in DIR],
[  case "$with_libnbase" in
  yes)
    ;;
  *)
    NBASEDIR="$with_libnbase"
    ;;
  esac],
NBASEDIR="../../nbase"
)

LDFLAGS="$LDFLAGS -L$NBASEDIR"
CFLAGS="$CFLAGS -I$NBASEDIR"
LIBNBASE_LIBS="$LIBS -lnbase"

AC_SUBST(LIBNBASE_LIBS)
AC_SUBST(NBASEDIR)

# First we test whether they specified openssl desires explicitly
use_openssl="yes"
specialssldir=""

AC_ARG_WITH(openssl,
[  --with-openssl=DIR    Use optional openssl libs and includes from [DIR]/lib/ 
and [DIR]/include/openssl/)],
[  case "$with_openssl" in
  yes)
    ;;
  no)
    use_openssl="no"
    ;;
  *)
    specialssldir="$with_openssl"
    CFLAGS="-I$with_openssl/include $CFLAGS"
    ;;
  esac]
)


# If they didn't specify it, we try to find it
if test "$use_openssl" = "yes" -a -z "$specialssldir"; then
  AC_CHECK_HEADER(openssl/ssl.h,,
  [ use_openssl="no"
    AC_MSG_WARN([Failed to find openssl/ssl.h so OpenSSL will not be used. If it
 is installed you can try the --with-openssl=DIR argument]) ])

 if test "$use_openssl" = "yes"; then
   AC_CHECK_HEADER(openssl/err.h,,
    [ use_openssl="no"
    AC_MSG_WARN([Failed to find openssl/err.h so OpenSSL will not be used. If it
 is installed you can try the --with-openssl=DIR argument]) ])
 fi

 if test "$use_openssl" = "yes"; then
   AC_CHECK_HEADER(openssl/rand.h,,
    [ use_openssl="no"
    AC_MSG_WARN([Failed to find openssl/rand.h so OpenSSL will not be used. If i
t is installed you can try the --with-openssl=DIR argument]) ])
 fi

 if test "$use_openssl" = "yes"; then
   AC_CHECK_LIB(crypto, BIO_int_ctrl,
    [],
    [ use_openssl="no"
    AC_MSG_WARN([Failed to find libcrypto so OpenSSL will not be used. If it is installed you can try the --with-openssl=DIR argument]) ])
 fi

 if test "$use_openssl" = "yes"; then
   AC_CHECK_LIB(ssl, SSL_new,
    [],
    [ use_openssl="no"
    AC_MSG_WARN([Failed to find libssl so OpenSSL will not be used. If it is ins
talled you can try the --with-openssl=DIR argument]) ])
 fi
fi

if test "$use_openssl" = "yes"; then
  AC_DEFINE(HAVE_OPENSSL)
fi


AC_MSG_CHECKING([struct ip])
AC_TRY_COMPILE([#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>],
               [struct ip ip;],
               [AC_MSG_RESULT(yes); bsd_networking=yes],
               [AC_MSG_RESULT(no); bsd_networking=no]);
if test $bsd_networking = yes; then

  AC_DEFINE(BSD_NETWORKING)
  AC_MSG_CHECKING([ip_v in struct ip])
  AC_TRY_COMPILE([#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>],
                 [struct ip ip; ip.ip_v;],
                 [AC_MSG_RESULT(yes); has_bitfields=yes],
                 [AC_MSG_RESULT(no); has_bitfields=no])

  if test $has_bitfields = no; then
    SAVE_CFLAGS="$CFLAGS"
    CFLAGS="-D__STDC__=2"

    AC_MSG_CHECKING([if setting __STDC__=2 gives ip_v])
    AC_TRY_COMPILE([#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>],
                   [struct ip ip; ip.ip_v;],
                   [AC_MSG_RESULT(yes); setting_stdc_helps=yes],
                  [AC_MSG_RESULT(no); setting_stdc_helps=no])

    CFLAGS="$SAVE_CFLAGS"
    if test $setting_stdc_helps = yes; then
      CFLAGS="$CFLAGS -D__STDC__=2"
    else
      AC_MSG_RESULT(Can't figure out how to get bitfields - configure failed)
      exit 1
    fi
  fi
fi

AC_SUBST(CFLAGS)

dnl This test is from the configure.in of Unix Network Programming second
dnl edition example code by W. Richard Stevens
dnl ##################################################################
dnl Check if sockaddr{} has sa_len member.
dnl
AC_CACHE_CHECK(if sockaddr{} has sa_len member, ac_cv_sockaddr_has_sa_len,
        AC_TRY_COMPILE([
#               include <sys/types.h>
#               include <sys/socket.h>],
                [unsigned int i = sizeof(((struct sockaddr *)0)->sa_len)],
        ac_cv_sockaddr_has_sa_len=yes,
        ac_cv_sockaddr_has_sa_len=no))
if test $ac_cv_sockaddr_has_sa_len = yes ; then
        AC_DEFINE(HAVE_SOCKADDR_SA_LEN)
fi

AC_CACHE_CHECK(if struct icmp exists, ac_cv_struct_icmp_exists,
        AC_TRY_COMPILE([
#               include <sys/types.h>
#               include <sys/param.h>
#               include <netinet/in_systm.h>
#               include <netinet/in.h>               
#               define __USE_BSD
#               define __FAVOR_BSD
#               define __BSD_SOURCE
#               include <netinet/ip.h>
#               include <netinet/ip_icmp.h>],
                [unsigned int i = sizeof(struct icmp)],
        ac_cv_struct_icmp_exists=yes,
        ac_cv_struct_icmp_exists=no))
if test $ac_cv_struct_icmp_exists = yes ; then
        AC_DEFINE(HAVE_STRUCT_ICMP)
fi

AC_CACHE_CHECK(if struct ip exists, ac_cv_struct_ip_exists,
        AC_TRY_COMPILE([
#               include <sys/types.h>
#               include <sys/param.h>
#               include <netinet/in_systm.h>
#               include <netinet/in.h>               
#               define __USE_BSD
#               define __FAVOR_BSD
#               define __BSD_SOURCE
#               include <netinet/ip.h>],
                [unsigned int i = sizeof(struct ip)],
        ac_cv_struct_ip_exists=yes,
        ac_cv_struct_ip_exists=no))
if test $ac_cv_struct_ip_exists = yes ; then
        AC_DEFINE(HAVE_STRUCT_IP)
fi

AC_CACHE_CHECK(if struct ip has ip_sum member, ac_cv_ip_has_ip_sum,
        AC_TRY_COMPILE([
#               include <sys/types.h>
#               include <sys/param.h>
#               include <netinet/in_systm.h>
#               include <netinet/in.h>
#               define __USE_BSD
#               define __FAVOR_BSD
#               define __BSD_SOURCE
#               include <netinet/ip.h>
#               include <netinet/ip_icmp.h>],
                [unsigned int i = sizeof(((struct ip *)0)->ip_sum)],
        ac_cv_ip_has_ip_sum=yes,
        ac_cv_ip_has_ip_sum=no))
if test $ac_cv_ip_has_ip_sum = yes ; then
        AC_DEFINE(HAVE_IP_IP_SUM)
fi

AC_OUTPUT(Makefile)
