#include "minishell.h"

int	skip_whitespaces(char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\r'
		|| line[i] == '\n' || line[i] == '\v' || line[i] == '\f')
		i++;
	return (i);
}

// needs to be changed
// check if the variable is valid. there should be no whitespace in the variable name
// aswell as there should be no whitespace in the value of the variable
int	check_env_variable(char *line)
{
 
	if(skip_whitespaces(line, 0) == ft_strlen(line))
		return (0);
	printf("line %c\n", line[0]);
	printf("len%i\n", ft_strlen(line));
	return 1;
}

void make_2d_env(t_env *env)
{
	int i;
	node_t *temp;

	i = count_nodes(env->head_env);
	env->env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env->env)
		return ;
	temp = env->head_env;
	i = 0;
	while (temp)
	{
		env->env[i] = temp->data;
		temp = temp->next;
		i++;
	}
	env->env[i] = NULL;
}
