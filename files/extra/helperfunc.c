/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperfunc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:39:16 by tgoossen          #+#    #+#             */
/*   Updated: 2024/10/22 15:39:17 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_strings(char const *s, char c)
{
	int	strings;
	int	len;
	int	quote_len;

	strings = 0;
	len = 0;
	quote_len = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = get_token_length(s, &quote_len);
			strings++;
			s += len;
		}
		else
			s++;
	}
	return (strings);
}

static void	handle_quote(char s_k, char *outer_quote, char *inner_quote,
		char *token, int *j)
{
	if (*outer_quote == 0)
		*outer_quote = s_k;
	else if (s_k == *outer_quote)
		*outer_quote = 0;
	else if (*inner_quote == 0)
	{
		*inner_quote = s_k;
		token[(*j)++] = s_k;
	}
	else if (s_k == *inner_quote)
	{
		*inner_quote = 0;
		token[(*j)++] = s_k;
	}
}

static char	*extract_token(const char *s, int len)
{
	char	*token;
	int		j;
	int		k;
	char	outer_quote;
	char	inner_quote;

	token = malloc(len + 1);
	if (!token)
		return (NULL);
	j = 0;
	k = 0;
	outer_quote = 0;
	inner_quote = 0;
	while (k < len)
	{
		if (is_quote(s[k]))
			handle_quote(s[k], &outer_quote, &inner_quote, token, &j);
		else
			token[j++] = s[k];
		k++;
	}
	token[j] = '\0';
	return (token);
}

static char	**allocate_and_fill(char const *s, char c, int strings)
{
	char	**str;
	int		i;
	int		len;
	int		quote_len;

	str = malloc((strings + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	i = 0;
	len = 0;
	quote_len = 0;
	while (i < strings)
	{
		while (*s == c)
			s++;
		len = get_token_length(s, &quote_len);
		str[i] = extract_token(s, len);
		if (!str[i])
			return (free_str_array(str, i), NULL);
		s += len;
		i++;
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split_mod(char const *s, char c)
{
	int	strings;

	if (s == NULL)
		return (NULL);
	strings = count_strings(s, c);
	return (allocate_and_fill(s, c, strings));
}
