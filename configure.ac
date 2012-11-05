#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([1.00])
AC_INIT(LibTwitter-Core C++, 0.0.1, neozaru@mailoo.org)
AM_INIT_AUTOMAKE([subdir-objects])
AC_CONFIG_MACRO_DIR([m4])
LT_INIT

AC_CONFIG_SRCDIR([curl/curl.h])
AC_CONFIG_HEADERS([config.h])


######################################################################
# DOXYGEN SUPPORT
######################################################################

DX_INIT_DOXYGEN([$PACKAGE_NAME],[doxygen.cfg],[doc])

DX_HTML_FEATURE(ON)
DX_CHM_FEATURE(OFF)
DX_CHI_FEATURE(OFF)
DX_MAN_FEATURE(OFF)
DX_RTF_FEATURE(OFF)
DX_XML_FEATURE(OFF)
DX_PDF_FEATURE(OFF)
DX_PS_FEATURE(OFF)


######################################################################

# Used for making libraries
AM_PROG_LIBTOOL
AC_PROG_MAKE_SET

#LT_INIT #deprecated

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([inttypes.h limits.h memory.h stdint.h stdlib.h string.h sys/socket.h sys/time.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([memset strcasecmp strncasecmp])

AC_CONFIG_FILES([Makefile
				src/Makefile
                libtwitter-core.pc
                examples/Client_Basic/Makefile
                examples/Client_Alternative/Makefile
                examples/Client_Send_Image/Makefile
                examples/Client_Streaming_Session/Makefile
                examples/Client_Streaming_Listener/Makefile
                examples/Client_Streaming_Hard_Request/Makefile
                testSuite/Makefile])


AC_OUTPUT
