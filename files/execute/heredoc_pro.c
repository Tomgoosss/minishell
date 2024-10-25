/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pro.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:15:05 by fbiberog          #+#    #+#             */
/*   Updated: 2024/10/25 17:44:24 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_heredoc_line(int write_fd, char *line, char *delimiter)
{
	if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
		&& (line[ft_strlen(delimiter)] == '\n'
			|| line[ft_strlen(delimiter)] == '\0'))
	{
		free(line);
		close(write_fd);
		exit(EXIT_SUCCESS);
	}
	write(write_fd, line, ft_strlen(line));
	write(write_fd, "\n", 1);
	free(line);
}

void	heredoc_c_process(int write_fd, char *delimiter)
{
	char				*line;
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	while (1)
	{
		line = readline("> ");
		if (!line || g_signal == 1)
		{
			close(write_fd);
			exit(EXIT_FAILURE);
		}
		process_heredoc_line(write_fd, line, delimiter);
	}
}

int	heredoc_p_process(pid_t pid, int read_fd, char *delimiter)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(read_fd);
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (-1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
	{
		return (read_fd);
	}
	ft_putstr_fd("warning: here-document delimited by end-of-file (wanted `",
		STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
	close(read_fd);
	return (-1);
}
