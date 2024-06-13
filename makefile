NAME    := minishell
CFLAGS =  -Wall -Wextra -lreadline #-L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include #-Werror
LIBFT := ./libft
CC = cc

HEADERS := -I./include -I /include -I$(LIBFT)
LIBS    := -ldl -pthread -lm $(LIBFT)/libft.a 
SRCS    :=	files/main.c files/free.c files/nodes.c files/parsing.c
OBJS    := ${SRCS:.c=.o}

all:  libft $(NAME)

libft:
	@make -C $(LIBFT)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

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
