/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomgoossens <tomgoossens@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:36:13 by tgoossen          #+#    #+#             */
/*   Updated: 2024/02/12 15:05:17 by tomgoossens      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

static void	free_str_array(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
}

char	**ft_split(char const *s, char c)
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

// int main(void)
// {
//     const char *dstr = "test,,hallo";
//     char split = ',';
//     char **result;

//     result = ft_split(dstr, split);

//         int i = 0;
//         while (result[i] && i < 5)
//         {
//             printf("%s\n", result[i]);
//             i++;
// 		}
// }
