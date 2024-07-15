#include "../minishell.h"

void	env_print(char *line, t_env *var)
{
	node_t	*temp;

	temp = var->head_env;
	if (ft_strncmp(line, "env", 3) == 0)
	{
		while (temp)
		{
			printf("%s\n", temp->data);
			temp = temp->next;
		}
	}
}

// this recreates the export function
void	export(char *line, t_env *var)
{
	node_t	*temp;
	char	*linetemp;

	temp = var->head_exp;
	// remove_all_white_spaces(line);
	if (ft_strncmp(line, "export", 7) == 0) // && ft_strlen(linetemp) == 6)
	{
		while (temp)
		{
			printf("declare -x %s\n", temp->data);
			temp = temp->next;
		}
	}
	// else if()
	// 	env_or_exp(line, var);
	// free(linetemp);
}

void	pwd_buildin(char *line, t_env *var)
{
	char	cwd[4069];

	if (strncmp(line, "pwd", 3) == 0)
		printf("%s\n", getcwd(cwd, sizeof(cwd)));
}

void	buildins(char *line, t_env *var)
{
	pwd_buildin(line, var);
	env_print(line, var);
	export(line, var);
}