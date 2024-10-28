/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperfunc4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:39:23 by tgoossen          #+#    #+#             */
/*   Updated: 2024/10/28 16:37:15 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoinfree(char const *s1, char const *s2)
{
	int		i;
	int		y;
	int		s1s2count;
	char	*copy;

	s1s2count = ft_strlen(s1) + ft_strlen(s2);
	copy = (char *)malloc((s1s2count + 1) * sizeof(char));
	i = 0;
	if (copy == 0)
		return (NULL);
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	y = 0;
	while (s2[y])
	{
		copy[i] = s2[y];
		y++;
		i++;
	}
	copy[i] = '\0';
	free((char *)s1);
	return (copy);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (1);
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

void	free_str_array(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
}

char	*ft_substr_mod(char const *s, unsigned int start, size_t len)
{
	char	*countm;
	size_t	lengs;
	size_t	i;

	lengs = ft_strlen(s);
	i = 0;
	if (start >= lengs || len == 0)
		return (ft_strdup(""));
	if (start + len > lengs)
		len = lengs - start;
	countm = (char *)malloc((len + 1) * sizeof(char));
	if (countm == 0)
		return (NULL);
	while (i < len)
	{
		countm[i] = s[i + start];
		i++;
	}
	countm[i] = '\0';
	return (countm);
}

int	is_valid_identifier(const char *str)
{
	int	i;

	i = 0;
	if (!str || !(*str) || (!ft_isalpha(*str) && *str != '_'))
		return (0);
	str++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
