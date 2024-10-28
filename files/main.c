/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:39:28 by tgoossen          #+#    #+#             */
/*   Updated: 2024/10/28 17:12:20 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

extern int	g_signal;

static void	handle_signal_status(t_ex *ex)
{
	if (g_signal)
	{
		if (g_signal == 1)
			ex->exit_status = 130;
		else if (g_signal == 2)
			ex->exit_status = 0;
		g_signal = 0;
	}
}

static void	execute_command(t_token *token, t_env *var, t_ex *ex)
{
	if (ft_strcmp(token->command[0], "minishell") == 0
		|| ft_strcmp(token->command[0], "./minishell") == 0)
		signals_ignore();
	main_execute(token, var, ex);
}

static t_ex	*init_loop(t_token **token)
{
	t_ex	*ex;

	*token = NULL;
	ex = ft_calloc(1, sizeof(t_ex));
	if (!ex)
		exit(errno);
	copy_dup(ex, 1);
	return (ex);
}

void	loop(t_env *var)
{
	char	*line;
	t_token	*token;
	t_ex	*ex;
	int		exitcode;

	ex = init_loop(&token);
	while (1)
	{
		setup_signals();
		handle_signal_status(ex);
		line = readline("minishell> ");
		if (!line)
			break ;
		if (!process(line, &token, var, ex))
			continue ;
		exitcode = check_exit(token->command);
		if (exitcode != 0)
			cleanup_and_exit(line, ex, exitcode);
		execute_command(token, var, ex);
		add_history(line);
		free_token_line(token, line);
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
