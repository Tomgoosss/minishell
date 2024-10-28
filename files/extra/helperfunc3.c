/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperfunc3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:39:21 by tgoossen          #+#    #+#             */
/*   Updated: 2024/10/28 18:11:51 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_delimiter(const char *s)
{
	return (*s == '<' || *s == '>' || *s == '|');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static int	extra_check(const char *s)
{
	if ((*s == '<' && *(s + 1) == '<') || (*s == '>' && *(s + 1) == '>'))
		return (2);
	if (is_delimiter(s))
		return (1);
	return (0);
}

int	get_token_length(const char *s, int *quote_len)
{
	int		len;
	char	quote_char;

	len = 0;
	quote_char = 0;
	*quote_len = 0;
	if (extra_check(s))
		return (extra_check(s));
	while (s[len])
	{
		if (is_quote(s[len]) && quote_char == 0)
		{
			quote_char = s[len];
			(*quote_len)++;
		}
		else if (s[len] == quote_char)
		{
			quote_char = 0;
			(*quote_len)++;
		}
		else if (quote_char == 0 && (is_delimiter(s + len) || s[len] == ' '))
			break ;
		len++;
	}
	return (len);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*result;

	result = malloc(n + 1);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s, n);
	result[n] = '\0';
	return (result);
}
