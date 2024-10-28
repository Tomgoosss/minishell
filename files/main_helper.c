/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:56:15 by fbiberog          #+#    #+#             */
/*   Updated: 2024/10/28 17:12:28 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(char *line, int i)
{
	if (i == 1)
		ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("\n", 2);
}

static int	check_quote_status(char *line, int *in_quote, int *quote_type)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!*in_quote && (line[i] == '\'' || line[i] == '"'))
		{
			*in_quote = 1;
			*quote_type = line[i];
		}
		else if (*in_quote && line[i] == *quote_type)
		{
			*in_quote = 0;
			*quote_type = 0;
		}
		i++;
	}
	return (i);
}

int	unclosed_quote(char *line, t_ex *ex)
{
	int	in_quote;
	int	quote_type;

	in_quote = 0;
	quote_type = 0;
	check_quote_status(line, &in_quote, &quote_type);
	if (in_quote)
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for matching `",
			2);
		ft_putchar_fd(quote_type, 2);
		ft_putstr_fd("'\n", 2);
		ex->exit_status = 2;
		return (1);
	}
	return (0);
}

void	cleanup_and_exit(char *line, t_ex *ex, int exitcode)
{
	rl_clear_history();
	free(line);
	free(ex);
	exit(exitcode);
}

int	process(char *line, t_token **token, t_env *var, t_ex *ex)
{
	if (unclosed_quote(line, ex))
	{
		free(line);
		return (0);
	}
	sort_export(var);
	*token = main_pars(line, var, ex);
	if (!*token)
		return (0);
	return (1);
}
