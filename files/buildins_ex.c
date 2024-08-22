#include "../minishell.h"

int check_if_buildin(t_token *token, t_env *var)
{
	// if(strncmp(token->command[0], "echo", 4))
	// 	// echo
	// if(strncmp(token->command[0], "cd", 2))
	// 	// cd
	if(strncmp(token->command[0], "pwd", 3))
		return(pwd_buildin());
	if(strncmp(token->command[0], "export", 4))
		return(exp_buildin(token->command, var));
	// if(strncmp(token->command[0], "unset", 5))
	// 	// unset
	if(strncmp(token->command[0], "env", 3))
		return(env_buildin(token->command, var));
	// if(strncmp(token->command[0], "exit", 4))
	// 	// exit
	return(0);
}