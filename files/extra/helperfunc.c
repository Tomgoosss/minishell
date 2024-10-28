/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperfunc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:39:16 by tgoossen          #+#    #+#             */
/*   Updated: 2024/10/28 16:20:11 by fbiberog         ###   ########.fr       */
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

static void	handle_quote(char s_k, t_quote_info *q)
{
	if (q->outer_quote == 0)
		q->outer_quote = s_k;
	else if (s_k == q->outer_quote)
		q->outer_quote = 0;
	else if (q->inner_quote == 0)
	{
		q->inner_quote = s_k;
		q->token[q->j++] = s_k;
	}
	else if (s_k == q->inner_quote)
	{
		q->inner_quote = 0;
		q->token[q->j++] = s_k;
	}
}

static char	*extract_token(const char *s, int len)
{
	t_quote_info	q;
	int				k;

	q.token = malloc(len + 1);
	if (!q.token)
		return (NULL);
	k = 0;
	q.j = 0;
	q.outer_quote = 0;
	q.inner_quote = 0;
	while (k < len)
	{
		if (is_quote(s[k]))
			handle_quote(s[k], &q);
		else
			q.token[q.j++] = s[k];
		k++;
	}
	q.token[q.j] = '\0';
	return (q.token);
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
