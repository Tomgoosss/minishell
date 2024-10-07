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
	else if (i == 4)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": too many arguments", 2);
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


void execute_child(t_token *token, t_ex *ex, t_env *var)
{
	int temp;
	temp = open_files(token);
	if(temp == -1)
	{
		//free some struct
		free(ex->path);
		ex->path = NULL;		
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
	exit(1);
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
			exit(127);
		}
		if(ex->amound_commands > 1)
			close_pipes_child(ex, count);
		execute_child(token, ex, var);
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
			waitpid(p, &status, 0);
			count--;
			while(count > 0)
			{
				wait(NULL);
				count--;
			}
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


// int check_if_red(t_token *token, t_ex *ex)
// {
// 	t_redirection *red;

// 	red = token->redirection;
// 	if(ex->amound_commands == 1)
// 	{
// 		if (red == NULL)
// 			return(0); 
// 		else if(red->type == REDIR_OUT_APPEND)
// 			return(1);
// 		else if(red->type == REDIR_OUT)
// 			return(1);
// 		else if(red->type == REDIR_IN_HERE_DOC)
// 			return(1);
// 		else if(red->type == REDIR_IN)
// 			return(1);
// 	}

// 	return(1);
// }

int execute(t_token *token, t_env *env, t_ex *ex, int count)
{
	int last_status;
	int temp;

	temp = 0;
	last_status = 0;
	if(check_buildin(token) == 1 && ex->amound_commands == 1)
	{
		temp = open_files(token);
		if(temp == -1)
		{
			//free some struct
			free(ex->path);
			ex->path = NULL;		
			exit(errno);
		}
		last_status = check_if_buildin(token, env);
	}
	else
	{
		last_status = create_child(token, ex, env, count);
	}
	return(last_status);
}

// void copy_dup(t_ex *ex, int i)
// {
//     static int saved_stdin = -1;
//     static int saved_stdout = -1;

//     if (i == 1)
//     {
//         // Save the original file descriptors
//         saved_stdin = dup(STDIN_FILENO);
//         saved_stdout = dup(STDOUT_FILENO);

//         // Duplicate the new file descriptors
//         if (ex->fd[0] != -1)
//             dup2(ex->fd[0], STDIN_FILENO);
//         if (ex->fd[1] != -1)
//             dup2(ex->fd[1], STDOUT_FILENO);
//     }
//     else if (i == 2)
//     {
//         // Restore the original file descriptors
//         if (saved_stdin != -1)
//         {
//             dup2(saved_stdin, STDIN_FILENO);
//             close(saved_stdin);
//             saved_stdin = -1;
//         }
//         if (saved_stdout != -1)
//         {
//             dup2(saved_stdout, STDOUT_FILENO);
//             close(saved_stdout);
//             saved_stdout = -1;
//         }
//     }
// }
void	main_execute(t_token *token, t_env *env, t_ex *ex) 
{
	int i;
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
		// copy_dup(ex, 1);
		last_status = execute(token, env, ex, i);
		// copy_dup(ex, 2);
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
	// printf("Exit status is: %i\n", ex->exit_status);
}