NAME = pipex
MANDATORY_NAME = .pipex_mandatory
BONUS_NAME = .pipex_bonus

CC = cc
CFLAG = -Wall -Wextra -Werror
HEADERS = pipex.h
SRCS_DIR = mandatory
SRCS = main.c	\
		pipex.c	\
		pipex_split.c	\
		make_parse.c	\
		error_control.c

OBJS = $(SRCS:.c=.o)
HEADERS := $(addprefix $(SRCS_DIR)/, $(HEADERS))
SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))

BONUS_DIR = bonus
BONUS_HEADERS = pipex_bonus.h
BONUS_SRCS = main_bonus.c	\
			pipex_bonus.c	\
			pipex_split_bonus.c	\
			make_parse_bonus.c	\
			error_control_bonus.c	\
			here_doc_bonus.c

BONUS_OBJS = $(BONUS_SRCS:.c=.o)
BONUS_HEADERS := $(addprefix $(BONUS_DIR)/, $(BONUS_HEADERS))
BONUS_SRCS := $(addprefix $(BONUS_DIR)/, $(BONUS_SRCS))

LIBRARY_DIR = libft
LIBRARY = $(LIBRARY_DIR)/libft.a

all : $(MANDATORY_NAME)

$(NAME) : $(OBJS)
	@$(MAKE) -C $(LIBRARY_DIR)
	$(CC) $(CFLAG) $(OBJS) $(LIBRARY) -o $@

$(MANDATORY_NAME) : $(OBJS)
	@$(MAKE) -C $(LIBRARY_DIR)
	$(CC) $(CFLAG) $(OBJS) $(LIBRARY) -o $@
	cp $(MANDATORY_NAME) $(NAME)
	@rm -rf $(BONUS_NAME)

$(SRCS_DIR)%.o : $(SRCS_DIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

bonus : $(BONUS_NAME)

$(BONUS_NAME) : $(BONUS_OBJS)
	@$(MAKE) -C $(LIBRARY_DIR)
	$(CC) $(CFLAG) $(BONUS_OBJS) $(LIBRARY) -o $@
	cp $(BONUS_NAME) $(NAME)
	@rm -rf $(MANDATORY_NAME)

$(BONUS_DIR)%.o : $(BONUS_DIR)%.c $(BONUS_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	@$(MAKE) -C $(LIBRARY_DIR) fclean
	rm -rf $(OBJS) $(BONUS_OBJS) $(LIBRARY)

fclean :
	@$(MAKE) -C $(LIBRARY_DIR) fclean
	rm -rf $(OBJS) $(BONUS_OBJS) $(LIBRARY) $(NAME) $(MANDATORY_NAME) $(BONUS_NAME)

re :
	@make fclean
	@make all
