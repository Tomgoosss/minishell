#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (1);
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

static int	wordleng_mod(char const *s, char c, char x, int j)
{
	int	i;

	i = 0;
	while (s[j] != c && s[j] != x && s[j] != '\0')
	{
		i++;
		j++;
	}
	return (i);
}
static int stringcounter_mod(char const *s, char c, char x)
{
    int str;
    int t;

    t = 0;
    str = 0;
    while (*s != '\0')
    {
        if (*s == x)
        {
            str++;
            t = 0;
        }
        else if (*s != c && t == 0)
        {
            str++;
            t = 1;
        }
        else if (*s == c)
        {
            t = 0;
        }
        s++;
    }
    return (str);
}
static void	free_str_array(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
}
char	*ft_substr_mod(char const *s, unsigned int start, size_t len)
{
	char	*countm;
	size_t	lengs;
	size_t	i;

	lengs = ft_strlen(s);
	i = 0;
	if (start >= lengs || len == 0)
		return (ft_strdup(""));
	if (start + len > lengs)
		len = lengs - start;
	countm = (char *)malloc((len + 1) * sizeof(char));
	if (countm == 0)
		return (NULL);
	while (i < len)
	{
		countm[i] = s[i + start];
		i++;
	}
	countm[i] = '\0';
	return (countm);
}

void print_str_array(char **str)
{
    if (str == NULL)
    {
        printf("Array is NULL\n");
        return;
    }

    for (int i = 0; str[i] != NULL; i++)
    {
        printf("[%d]: '%s'\n", i, str[i]);
    }
    printf("End of array\n");
}
int is_delimiter(const char *s)
{
    return (*s == '<' || *s == '>' || *s == '|');
}

int get_token_length(const char *s)
{
    int len;
    
    if ((*s == '<' && *(s + 1) == '<') || (*s == '>' && *(s + 1) == '>'))
        return 2;
    if (is_delimiter(s))
        return 1;
    len = 0;
    while (s[len] && !is_delimiter(s + len) && s[len] != ' ')
        len++;
    return len;
}

char **ft_split_mod(char const *s, char c)
{
    int strings = 0;
    int i = 0;
    int len = 0;
    char **str;
    const char *og_string = s;

    while (*s)
    {
        if (*s != c)
        {
            len = get_token_length(s);
            strings++;
            s += len;
        }
        else
            s++;
    }
    str = malloc((strings + 1) * sizeof(char *));
    if (str == NULL)
        return (NULL);
    s = og_string;
    i = 0;
    while (i < strings)
    {
        while (*s == c)
            s++;
        len = get_token_length(s);
        str[i] = ft_substr(s, 0, len);
        if (str[i] == NULL)
            return (free_str_array(str, i), NULL);
        s += len;
        i++;
    }
    str[i] = NULL;
    // print_str_array(str);
    return (str);
}