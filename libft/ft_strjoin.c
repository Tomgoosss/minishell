/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:01:47 by tgoossen          #+#    #+#             */
/*   Updated: 2023/10/24 16:17:50 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		y;
	int		s1s2count;
	char	*copy;

	s1s2count = ft_strlen(s1) + ft_strlen(s2);
	copy = (char *)malloc((s1s2count + 1) * sizeof(char));
	i = 0;
	if (copy == 0)
		return (NULL);
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	y = 0;
	while (s2[y])
	{
		copy[i] = s2[y];
		y++;
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

// int main(void)
// {
// 	const char *s1 = "dit is";
// 	const char *s2 = "mijn zin";

// 	printf ("%s\n", ft_strjoin(s1, s2));
// }