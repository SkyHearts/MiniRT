/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:32:20 by jyim              #+#    #+#             */
/*   Updated: 2022/11/20 16:21:49 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_ptrlen(unsigned long nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 16;
		count++;
	}
	return (count);
}

void	ft_writeptr(unsigned long nb)
{
	char	*set;

	set = "0123456789abcdef";
	if (nb > 15)
	{
		ft_writeptr(nb / 16);
		ft_writeptr(nb % 16);
	}
	else
		ft_putchar(set[nb]);
}

int	ft_putptr(unsigned long nb)
{
	int	count;

	count = 0;
	count += ft_putstr("0x");
	count += get_ptrlen(nb);
	ft_writeptr(nb);
	return (count);
}

/* #include <stdio.h>

int main(void)
{
	char s[] = "123";
	printf("\nft_putptr = %i", ft_putptr(s));
	printf("\n");
	printf("\n___putptr = %i", printf("%p", s));
} */