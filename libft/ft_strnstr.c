/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomgoossens <tomgoossens@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:22:32 by tgoossen          #+#    #+#             */
/*   Updated: 2024/02/02 17:01:03 by tomgoossens      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	lenglittle;

	lenglittle = ft_strlen(little);
	if (lenglittle == 0)
		return ((char *)big);
	while (*big && len >= lenglittle)
	{
		if (*big == *little && ft_strncmp(big, little, lenglittle) == 0)
		{
			return ((char *)big);
			little++;
		}
		big++;
		len--;
	}
	return (0);
}

// int main(void)
// {
// 	const char littlee[50] = "need";
// 	const char bigg[50] = "i need to find this please";
// 	printf("%s\n", ft_strnstr(bigg, littlee, 20));
// 	// printf("%s", strnstr(bigg, littlee, 20));
// }