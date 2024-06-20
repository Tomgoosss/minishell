/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:09:51 by fbiberog          #+#    #+#             */
/*   Updated: 2024/06/20 12:59:06 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//check_whitespaces function is used to skip whitespaces in the line
// it returns -1 if there is no whitespace in the line or there is nothing after the whitespace
int	check_whitespaces(char *line, int i)
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

// //check_redirections function is used to check if there is any redirection in the line
// // it returns -1 if there is no redirection in the line
// // it returns 1 if there is a redirection in the line
// // it returns 0 if there is a redirection in the line but it is not valid, valid means that there is a file after the redirection
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
					&& line[i + 1] == '>')) && check_whitespaces(line, (i + 2)) == 1)
			return (1);
		if (check_whitespaces == -1)
			return (0);
		i++;
	}
	return (0);
}

int closing_quote(char *line, int i, char c)
{
	i++;
	while(line[i])
	{
		if(line[i] == c)
			return (i + 1);
		i++;
	}
	return (0);
}

void	main_pars(char *line, t_env *var)
{
		
	return;
}
