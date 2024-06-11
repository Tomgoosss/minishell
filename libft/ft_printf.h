/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:38:10 by tgoossen          #+#    #+#             */
/*   Updated: 2023/11/09 16:27:04 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>

int		ft_printf(const char *var, ...);
int		ft_hexpointer(void *str);
int		ft_putchar(char c);
int		ft_strlen(const char *s);
int		putstr(const char *c);
int		allbase(long nb, char *base);

#endif