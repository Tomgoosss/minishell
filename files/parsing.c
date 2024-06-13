/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:09:51 by fbiberog          #+#    #+#             */
/*   Updated: 2024/06/13 19:26:41 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_character(char *line, int i)
{
	if (!(line[i] == ' ' || line[i] == '\t' || line[i] == '\r'
			|| line[i] == '\n' || line[i] == '\v' || line[i] == '\f'))
		return (-1);
	while ((line[i] == ' ' || line[i] == '\t' || line[i] == '\r'
			|| line[i] == '\n' || line[i] == '\v' || line[i] == '\f')
		&& line[i])
	{
		i++;
		if (line[i] == '\0')
			return (-1);
	}
	return (1);
}

int	check_redirections(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
			break ;
		i++;
		if (line[i] == '\0')
			return (-1);
	}
	i = 0;
	while (line[i + 2])
	{
		if (((line[i] == '<' && line[i + 1] == '<') || ((line[i] == '>')
					&& line[i + 1] == '>')) && is_character(line, (i + 2)) == 1)
			return (1);
		if (is_character == -1)
			return (0);
		i++;
	}
	return (0);
}
int	closing_bracket(char *line, int i, char c)
{
	while (line[i])
	{
		if (line[i] == c)
			return (i + 1);
		i++;
	}
	return (0);
}
int	check_unclosed_brackets(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' && !closing_bracket(line, i + 1, '"'))
			return (0);
		if (line[i] == '"')
			i = closing_bracket(line, i + 1, '"');
		else
			i++;
	}
	i = 0;
	while (line[i])
	{
		if (line[i] == 39 && !closing_bracket(line, i + 1, 39))
			return (0);
		if (line[i] == 39)
			i = closing_bracket(line, i + 1, 39);
		else
			i++;
	}
	return (1);
}
void	main_pars(char *line, t_minishell *man)
{
	if (!check_redirections(line))
		printf("hallo\n");
	if (!check_unclosed_brackets(line))
		printf("tomstinkt\n");
}
