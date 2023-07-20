/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:36:10 by jyim              #+#    #+#             */
/*   Updated: 2022/11/20 19:06:53 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_hex_len(unsigned int nb)
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

void	ft_lower(unsigned int nb)
{
	char	*lower;

	lower = "0123456789abcdef";
	if (nb > 15)
	{
		ft_lower(nb / 16);
		ft_lower(nb % 16);
	}
	else
		ft_putchar(lower[nb]);
}

void	ft_upper(unsigned int nb)
{
	char	*upper;

	upper = "0123456789ABCDEF";
	if (nb > 15)
	{
		ft_upper(nb / 16);
		ft_upper(nb % 16);
	}
	else
		ft_putchar(upper[nb]);
}

int	ft_putnbr_hex(unsigned int nb, char c)
{
	int	count;

	count = get_hex_len(nb);
	if (c == 'x')
		ft_lower(nb);
	else
		ft_upper(nb);
	return (count);
}

/* int main(void)
{
	static char asd[] = "asdasdasdasd";
	unsigned int nb = 20154;
	//ft_putnbr_hex(nb, 'X');
	//printf("\n%d",ft_putnbr_hex(nb, 'X'));
} */