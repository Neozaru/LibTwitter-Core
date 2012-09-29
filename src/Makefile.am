top_srcdir = ../

# Didn't found solution for working with subdirs and statically link internal subdirs ...
AUTOMAKE_OPTIONS = subdir-objects


core=Twitter/Core

lib_LTLIBRARIES = $(top_builddir)/bin/libtwitter-core.la


__top_builddir__bin_libtwitter_core_la_SOURCES = Twitter/Core/OAuth.cpp Twitter/Core/OAuth.h \
					 Twitter/Core/Utils.cpp Twitter/Core/Utils.h \
					 Twitter/Core/CurlProcess.cpp Twitter/Core/CurlProcess.h \
					 Twitter/Core/TwitterRequest.cpp Twitter/Core/TwitterRequest.h \
					 Twitter/Core/RequestCreator.cpp Twitter/Core/RequestCreator.h \
					 Twitter/Core/TwitterSession.cpp Twitter/Core/TwitterSession.h \
					 Twitter/Core/TwitterRequestListener.h	


__top_builddir__bin_libtwitter_core_la_SOURCES += Twitter/Core/Parsers/HTML_Parser.h \
		 Twitter/Core/Parsers/Auth_Page_Parser.cpp Twitter/Core/Parsers/Auth_Page_Parser.h \
		 Twitter/Core/Parsers/PIN_Page_Parser.cpp Twitter/Core/Parsers/PIN_Page_Parser.h
	

__top_builddir__bin_libtwitter_core_la_SOURCES += Twitter/Core/Utils/SHA1.cpp Twitter/Core/Utils/SHA1.h \
					 Twitter/Core/Utils/HMAC_SHA1.cpp Twitter/Core/Utils/HMAC_SHA1.h \
					 Twitter/Core/Utils/base64.cpp Twitter/Core/Utils/base64.h \
					 Twitter/Core/Utils/urlencode.cpp Twitter/Core/Utils/urlencode.h



#AM_CPPFLAGS = -I$(core)/ -I$(core)/Utils -I$(core)/Parsers


library_includedir = $(includedir)/$(core)

nobase_include_HEADERS = $(core)/TwitterConstants.h $(core)/TwitterSession.h $(core)/TwitterRequest.h $(core)/CurlProcess.h $(core)/OAuth.h $(core)/TwitterRequestListener.h $(core)/RequestCreator.h


nobase_dist_include_HEADERS = $(core)/TwitterConstants.h $(core)/TwitterSession.h $(core)/TwitterRequest.h $(core)/CurlProcess.h $(core)/OAuth.h $(core)/TwitterRequestListener.h $(core)/RequestCreator.h
