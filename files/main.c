#include "minishell.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void	handle_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\nminishell> ", 2); // Display a new prompt on ctrl-C
}

void	handle_sigquit(int sig)
{
	(void)sig;
	// Do nothing, just return to keep the prompt intact
}

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
	while (1)
	{
		line = readline("minishell> ");
		if (!line) // Handle ctrl-D (EOF)
		{
			ft_putstr_fd("exit\n", 2);
			// free(line);
			// free_env(var);
			// free_token(token);
			break;
		}
		sort_export(var);
		if ((exitcode = check_exit(ft_split(line, ' '))) != 0)
		{
			ft_putstr_fd("exit\n", 2);
			rl_clear_history();
			exit(exitcode);
		}
		if (line)
		{
			token = main_pars(line, var);
			if (!token)
			{
				free(line);
				continue; // Skip to the next iteration if token is NULL
			}
			main_execute(token, var, ex);
			buildins_par(token, var);	
			add_history(line);
			free_token(token);
		}
		free(line);
	}
	free(ex); // Free ex before exiting the loop
	rl_clear_history();
}

int	main(int argc, char **argv, char **environment)
{
	t_env	*var;

	signal(SIGINT, handle_sigint);  // Handle ctrl-C
	signal(SIGQUIT, SIG_IGN);        // Ignore ctrl-\

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