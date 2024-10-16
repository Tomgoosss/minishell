#include "minishell.h"

int empty_line(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] > 32 && line[i] <= 126)
			return (0);
		i++;
	}
	return (1);
}

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
	if (!str || *str == '\0')
	{
		printf("syntax error near unexpected token `newline'\n");
		return (0);
	}
	if (is_meta_character(str))
	{
		printf("syntax error near unexpected token `%c'\n", str[0]);
		return (0);
	}
	if (not_print_str(str))
	{
		printf("syntax error: invalid filename\n");
		return (0);
	}
	return (1);
}
