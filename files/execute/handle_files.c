#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>


static void heredoc_child_process(int write_fd, char *delimiter)
{
	char *line;

	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
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
		free(line);
	}
}

static int heredoc_parent_process(pid_t pid, int read_fd)
{
	int status;

	waitpid(pid, &status, 0);

	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
	{
		return read_fd;
	}
	else
	{
		ft_putstr_fd("Heredoc was interrupted.\n", STDERR_FILENO);
		close(read_fd);
		return -1;
	}
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
		close(pipefd[0]); // Close read end
		heredoc_child_process(pipefd[1], delimiter);
	}
	else // Parent process
	{
		close(pipefd[1]); // Close write end
		return heredoc_parent_process(pid, pipefd[0]);
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

int red_out_append(t_redirection *red)
{
	int fd;

	fd = open(red->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("ERROR");
		return(fd);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 red_out_append");
		close(fd);
		return(1);
	}
	close(fd);
	return(0);
}
int red_out(t_redirection *red)
{
	int fd;

	fd = open(red->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd == -1)
	{
		perror("ERROR");
		return (fd);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 red_out");
		close(fd);
		return(1);
	}
	close(fd);
	return(0);
}

int red_in(t_redirection *red)
{
	int fd;

	fd = open(red->file, O_RDONLY);
	if (fd == -1)
	{
		perror("ERROR");
		return(fd);
	}
	if(dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2 red_in");
		close(fd);
		return(1);
	}
	close(fd);
	return(0);
}

int open_files(t_token *token)
{
	t_redirection *red;
	int result;

	result = 0;
	red = token->redirection;
	while(red)
	{
		if(red->type == REDIR_OUT_APPEND)
			result = red_out_append(red);
		else if(red->type == REDIR_OUT)
			result = red_out(red);
		else if(red->type == REDIR_IN_HERE_DOC)
			red_in_heredoc(red);
		else if(red->type == REDIR_IN)
			result = red_in(red);
		else 
			result = 0;
		if (result != 0)
			return(result);
		red = red->next;
	}
	return(0);
}