#include "minishell.h"

void	error_lines(char *arg, int i)
{
	if (i == 1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (i == 2)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (i == 3)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd("not enough arguments: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("\n", 2);
	}
}

int find_path(char **temp_path, t_ex *ex, t_token *token)
{
	int i;

	i = 0;
	if (access(token->command[0], X_OK) == 0)
	{
		ex->path = ft_strdup(token->command[0]);
		free2pointers(temp_path);
		return(0);
	}
	while(temp_path[i])
	{
		ex->path = ft_strjoin(temp_path[i], "/");
		ex->path = ft_strjoinfree(ex->path, token->command[0]);
		if(access(ex->path, X_OK) == 0)
		{
			// printf("check path = %s\n", ex->path);
			free2pointers(temp_path);
			return(0);
		}
		free(ex->path);
		i++;
	}
	free2pointers(temp_path);
	return(1);
}

void make_path(t_token *token, t_ex *ex, t_env *var)
{
	int i;
	char **temp_path;

	i = 0;
	while(var->env && ft_strncmp(var->env[i], "PATH=", 5) != 0)
		i++;
	temp_path = ft_split(var->env[i] + 5, ':');
	if(find_path(temp_path, ex, token) == 0 || check_buildin(token))
		return ;
	error_lines(token->command[0], 1);
	// free structs
	exit(127);
}

// void dup_choose(t_ex *ex, int count)
// {
// 	if (count == 0 && ex->amound_commands >= 2)
// 		dup2(ex->fd[1], STDOUT_FILENO);
// 	else
// 		dup2
// }


void execute(t_token *token, t_ex *ex, t_env *var, int count)
{
	int temp;
	temp = open_files(token);
	if(temp == -1)
	{
		//free some struct
		free2pointers(ex->path);
		exit(errno);
	}
	// dup_choose(ex, count);
	if (check_if_buildin(token, var) == 1)
	{
		exit(0);
	}
	// printf("test\n");
	if(execve(ex->path, token->command, var->env) == -1)
	{
		error_lines(token->command[0], 1);
		exit(errno);
	}
}

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


int create_child(t_token *token, t_ex *ex, t_env *var, int count)
{
	int p;
	int status;

	p = fork();
	if(p == -1)
	{
		perror("fork");
		exit(errno);
	}
	if(p == 0)
	{
		make_path(token, ex, var);
		if(!ex->path)
		{
			exit(1);
		}
		if(ex->amound_commands > 1)
			close_pipes_child(ex, count);
		execute(token, ex, var, count);
		// if execve fails, then cleanup and close
		exit(1);

	}
	else
	{
		if(ex->amound_commands > 1)
			close_pipes_par(ex, count);
		if (ex->path)
        {
            free(ex->path);
            ex->path = NULL;
        }
		if(count == ex->amound_commands - 1)
		{
			while(wait(&status) > 0)
				continue;
        	waitpid(p, &status, 0);
       		return(WEXITSTATUS(status));
		}
	}
	return(0);
}

int count_nodes(t_token *token)
{
	t_token *temp;
	int count;

	count = 0;
	temp = token;
	while(temp)
	{
		count++;
		temp = temp->next;
	}
	return(count);
}

void	main_execute(t_token *token, t_env *var, t_ex *ex) 
{
	int i;
	t_redirection *red;
	int count_commands;
	int last_status;



	i = 0;
	ex->amound_commands = count_nodes(token);
	while(token)
	{
		if(ex->amound_commands > 1 && i < ex->amound_commands - 1)
		{
			if(pipe(ex->fd) == -1)
			{
				perror("pipe failed");
				exit(errno);
			}
		}
		// printf("Creating child process %d\n", i);
		last_status = create_child(token, ex, var, i);
		// printf("Child process %d created with pid %d\n", i, pid);
		if(i > 0)
			close(ex->prev_fd[0]);
		if (i <= ex->amound_commands - 1 && ex->amound_commands > 0)
			ex->prev_fd[0] = ex->fd[0];
		if(ex->path)
		{
			free(ex->path);
			ex->path = NULL;
		}
		i++;
		token = token->next;
	}
	ex->exit_status = last_status;
}