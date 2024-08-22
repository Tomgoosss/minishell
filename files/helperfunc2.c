#include "../minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v'
		|| c == '\f')
		return (1);
	return (0);
}

int	not_print_str(char *c)
{
	int	i;

	i = 0;
	if (!c)
		return (0);
	while (c[i])
	{
		if (c[i] < 32 || c[i] > 126)
			return (1);
		i++;
	}
	return (0);
}

int	is_meta_character(char *str)
{
	if (ft_strchr(str, '>') || ft_strchr(str, '<') || ft_strchr(str, '|'))
		return (1);
	return (0);
}

int	valid_redirection(char *str)
{
	if (!str)
	{
		printf("syntax error near unexpected token `newline'\n");
		return (0);
	}
	if (is_meta_character(str) || not_print_str(str))
	{
		printf("not valid\n");
		printf("%i\n", is_meta_character(str));
		printf("%i\n", not_print_str(str));
		printf("syntax error near unexpected token `%c'\n", str[0]);
		return (0);
	}
	printf("valid\n");
	return (1);
}