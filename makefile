NAME    := minishell
CFLAGS =  -g -Wall -Wextra -lreadline -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include #-Werror
LIBFT := ./libft
CC = cc

HEADERS := -I. -I$(LIBFT)
LIBS    := -ldl -pthread -lm $(LIBFT)/libft.a 
SRCS    := files/main.c \
           files/buildins/buildins.c files/buildins/buildins_ex.c files/buildins/env.c \
           files/buildins/export.c files/buildins/export_buildin.c files/buildins/mini_exit.c \
           files/buildins/nodes.c \
           files/execute/execute.c files/execute/handle_files.c \
           files/extra/free.c files/extra/helperfunc.c files/extra/helperfunc2.c \
           files/parsing/parsing.c
OBJS    := ${SRCS:.c=.o}

all:  libft $(NAME)

libft:
	@make -C $(LIBFT)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

files/%.o: files/%.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re libft
