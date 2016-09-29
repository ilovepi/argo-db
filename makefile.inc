## For students: change this path to the root of your code if this doesn't work
CODEROOT = ..

#CC = gcc
#CC = g++
CC = clang++

#CPPFLAGS = -Wall -I$(CODEROOT) -g     # with debugging info
CPPFLAGS = -Wall -I$(CODEROOT) -g -std=c++14  # with debugging info and the C++11 feature
