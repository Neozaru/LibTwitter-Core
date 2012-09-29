project(LibTwitter-Core)

file(
	GLOB_RECURSE
	source_files
	src/Twitter/Core/*.h
	src/Twitter/Core/*.cpp
	src/Twitter/Core/Utils/*.cpp
	src/Twitter/Core/Utils/*.h
	src/Twitter/Core/Parsers/*.cpp
	src/Twitter/Core/Parsers/*.h
)


add_library( twitter-core STATIC 
			${source_files} 
			)

