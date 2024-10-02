#include <stdio.h>

void echo(char **command)
{
	int i;

    if(ft_strncmp(command[1], "-n", 2) == 0)
    {
       //print statement infront of minishell
	   return 0;
    }
	i = 1;
    while(command[i])
	{
		if(command[i + 1])
			printf("%s ", command[i]);
		else
			printf("%s", command[i]);
		i++;
	}
	printf("\n");
	return 0;
}

