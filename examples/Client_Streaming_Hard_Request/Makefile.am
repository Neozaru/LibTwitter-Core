
bin_PROGRAMS = Client_streaming

Client_streaming_SOURCES = Client_Streaming.cpp \
							MyTwitterRequest.h

AM_CPPFLAGS = `pkg-config libtwitter-core --cflags`
Client_streaming_LDFLAGS = `pkg-config libtwitter-core --libs`