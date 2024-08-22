NAME = pipex
CC = cc
CFLAG = -g -Wall -Wextra -Werror
HEADERS = pipex.h
SRCS = pipex.c pipex_split.c command_split.c
OBJS = $(SRCS:.c=.o)

LIBRARY_DIR = libft
LIBRARY = $(LIBRARY_DIR)/libft.a

all : $(NAME)

$(NAME) : $(OBJS)
	@$(MAKE) -C $(LIBRARY_DIR)
	$(CC) $(CFLAG) $(OBJS) $(LIBRARY) -o $@

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	@$(MAKE) -C $(LIBRARY_DIR) fclean
	rm -rf $(OBJS) $(LIBRARY)

fclean :
	@$(MAKE) -C $(LIBRARY_DIR) fclean
	rm -rf $(OBJS) $(LIBRARY) $(NAME)

re :
	@make fclean
	@make all
