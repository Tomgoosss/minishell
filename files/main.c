#include "minishell.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int g_exit_status = 0;

void	handle_sigint(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
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
	t_token	*token = NULL;
	t_ex	*ex;
	int		exitcode;

	ex = ft_calloc(1, sizeof(t_ex));
	if (!ex)
		exit(errno);
	fill_nodes_env(var);
	exitcode = 0;
	while (1)
	{
		signal(SIGINT, handle_sigint);
		line = readline("minishell> ");
		if (!line) // Handle ctrl-D (EOF)
			break;
		if (g_exit_status == 130)
		{
			ex->exit_status = 130;
			g_exit_status = 0;
		}
		if (unclosed_quote(line, ex))
		{
			free(line);
			continue;
		}
		sort_export(var);
		if ((exitcode = check_exit(ft_split(line, ' '))) != 0)
		{
			ft_putstr_fd("exit\n", 2);
			rl_clear_history();
			free(line);
			free(ex);
			exit(exitcode);
		}
		token = main_pars(line, var, ex);
		if (!token)
		{
			free(line);
			continue;
		}
		signal(SIGINT, SIG_IGN);
		main_execute(token, var, ex);
		add_history(line);
		free_token(token);
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