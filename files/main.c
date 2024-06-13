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
void env_buildin(char *line, t_minishell *man)
{
	node_t *temp;

	temp = man->head;
	if (ft_strncmp(line, "env", 3) == 0)
	{
		while(temp)
		{
			printf("%s\n", temp->data);
			temp = temp->next;
		}
	}
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
	env_buildin(line, man);
}

void loop(t_minishell *man)
{
	char *line;

	fill_nodes_env(man);
	while(1)
	{
		line = readline("tomzijnmondheeftnognooitfrisgeroken> ");
		main_pars(line, man);
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

int main(int argc, char **argv, char **env)
{
    t_minishell *man;
	t_token **token;

	man = ft_calloc(1, sizeof(t_minishell));
	man->env = env;
	if(!man)
		exit(1);
	// tokenizer(argc, argv, token);
    loop(man);
}
//save environment in a linked list, that way you can easily access it and add enviromental variables to it