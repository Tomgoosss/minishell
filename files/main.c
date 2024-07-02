#include "../minishell.h"

void	error_msg(char *line, int i)
{
	ft_putstr_fd("bash: ", 2);
	if (i == 1)
		ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("\n", 2);
}

int	check_exit(char *line)
{
	if (line == NULL)
		return (1);
	if (ft_strncmp(line, "exit", 4) == 0)
		return (1);
	return (0);
}
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

void	loop(t_env *var)
{
	char	*line;

	fill_nodes_env(var);
	while (1)
	{
		line = readline("minishell> ");
		line = remove_white_spaces(line);
		printf("line: %s\n", line);
		sort_export(var);
		main_pars(line, var);
		if (check_exit(line) != 0)
		{
			ft_putstr_fd("exit\n", 2);
			rl_clear_history();
			break ;
		}
		add_history(line);
		buildins(line, var);
	}
}

int	main(int argc, char **argv, char **environment)
{
	t_env	*var;

	var = ft_calloc(1, sizeof(t_env));
	var->env = environment;
	if (!var)
		exit(1);
	loop(var);
}
// save environment in a linked list,
// that way you can easily access it and add enviromental variables to it

