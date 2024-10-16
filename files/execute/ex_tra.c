#include "minishell.h"

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


int find_slash(t_token *token)
{
	struct stat file_stat;
	int i;

	i = 0;
	if(token->command == NULL || token->command[0] == NULL)
		return 0;
	if (access(token->command[0], X_OK) == 0)
	{
		if (stat(token->command[0], &file_stat) == 0)
		{
			if (S_ISREG(file_stat.st_mode))
				return (0);
		}
	}
	while (token->command[0][i] != '\0')
	{
		if (token->command[0][i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int check_if_dir(t_token *token)
{
	DIR *dir;
	
	dir = opendir(token->command[0]);
	// printf("DIR pointer: %p\n", (void *)dir);
	if (dir)
	{
		closedir(dir);
		error_lines(token->command[0], 5);
		return 126;
	}
	else if (errno == ENOENT)
	{
		error_lines(token->command[0], 2);
		return 127;
	}
	else if (errno == EACCES)
	{
		error_lines(token->command[0], 6);
		return 126;
	}
	else
	{
		error_lines(token->command[0], 2);
		return 1; 
	}
}