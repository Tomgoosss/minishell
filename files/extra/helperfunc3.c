#include "minishell.h"

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
    char quote_char = 0;
    
    *quote_len = 0;
    if ((*s == '<' && *(s + 1) == '<') || (*s == '>' && *(s + 1) == '>'))
        return 2;
    if (is_delimiter(s))
        return 1;
    while (s[len])
    {
        if (is_quote(s[len]) && quote_char == 0)
        {
            quote_char = s[len];
            (*quote_len)++;
        }
        else if (s[len] == quote_char)
        {
            quote_char = 0;
            (*quote_len)++;
        }
        else if (quote_char == 0 && (is_delimiter(s + len) || s[len] == ' '))
            break;
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