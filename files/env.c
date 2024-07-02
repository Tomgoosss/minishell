#include "../minishell.h"

// needs to be changed
// check if the variable is valid. there should be no whitespace in the variable name
// aswell as there should be no whitespace in the value of the variable
int	check_env_variable(char *line)
{
	int	i;

	i = 0; 
	if(skip_whitespaces(line, 0) == ft_strlen(line))
		return (0);
	printf("line %c\n", line[0]);
	printf("len%i\n", ft_strlen(line));

}

void	env_variable(char *line, t_env *var)
{
	int		i;
	char	*env_variable;
	node_t	*temp;

	temp = var->head_env;
	i = 0;
	if (!ft_strncmp(line, "export", 6))
	{
		i = skip_whitespaces(line, 6);
		if(i == 6)
			{
				// execute export
				return ;
			}
		env_variable = ft_substr(line, i, ft_strlen(line) - i);
		if (check_env_variable(env_variable) == 0)
			return ;
		add_node(&temp, make_node(env_variable));
	}
	return ;
}

int	skip_whitespaces(char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\r'
		|| line[i] == '\n' || line[i] == '\v' || line[i] == '\f')
		i++;
	return (i);
}