NAME    := minishell
CFLAGS =  -g -Wall -Wextra -Werror #-lreadline #-L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include
LIBFT := ./libft
CC = cc

HEADERS := -I. -I$(LIBFT)
LIBS    := -ldl -pthread -lm -lreadline $(LIBFT)/libft.a 
SRCS    := files/main.c files/main_helper.c \
           files/buildins/buildins.c files/buildins/buildins_ex.c files/buildins/env.c \
           files/buildins/export.c files/buildins/export_sort.c files/buildins/export_buildin.c files/buildins/mini_exit.c \
           files/buildins/nodes.c files/extra/error_lines.c files/extra/error_lines2.c files/execute/path.c\
           files/execute/execute.c files/execute/handle_files.c files/execute/close_pipes.c\
           files/extra/free.c files/extra/helperfunc.c files/extra/helperfunc2.c \
           files/parsing/parsing.c files/buildins/cd.c files/buildins/echo.c files/buildins/unset.c \
		   files/execute/ex_tra.c files/execute/heredoc.c files/extra/helperfunc4.c \
		   files/extra/helperfunc3.c files/signals.c files/signals2.c files/parsing/var_expansion.c files/parsing/redirections.c \
		   files/parsing/tokenize.c files/execute/heredoc_pro.c files/parsing/var_expansion_utils.c files/buildins/shlvl.c files/extra/free2.c \
		   files/buildins/one_extra_norminette.c
OBJS    := ${SRCS:.c=.o}

all:  libft $(NAME)

libft:
	@make -C $(LIBFT)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

files/%.o: files/%.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(HEADERS) -o $(NAME) $(LIBS)  # Move $(LIBS) to the end

clean:
	@rm -rf $(OBJS)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re libft
