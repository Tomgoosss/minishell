#include "minishell.h"

static void heredoc_child_process(int write_fd, char *delimiter)
{
	reset_signals();
	char *line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			perror("get_next_line");
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

	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
	{
		return read_fd;
	}
	if (g_signal == 1)  // Check for Ctrl+C
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		close(read_fd);
		return -1;
	}
	ft_putstr_fd("warning: here-document delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
	close(read_fd);
	return -1;
}

int heredoc(char *delimiter)
{
	int pipefd[2];
	pid_t pid;

	if (pipe(pipefd) == -1) 
	{
		perror("pipe");
		return -1;
	}

	pid = fork();
	if (pid == -1) {
		perror("fork");
		return -1;
	}
	if (pid == 0) // Child process
	{
		reset_signals(); // Reset signals for child process
		close(pipefd[0]); // Close read end
		heredoc_child_process(pipefd[1], delimiter);
	}
	else // Parent process
	{
		setup_signals(); // Set up signals for parent process
		close(pipefd[1]); // Close write end
		return heredoc_parent_process(pid, pipefd[0], delimiter);
	}
	return (1);
}

void red_in_heredoc(t_redirection *red)
{
	int fd;

	fd = heredoc(red->file);
	if (fd == -1)
	{
		perror("ERROR");
		return;
	}

	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2 red_in_heredoc");
		close(fd);
		return;
	}
	close(fd);
}