#include "minishell.h"

static void heredoc_child_process(int write_fd, char *delimiter, t_ex *ex)
{
	char *line;
	struct sigaction sa;

	// Set up a custom signal handler for SIGINT in the child process
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

		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0 &&
				(line[ft_strlen(delimiter)] == '\n' || line[ft_strlen(delimiter)] == '\0'))
		{
			free(line);
			close(write_fd);
			exit(EXIT_SUCCESS);
		}

		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
}

static int heredoc_parent_process(pid_t pid, int read_fd, char *delimiter)
{
	int status;

	waitpid(pid, &status, 0);

	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		g_signal = 1;
		close(read_fd);
		return -1;
	}

	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
	{
		return read_fd;
	}

	if (g_signal != 1)  // Only print this message if not interrupted by SIGINT
	{
		ft_putstr_fd("warning: here-document delimited by end-of-file (wanted `", STDERR_FILENO);
		ft_putstr_fd(delimiter, STDERR_FILENO);
		ft_putstr_fd("')\n", STDERR_FILENO);
	}
	close(read_fd);
	return -1;
}

static int heredoc_fork(int *pipefd, pid_t *pid)
{
	if (pipe(pipefd) == -1) 
	{
		perror("pipe");
		return -1;
	}
	*pid = fork();
	if (*pid == -1) 
	{
		perror("fork");
		return -1;
	}
	return 0;
}

int heredoc(char *delimiter, t_ex *ex)
{
	int pipefd[2];
	pid_t pid;

	if (heredoc_fork(pipefd, &pid) == -1)
		return -1;
	if (pid == 0) // Child process
	{
		close(pipefd[0]); // Close read end
		heredoc_child_process(pipefd[1], delimiter, ex);
	}
	else // Parent process
	{
		close(pipefd[1]); // Close write end
		return heredoc_parent_process(pid, pipefd[0], delimiter);
	}
	return (1);
}

int red_in_heredoc(t_redirection *red, t_ex *ex)
{
	int fd;

	fd = heredoc(red->file, ex);
	if (fd == -1)
	{
		// perror("ERROR");
		return -1;  // Return -1 to indicate an error
	}

	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2 red_in_heredoc");
		close(fd);
		return -1;  // Return -1 to indicate an error
	}
	close(fd);
	return 0;  // Return 0 to indicate success
}
