int	size_no_whitespace(char *line)
{
	int	i;
	int	size;
	int	reset;

	i = 0;
	size = 0;
	reset = 0;
	while (line[i] != '\0')
	{
		if (line[i] == "'" || line[i] == 34)
		{
			size += closing_quote(line, i, line[i], 0) - i - 1;
			i = closing_quote(line, i, line[i], 0);
		}
		if (!is_space(line[i]))
		{
			reset = 1;
			size++;
		}
		else if (reset == 1)
		{
			reset = 0;
			size++;
		}
		i++;
	}
	return (size);
}

char	*ft_stlcat(char *dst, const char *src, size_t n)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	dstlen = 0;
	srclen = 0;
	i = 0;
	while (dst[dstlen] && dstlen < n - 1)
		dstlen++;
	while (src[srclen])
		srclen++;
	if (dstlen >= n)
		return NULL;
	while (src[i] && (dstlen + i) < (n - 1))
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (dst);
}
char *remove_white_spaces(char *line)
{
    int i = 0;
    int j = 0;
    char *new_line;

    new_line = malloc(sizeof(char) * (size_no_whitespace(line) + 1));
    if (!new_line)
        return NULL;
    new_line[0] = '\0'; 
    while (line[i])
    {
        if (line[i] == '\'' || line[i] == '\"')
        {
            int quote_len = closing_quote(line, i + 1, line[i], 0);
            if (quote_len == 0)
                return (free(new_line), 0);
            ft_stlcat(new_line, line + i, quote_len + 1);
            j = quote_len;
            i = quote_len;
        }
        else if (!is_space(line[i]))
            new_line[j++] = line[i++];
        else
        {
            if (j > 0 && !is_space(line[i + 1]))
                new_line[j++] = ' ';
            i++;
        }
    }
    new_line[j] = '\0';
    return new_line;
}