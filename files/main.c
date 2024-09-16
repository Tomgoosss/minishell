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
	t_token	*token = NULL; // Initialize token to NULL
	t_ex	*ex;
	int		exitcode;

	ex = ft_calloc(1, sizeof(t_ex));
	if (!ex)
		exit(errno);
	fill_nodes_env(var);
	exitcode = 0;
	int i = 0;
	while (1)
	{
		line = readline("minishell> ");
		if (!line) // Check if line is NULL
			break; // Exit loop if readline fails
		add_history(line); // Add line to history
		token = main_pars(line, var);
		free(line); // Free line after processing
		main_execute(token, ex, var);
		free_token(token);
		if (i == 2)
			break;
		i++;
	}
	free(ex); // Free ex before exiting the loop
	rl_clear_history();
}


int	main(int argc, char **argv, char **environment)
{
	t_env	*var;

	argc = 0;
	argv = NULL;
	var = ft_calloc(1, sizeof(t_env));
	if (!var) // Check for malloc failure
		exit(1);
	var->env = environment; // Ensure environment is properly assigned
	loop(var);
	free_env(var);
	return (0);
}