/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:40:02 by tgoossen          #+#    #+#             */
/*   Updated: 2023/11/09 16:24:34 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	numpick(const char *var, va_list args)
{
	if (*var == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (*var == 's')
		return (putstr(va_arg(args, const char *)));
	else if (*var == 'p')
		return (ft_hexpointer(va_arg(args, void *)));
	else if (*var == 'd' || *var == 'i')
		return (allbase(va_arg(args, int), "0123456789"));
	else if (*var == 'u')
		return (allbase(va_arg(args, unsigned int), "0123456789"));
	else if (*var == 'x')
		return (allbase(va_arg(args, unsigned int), "0123456789abcdef"));
	else if (*var == 'X')
		return (allbase(va_arg(args, unsigned int), "0123456789ABCDEF"));
	else if (*var == '%')
		ft_putchar('%');
	return (1);
}

int	valid(char s)
{
	int		i;
	char	*c;

	c = "cspdiuxX%";
	i = 0;
	while (c[i])
	{
		if (c[i] == s)
			return (1);
		i++;
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		i;

	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && valid(format[i + 1]))
		{
			count += numpick(&format[i + 1], args);
			i += 2;
		}
		else
		{
			count += write(1, &format[i], 1);
			i++;
		}
	}
	va_end(args);
	return (count);
}

// int main()
// {
//     // int test = 'i';
// 	int test =  16;
//     printf("%i\n", ft_printf("%p\n", test));
//     printf("%i\n", printf("%p\n", test));
// }

// int	main(void)
// {
// 	char			char1 = 'q', char2 = '\t', char3 = 'string';
// 	char			str1[] = "Hello", str2[] = "", *str3 = NULL;
// 	int				int1 = 16, int2 = -2147483648, int3 = 2147483650;
// 	unsigned int	uint1 = 145, uint2 = -50, uint3 = 4294967296;
// 	int				hu1 = 16, hu2 = -5000, hu3 = 4294967296;
// 	int				hl1 = 9946843, hl2 = -2147483648, hl3 = 2147483650;
// 	int				ptr1 = 40, ptr2 = NULL, ptr3 = 'c', ptr4 = -1;
//  printf("Chars %%: %c, %c, %c\n", char1, char2, char3);
// 	ft_printf("Chars %%: %c, %c, %c\n\n", char1, char2, char3);
// 	printf("Strings: %s, %s, %s\n", str1, str2, str3);
// 	ft_printf("Strings: %s, %s, %s\n\n", str1, str2, str3);
// 	printf("Ints: %d, %i, %d\n", int1, int2, int3);
// 	ft_printf("Ints: %d, %i, %d\n\n", int1, int2, int3);
// 	printf("Unsigned: %u, %u, %u\n", uint1, uint2, uint3);
// 	ft_printf("Unsigned: %u, %u, %u\n\n", uint1, uint2, uint3);
// 	printf("Hex Upper: %X, %X, %X\n", hu1, hu2, hu3);
// 	ft_printf("Hex Upper: %X, %X, %X\n\n", hu1, hu2, hu3);
// 	printf("Hex Lower: %x, %x, %x\n", hl1, hl2, hl3);
// 	ft_printf("Hex Lower: %x, %x, %x\n\n", hl1, hl2, hl3);
// 	printf("ptrs: %p, %p, %p, %p \n", ptr1, ptr2, ptr3, ptr4);
// 	ft_printf("ptrs: %p, %p, %p, %p \n\n", ptr1, ptr2, ptr3, ptr4);
// 	printf("mix: %% %c %s %d %x\n", char1, str1, int1, hl1);
// 	ft_printf("mix: %% %c %s %d %x\n\n", char1, str1, int1, hl1);
// 	int		i;
// 	int		j;
// 	char	string1[] = "AB%sDEF";
// 	char	*string2 = "123456";
// 	ft_printf("%s", "return value check:\n");
// 	i = ft_printf(string1, string2);
// 	printf("\n%d\n", i);
// 	j = printf(string1, string2);
// 	printf("\n%d", j);
// 	if (i != j)
// 	{
// 		printf("\n\nThe value is incorrect!\ni = %d\nj = %d\n\n", i, j);
// 	}
// 	return (0);
// }
