/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:23:02 by tgoossen          #+#    #+#             */
/*   Updated: 2023/10/24 16:19:02 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*nstring;
	int		i;

	i = 0;
	nstring = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (nstring == 0)
		return (0);
	while (s[i])
	{
		nstring[i] = f(i, s[i]);
		i++;
	}
	nstring[i] = '\0';
	return (nstring);
}
