/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomgoossens <tomgoossens@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:33:42 by tgoossen          #+#    #+#             */
/*   Updated: 2024/02/02 23:04:15 by tomgoossens      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free(char **line)
{
	free(*line);
	*line = NULL;
	return (NULL);
}

char	*readtxt(int fd, char *buffer)
{
	int		bytes_read;
	char	*tempbuffer;

	tempbuffer = malloc(BUFFER_SIZE + 1);
	bytes_read = 1;
	while (bytes_read > 0 && ft_nlcheck(buffer) == -1)
	{
		bytes_read = read(fd, tempbuffer, BUFFER_SIZE);
		if (bytes_read > 0)
		{
			tempbuffer[bytes_read] = '\0';
			buffer = ft_strjoin2(buffer, tempbuffer);
			if (!buffer)
				return (ft_free(&tempbuffer));
		}
	}
	ft_free(&tempbuffer);
	if (bytes_read < 0)
		return (ft_free(&buffer));
	return (buffer);
}

char	*read_first_line(char *tempbuffer)
{
	int		i;
	int		o;
	char	*line;

	i = 0;
	o = 0;
	while (tempbuffer[i] && tempbuffer[i] != '\n')
		i++;
	if (tempbuffer[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	while (o < i)
	{
		line[o] = tempbuffer[o];
		o++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_rem(char *buffer)
{
	int		i;
	int		j;
	char	*tempbuffer;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n' )
		i++;
	if (buffer[i] == '\0')
		return (ft_free(&buffer));
	tempbuffer = malloc(ft_strlen(buffer) - i + 1);
	if (!tempbuffer)
		return (ft_free(&buffer));
	while (buffer[i])
		tempbuffer[j++] = buffer[i++];
	ft_free(&buffer);
	tempbuffer[j] = '\0';
	return (tempbuffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer = 0;
	char		*tempbuffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = readtxt(fd, buffer);
	if (buffer == NULL)
		return (NULL);
	tempbuffer = read_first_line(buffer);
	if (!tempbuffer)
		return (ft_free(&buffer));
	buffer = get_rem(buffer);
	return (tempbuffer);
}

// int main()
// {
//     int i = 0;
//     int fd = open("get_next_line.c", O_RDONLY);
//     char *str;

//     while (i < 40)
//     {
//         str = get_next_line(fd);
//         if (str == NULL)
//         {
//             // Handle read error
//             break;
//         }
//         printf("%d = %s\n", i, str);
//         free(str);
//         i++;
//     }
//     close(fd);
//     return 0;
// }