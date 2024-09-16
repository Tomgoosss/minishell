#include "minishell.h"

void	error_msg(char *line, int i)
{
	ft_putstr_fd("bash: ", 2);
	if (i == 1)
		ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("\n", 2);
}

void	loop(t_env *var)
{
	char	*line;
	t_token	*token;
	t_ex *ex;
	int		exitcode;

	ex = ft_calloc(1, sizeof(t_ex));
	if(!ex)
		exit(errno);
	fill_nodes_env(var);
	exitcode = 0;
	while (1)
	{
		line = readline("minishell> ");
		sort_export(var);
		// if ((exitcode = check_exit(ft_split(line, ' '))) != 0)
		// {
		// 	ft_putstr_fd("exit\n", 2);
		// 	rl_clear_history();
		// 	exit(exitcode);
		// }
		if (line)
			token = main_pars(line, var);
		if (!token)
			return (free(line));
		else
			main_execute(token, var, ex);	
		// if (!token)
		// 	return (free(line));
		// else
		// 	main_execute(token, var);
		add_history(line);
		free(line);
	}
}

int	main(int argc, char **argv, char **environment)
{
	t_env	*var;

	argc = 0;
	argv = NULL;
	var = ft_calloc(1, sizeof(t_env));
	var->env = environment;
	if (!var)
		exit(1);
	loop(var);
}
