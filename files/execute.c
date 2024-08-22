#include "../minishell.h"

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
		printf("test");
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
			free2pointers(temp_path);
			return(0);
		}
		free(ex->path);
		i++;
	}
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
	free2pointers(temp_path);
	error_lines(token->command[0], 1);
	// free structs
	exit(127);
}

// void execute(t_token *token, t_ex *ex, t_env *var)
// {
// 	open_files(token);
// }

// int create_child(t_token *token, t_ex *ex, t_env *var)
// {
// 	int temp_fd;
// 	int p;

// 	pipe(ex->fd);
// 	p = fork();
// 	temp_fd = 0;

// 	if(p == -1)
// 	{
// 		perror("fork");
// 		exit(errno);
// 	}
// 	if(p == 0)
// 	{
// 		make_path(token, ex, var);
// 		if(!ex->path)
// 		{
// 			exit(1);
// 		}
// 		execute(token, ex, var);
// 	}
// 	else
// 	{

// 	}
// }

void	main_execute(t_token *token, t_env *var) 
{
	int i;
	t_ex *execute;
	t_redirection *red;

	execute = ft_calloc(1, sizeof(t_ex));
	if(!execute)
		exit(errno);
	i = 0;

	// Check if command is builtins
	// make_path(token, execute, var);
	printf("check path = %s\n", execute->path);
	// check_if_buildin(token, var);
	// Else run execve
	// create_child(token, execute, var);


}