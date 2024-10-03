#include <stdio.h>

int echo(char **command)
{
	int i = 1;
	int newline = 1;

	if (command[i] && ft_strncmp(command[i], "-n", 2) == 0)
	{
		newline = 0;
		i++;
	}

	while (command[i])
	{
		printf("%s", command[i]);
		if (command[i + 1])
			printf(" ");
		i++;
	}

	if (newline)
		printf("\n");

	return 1;
}

