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
        printf("[%d]: %s\n", i, str[i]);
    }
    printf("End of array\n");
}
int is_delimiter(const char *s)
{
    return (*s == '<' || *s == '>' || *s == '|');
}

int is_quote(char c)
{
    return (c == '\'' || c == '"');
}

int get_token_length(const char *s, int *quote_len)
{
    int len = 0;
    char quote_char;
    
    *quote_len = 0;
    if ((*s == '<' && *(s + 1) == '<') || (*s == '>' && *(s + 1) == '>'))
        return 2;
    if (is_delimiter(s))
        return 1;
    while (s[len])
    {
        if (is_quote(s[len]))
        {
            quote_char = s[len];
            len++;
            while (s[len] && s[len] != quote_char)
                len++;
            if (s[len] == quote_char)
            {
                len++;
                *quote_len += 2;
            }
            else
                *quote_len += 1;
        }
        else if (is_delimiter(s + len) || s[len] == ' ')
            break;
        else
            len++;
    }
    return len;
}

char *ft_strndup(const char *s, size_t n)
{
    char *result = malloc(n + 1);
    if (result == NULL)
        return NULL;
    strncpy(result, s, n);
    result[n] = '\0';
    return result;
}

char **ft_split_mod(char const *s, char c)
{
    int strings = 0;
    int i = 0;
    int len = 0;
    int quote_len = 0;
    char **str;
    const char *og_string = s;

    if (s == NULL)
        return (NULL);
    while (*s)
    {
        if (*s != c)
        {
            len = get_token_length(s, &quote_len);
            strings++;
            s += len;
        }
        else
            s++;
    }
    if (!(str = malloc((strings + 1) * sizeof(char *))))
        return (NULL);
    s = og_string;
    i = 0;
    while (i < strings)
    {
        while (*s == c)
            s++;
        len = get_token_length(s, &quote_len);
        if (!(str[i] = malloc(len - quote_len + 1)))
        {
            free_str_array(str, i);
            return (NULL);
        }
        int j = 0;
        int k = 0;
        while (k < len)
        {
            if (!is_quote(s[k]))
            {
                str[i][j] = s[k];
                j++;
            }
            k++;
        }
        str[i][j] = '\0';
        s += len;
        i++;
    }
    str[i] = NULL;
    return (str);
}
