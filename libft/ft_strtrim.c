/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:36:50 by tgoossen          #+#    #+#             */
/*   Updated: 2023/10/24 15:04:48 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ctester(char const *set, char s1)
{
	while (*set)
	{
		if (*set == s1)
			return (1);
		else
			set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*ret;

	i = 0;
	j = 0;
	while (ctester(set, s1[j]) == 1)
		j++;
	while (s1[i] != '\0')
		i++;
	i = i - 1;
	while (ctester(set, s1[i]) == 1)
		i--;
	i = i + 1;
	ret = ft_substr(s1, j, i - j);
	if (ret == 0)
		return (NULL);
	ret[i] = '\0';
	return (ret);
}

// int main(void)
// {
// 	const char *s1 = "pfpfdittfffpfpf";
// 	const char *set = "pf";

// 	printf("%s\n", ft_strtrim(s1, set));

// }