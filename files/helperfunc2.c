#include "../minishell.h"

// count leng of char withoud white spaces
int count_len_str(char *line)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while(line[i])
	{
		if(line[i] == ' ' || line[i] == '\t' || line[i] == '\f' || line[i] == '\n' || line[i] == '\r' || line[i] == '\v')
			i++;
		else
		{
			c++;
			i++;
		}
	}
	return(c);
}
// wrong type of remove white spaces but now already in use for a function so keep it in
char *remove_all_white_spaces(char *line)
{
	int i;
	int l;
	char *templine;

	i = 0;
	l = 0;
	if(count_len_str(line) == 0)
		return(NULL);
	templine = malloc(count_len_str(line) + 1);
	if(!templine)
		return(NULL);
	while(line[i])
	{
		if(line[i] == ' ' || line[i] == '\t' || line[i] == '\f' || line[i] == '\n' || line[i] == '\r' || line[i] == '\v')
			i++;
		else
			templine[l++] = line[i++];
	}
	templine[l] = '\0';
	return(templine);
}
