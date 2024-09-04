#include "minishell.h"

void	error_lines(char *arg, int i)
{
	if (i == 1)
		ft_putstr_fd("command not found: ", 2);
	if (i == 2)
		ft_putstr_fd("No such file or directory: ", 2);
	if (i == 3)
		ft_putstr_fd("not anough arguments: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\n", 2);
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
	if(find_path(temp_path, ex, token) == 0)
		return ;
	error_lines(token->command[0], 1);
	// free structs
	exit(127);
}

void execute(t_token *token, t_ex *ex, t_env *var)
{
	int temp;
	temp = open_files(token);
	if(temp == -1)
	{
		//free some struct
		free2pointers(ex->path);
		exit(errno);
	}
	if (check_if_buildin(token, var) == 1)
	{
		exit(0);
	}
	if(execve(ex->path, token->command, var->env) == -1)
	{
		perror("execve");
		free2pointers(ex->path);
		exit(errno);
	}
}

// void close_pipes_par(t_ex *ex, int count)
// {
// 	int i;

// 	i = 0;
// 	if (i == 0 && ex->amound_commands >= 2)
// 		close(ex->fd[1]);
// 	else
// 		close(ex->fd[0]);
// }
// void close_pipes_child(t_ex *ex, int count)
// {
// 	int i;

// 	i = 0;
// 	if (i == 0 && ex->amound_commands >= 2)
// 		close(ex->fd[0]);
// 	else
// 		close(ex->fd[1]);
	
// }

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
		// if(ex->amound_commands > 1)
		// 	close_pipes_child(ex, count);
		execute(token, ex, var);
	}
	else
	{
		free(ex->path);
		if(count == ex->amound_commands - 1)
		{
			waitpid(p, &status, 0);
			return(WEXITSTATUS(status));
		}
	}
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

void	main_execute(t_token *token, t_env *var) 
{
	int i;
	t_ex *execute;
	t_redirection *red;
	int count_commands;

	execute = ft_calloc(1, sizeof(t_ex));
	if(!execute)
		exit(errno);
	i = 0;
	execute->amound_commands = count_nodes(token);
	while(token)
	{
		// if(execute->amound_commands > 1 && i <= execute->amound_commands - 1)
		// 	pipe(execute->fd);
		create_child(token, execute, var, i);
		i++;
		token = token->next;
	}
}