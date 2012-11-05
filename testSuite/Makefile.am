
bin_PROGRAMS = testSuite

testSuite_SOURCES = src/tests.cpp \
					src/Test_Requests.h

AM_CPPFLAGS = `pkg-config libtwitter-core --cflags` `pkg-config cppunit --cflags`
testSuite_LDFLAGS = `pkg-config libtwitter-core --libs` `pkg-config cppunit --libs`