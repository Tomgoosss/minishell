/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:39:06 by tgoossen          #+#    #+#             */
/*   Updated: 2024/10/25 17:43:33 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"

static int	heredoc_fork(int *pipefd, pid_t *pid)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork");
		return (-1);
	}
	return (0);
}

int	heredoc(char *delimiter)
{
	int		pipefd[2];
	pid_t	pid;
	int		result;

	if (heredoc_fork(pipefd, &pid) == -1)
		return (-1);
	if (pid == 0)
	{
		close(pipefd[0]);
		heredoc_c_process(pipefd[1], delimiter);
	}
	else
	{
		close(pipefd[1]);
		signal(SIGINT, SIG_IGN);
		result = heredoc_p_process(pid, pipefd[0], delimiter);
		return (result);
	}
	return (-1);
}

int	red_in_heredoc(t_redirection *red)
{
	int	fd;

	fd = heredoc(red->file);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2 red_in_heredoc");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
