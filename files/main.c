#include "../minishell.h"


void error_msg(char *line, int i)
{
	ft_putstr_fd("bash: ", 2);
	if(i == 1)
		ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("\n", 2);
}

int check_exit(char *line)
{
	if(line == NULL)
		return(1);
	if(ft_strncmp(line, "exit", 4) == 0)
		return(1);
	return(0);
}
void cd_buildin(cd, path, man)
{
	if(strncmp(cd, "cd", 3))
}

void pwd_buildin(char *line, t_minishell *man)
{
	char cwd[4069];
	if(strncmp(line, "pwd", 3) == 0)
		printf("%s\n", getcwd(cwd, sizeof(cwd)));
}

void buildins(char *line, t_minishell *man)
{
	pwd_buildin(line, man);
	cd_buildin(line, path, man);
}

void loop(t_minishell *man)
{
	char *line;
	// node_t *node;

	while(1)
	{
		line = readline("minishell> ");
		if(check_exit(line) != 0)
		{
			ft_putstr_fd("exit\n", 2);
			rl_clear_history();
			break;
		}
		add_history(line);
		buildins(line, man);
		
	}
}

int main()
{
    t_minishell *man;

	man = ft_calloc(1, sizeof(t_minishell));
	if(!man)
		exit(1);
    loop(man);
}