NAME = pipex
CC = cc -Wall -Wextra -Werror
HEADERS = pipex.h
SRCS = pipex.c
OBJS = $(SRCS(.c=.o))

all : name
