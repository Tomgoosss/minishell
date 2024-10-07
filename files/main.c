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

int	unclosed_quote(char *line, t_ex *ex)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			i = closing_quote(line, i, line[i], 1);
		if (i == -1)
		{
			printf("syntax error: unexpected EOF while looking for matching `%c\'\n", line[j]);
			ex->exit_status = 2;
			return (1);
		}
		i++;
	}
	return (0);
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
			break;
		if (unclosed_quote(line, ex))
			continue;
		sort_export(var);
		if ((exitcode = check_exit(ft_split(line, ' '))) != 0)
		{
			ft_putstr_fd("exit\n", 2);
			rl_clear_history();
			exit(exitcode);
		}
		if (line)
		{
			token = main_pars(line, var, ex);
			if (!token)
			{
				free(line);
				continue; // Skip to the next iteration if token is NULL
			}
			main_execute(token, var, ex);
			add_history(line);
			free_token(token);
		}
		free(line);
	}
	free(ex); 
	rl_clear_history();
}

int	main(int argc, char **argv, char **environment)
{
	t_env	*var;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);

	argc = 0;
	argv = NULL;
	var = ft_calloc(1, sizeof(t_env));
	if (!var)
		exit(1);
	var->env = environment;
	loop(var);
	free_env(var);
	return (0);
}