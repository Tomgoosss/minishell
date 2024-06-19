#include "../minishell.h"
int is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	size_no_whitespace(char *line)
{
	int	i;
	int	size;
	int	reset;

	i = 0;
	size = 0;
	reset = 0;
	while (line[i] != '\0')
	{
		if (!is_space(line[i]))
		{
			reset = 1;
			size++;
		}
		else if (reset == 1)
		{
			reset = 0;
			size++;
		}
		i++;
	}
	return (size);
}

char	*remove_white_spaces(char *line)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = 0;
	new_line = malloc(sizeof(char) * (size_no_whitespace(line) + 1));
	while (line[i])
	{
		if (!is_space(line[i]))
		{
			new_line[j] = line[i];
			j++;
		}
		else if (j > 0 && !is_space(line[i + 1]))
		{
			new_line[j] = ' ';
			j++;
		}
		i++;
	}
	new_line[j] = '\0';
	return (new_line);
}
//problem with remove_white_spaces is that export name=123 cant have any spaces inbetween name and 123