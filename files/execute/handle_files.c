#include "minishell.h"


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

// void red_in_heredoc(t_redirection *red)
// {
// 	int fd;

// 	fd = open()
// }

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
		// else if(red->type == REDIR_IN_HERE_DOC)
		// 	red_in_heredoc(red);
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