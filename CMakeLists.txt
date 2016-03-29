cmake_minimum_required (VERSION 3.4)
project (ExtraWork CXX)

include_directories(Client ExtraWork)

add_executable(client Client/main.cpp)

if(MSVC)
	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /DEF:extrawork.def")
endif()

add_library(IX86ExtraWork SHARED ExtraWork/extrawork.def ExtraWork/extrawork.cpp ExtraWork/extrawork.h)