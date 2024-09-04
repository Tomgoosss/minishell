#include "minishell.h"

int	env_buildin(char **command, t_env *var)
{
	node_t	*temp;

	temp = var->head_env;
	while (temp)
	{
		printf("%s\n", temp->data);
		temp = temp->next;
	}
	return(1);
}

int	pwd_buildin()
{
	char	cwd[4069];
	int		temp;

	printf("%s\n", getcwd(cwd, sizeof(cwd)));
	return(1);
}
