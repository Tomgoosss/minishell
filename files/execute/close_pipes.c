#include "minishell.h"

//fd[0] read
//fd[1] write
void 	close_pipes_par(t_ex *ex, int count)
{
	if (count == 0) // first command
	{
		close(ex->fd[1]);
	}
	else if(count < ex->amound_commands - 1) // middle command
	{
		close(ex->prev_fd[0]);
		close(ex->fd[1]);
	}
	else if (count == ex->amound_commands - 1)// last command
	{
		close(ex->prev_fd[0]);
	}
}
void close_pipes_child(t_ex *ex, int count)
{
    if (count == 0) // First command
    {
        close(ex->fd[0]);
        dup2(ex->fd[1], STDOUT_FILENO);
		close(ex->fd[1]);
    }
    else if(count < ex->amound_commands - 1)  // Middle commands
    {
        close(ex->fd[0]);
        dup2(ex->prev_fd[0], STDIN_FILENO);
        dup2(ex->fd[1], STDOUT_FILENO);
        close(ex->prev_fd[0]);
		close(ex->fd[1]);
    }
    else if (count == ex->amound_commands - 1) // Last command
    {
        dup2(ex->prev_fd[0], STDIN_FILENO);
        close(ex->prev_fd[0]);
    }
}

void copy_dup(t_ex *ex, int i)
{

    if (i == 1)
    {
        ex->in_dup = dup(STDIN_FILENO);
        ex->out_dup = dup(STDOUT_FILENO);
    }
    else if (i == 2)
    {
		dup2(ex->in_dup, STDIN_FILENO);
		dup2(ex->out_dup, STDOUT_FILENO);
    }
}

void cleanup_execution(t_ex *ex, int i)
{
    if (i > 0)
        close(ex->prev_fd[0]);
    if (i < ex->amound_commands - 1)
    {
        ex->prev_fd[0] = ex->fd[0];
    }
    if (ex->path)
    {
        free(ex->path);
        ex->path = NULL;
    }
}

void setup_pipe(t_ex *ex, int i)
{
    if (ex->amound_commands > 1 && i < ex->amound_commands - 1)
    {
        if (pipe(ex->fd) == -1)
        {
            perror("pipe failed");
            exit(errno);
        }
    }
}