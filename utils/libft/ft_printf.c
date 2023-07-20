/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 20:13:02 by jyim              #+#    #+#             */
/*   Updated: 2022/11/20 16:21:55 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_conver(char c, va_list args)
{
	int	count;

	count = 0;
	if (c == 'c')
		count = ft_putchar(va_arg(args, int));
	if (c == 'i' || c == 'd')
		count = ft_putnbr_dec(va_arg(args, int));
	if (c == 'p')
		count = ft_putptr(va_arg(args, unsigned long));
	if (c == 's')
		count = ft_putstr(va_arg(args, char *));
	if (c == 'u')
		count = ft_putnbr_uns_dec(va_arg(args, unsigned int));
	if (c == 'x' || c == 'X')
		count = ft_putnbr_hex(va_arg(args, unsigned int), c);
	if (c == '%')
		count = ft_putchar('%');
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(args, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			count += check_conver(str[i + 1], args);
			i += 2;
		}
		else
			count += ft_putchar(str[i++]);
	}
	return (count);
}
