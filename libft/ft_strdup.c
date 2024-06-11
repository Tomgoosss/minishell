/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:06:48 by tgoossen          #+#    #+#             */
/*   Updated: 2023/10/24 14:06:10 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*fake;
	size_t	lengs;
	size_t	i;

	lengs = ft_strlen(s);
	fake = (char *)malloc(((lengs) + 1) * sizeof (char));
	i = 0;
	if (fake == NULL)
		return (NULL);
	while (i < lengs)
	{
		fake[i] = s[i];
		i++;
	}
	fake[i] = '\0';
	return (fake);
}

// int main(void)
// {
// 	const char original[] = "copy this";
// 	char *fake = ft_strdup(original); 
// 	ft_strdup(original);
// 	printf("%s", fake);
// }