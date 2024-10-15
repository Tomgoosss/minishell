#include "minishell.h"

void	error_lines(char *arg, int i)
{
	if (i == 1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (i == 2)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (i == 3)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd("not enough arguments: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (i == 4)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": too many arguments\n", 2);
	}
	else if (i == 5)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": Is a directory\n", 2);
	}
	else if (i == 6)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
}