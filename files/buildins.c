#include "../minishell.h"

void	env_buildin(char *line, t_env *var)
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
		temp = var->head_env;
	}
}

void	exp_buildin(char *line, t_env *var)
{
	node_t	*temp;

	temp = var->head_exp;
	if (ft_strncmp(line, "export", 7) == 0)
	{
		sort_export(var);
		while (temp)
		{
			printf("%s\n", temp->data);
			temp = temp->next;
		}
		temp = var->head_env;
	}
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
	env_buildin(line, var);
	exp_buildin(line, var);
}