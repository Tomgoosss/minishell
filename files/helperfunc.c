#include "../minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v'
		|| c == '\f')
		return (1);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

static int	wordleng(char const *s, char c, int j)
{
	int	i;

	i = 0;
	while (s[j] != c && s[j] != '\0')
	{
		i++;
		j++;
	}
	return (i);
}
static int	stringcounter(char const *s, char c)
{
	int	str;
	int	t;

	t = 0;
	str = 0;
	while (*s != '\0')
	{
		if (*s != c && t == 0)
		{
			str++;
			t = 1;
		}
		if (*s == c)
		{
			t = 0;
		}
		s++;
	}
	return (str);
}
static void	free_str_array(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
}

char	**ft_split_mod(char const *s, char c)
{
	int		strings;
	int		i;
	char	**str;

	strings = stringcounter(s, c);
	str = malloc((strings + 1) * sizeof(char *));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < strings)
	{
		while (*s == c)
			s++;
		if(*s == '\'' || *s == '\"')
		{
			str[i] = ft_substr(s, 0, closing_quote(s, 0, *s));
			if (str[i] == NULL)
			{
				free_str_array(str, i);
				return (NULL);
			}
			s += closing_quote(s, 0, *s);
		}
		else
			str[i] = ft_substr(s, 0, wordleng(s, c, 0));
		if (str[i] == NULL)
		{
			free_str_array(str, i);
			return (NULL);
		}
		s += wordleng(s, c, 0);
		i++;
	}
	str[i] = NULL;
	return (str);
}
