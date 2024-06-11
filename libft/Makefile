sourcefiles = 	ft_itoa.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
				ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
				ft_memset.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c \
				ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
				ft_substr.c ft_tolower.c ft_toupper.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
				ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_atoi.c get_next_line.c get_next_line_utils.c \
				allbase.c ft_putstr.c ft_putchar.c ft_hexpointer.c ft_printf.c

objects =		$(sourcefiles:.c=.o)

NAME =			libft.a

all:			$(NAME)

$(NAME):		$(objects)
	ar rcs libft.a $(objects)

%.o: %.c
	cc -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -f $(objects)

fclean:
	rm -f $(objects) $(NAME)

re: 			fclean all