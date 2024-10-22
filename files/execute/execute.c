/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:39:00 by tgoossen          #+#    #+#             */
/*   Updated: 2024/10/22 15:39:01 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_child(t_token *token, t_ex *ex, t_env *var)
{
	int	temp;

	reset_signals();
	temp = open_files(token, 0);
	if (temp == -1)
	{
		free(ex->path);
		ex->path = NULL;
		exit(1);
	}
	if (check_if_buildin(token, var) == 0)
	{
		ex->exit_status = 0;
		exit(0);
	}
	if (execve(ex->path, token->command, var->env) == -1)
	{
		error_lines(token->command[0], 1);
		exit(errno);
	}
	exit(1);
}

int	parent_process(t_ex *ex, int p, int count)
{
	int	status;

	if (ex->amound_commands > 1)
		close_pipes_par(ex, count);
	if (ex->path)
	{
		free(ex->path);
		ex->path = NULL;
	}
	if (count == ex->amound_commands - 1)
	{
		signals_ignore();
		waitpid(p, &status, 0);
		while (count > 0)
		{
			wait(NULL);
			count--;
		}
		return (WEXITSTATUS(status));
	}
	return (0);
}

int	create_child(t_token *token, t_ex *ex, t_env *var, int count)
{
	int	p;

	signals_ignore();
	p = fork();
	if (p == -1)
	{
		perror("fork");
		exit(errno);
	}
	if (p == 0)
	{
		reset_signals();
		make_path(token, ex, var);
		if (!ex->path)
			exit(127);
		if (ex->amound_commands > 1)
			close_pipes_child(ex, count);
		execute_child(token, ex, var);
	}
	return (parent_process(ex, p, count));
}

int	execute(t_token *token, t_env *env, t_ex *ex, int count)
{
	int	last_status;
	int	temp;

	temp = 0;
	last_status = 0;
	make_2d_env(env);
	if (find_slash(token) == 1)
		return (check_if_dir(token));
	temp = open_files(token, 1);
	if (temp == -1)
	{
		free(ex->path);
		ex->path = NULL;
		return (errno);
	}
	if (check_buildin(token) == 1 && ex->amound_commands == 1)
	{
		last_status = check_if_buildin(token, env);
	}
	else
	{
		last_status = create_child(token, ex, env, count);
	}
	return (last_status);
}

void	main_execute(t_token *token, t_env *env, t_ex *ex)
{
	int	i;
	int	last_status;

	i = 0;
	ex->amound_commands = count_nodes(token);
	while (token)
	{
		setup_pipe(ex, i);
		last_status = execute(token, env, ex, i);
		cleanup_execution(ex, i);
		i++;
		token = token->next;
	}
	ex->exit_status = last_status;
}
