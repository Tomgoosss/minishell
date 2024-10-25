/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:39:28 by tgoossen          #+#    #+#             */
/*   Updated: 2024/10/25 18:08:14 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

extern int	g_signal;

void	error_msg(char *line, int i)
{
	if (i == 1)
		ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("\n", 2);
}

int	unclosed_quote(char *line, t_ex *ex)
{
	int	i;
	int	quote_type;
	int	in_quote;

	i = 0;
	in_quote = 0;
	quote_type = 0;
	while (line[i])
	{
		if (!in_quote && (line[i] == '\'' || line[i] == '"'))
		{
			in_quote = 1;
			quote_type = line[i];
		}
		else if (in_quote && line[i] == quote_type)
		{
			in_quote = 0;
			quote_type = 0;
		}
		i++;
	}
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

void	loop(t_env *var)
{
	char	*line;
	t_token	*token;
	t_ex	*ex;
	int		exitcode;

	token = NULL;
	ex = ft_calloc(1, sizeof(t_ex));
	if (!ex)
		exit(errno);
	exitcode = 0;
	copy_dup(ex, 1);
	while (1)
	{
		setup_signals();
		if (g_signal)
		{
			if (g_signal == 1)
				ex->exit_status = 130;
			else if (g_signal == 2)
				ex->exit_status = 0;
			g_signal = 0;
		}
		line = readline("minishell> ");
		if (!line)
			break ;
		if (unclosed_quote(line, ex))
		{
			free(line);
			continue ;
		}
		sort_export(var);
		token = main_pars(line, var, ex);
		if (!token)
			continue ;
		if ((exitcode = check_exit(token->command)) != 0)
		{
			rl_clear_history();
			free(line);
			free(ex);
			exit(exitcode);
		}
		if (ft_strcmp(token->command[0], "minishell") == 0
			|| ft_strcmp(token->command[0], "./minishell") == 0)
			signals_ignore();
		main_execute(token, var, ex);
		add_history(line);
		free_token(token);
		free(line);
		copy_dup(ex, 2);
	}
	free(ex);
	rl_clear_history();
}

int	main(int argc, char **argv, char **environment)
{
	t_env	*var;

	setup_signals();
	argc = 0;
	argv = NULL;
	var = ft_calloc(1, sizeof(t_env));
	if (!var)
		exit(1);
	fill_nodes_env(var, environment);
	loop(var);
	free_env(var);
	return (0);
}
