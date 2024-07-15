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

void	loop(t_env *var)
{
	char	*line;

	fill_nodes_env(var);
	sort_export(var);
	while (1)
	{
		line = readline("minishell> ");
		sort_export(var);
		// main_pars(line, var);
		main_execution(var);
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
