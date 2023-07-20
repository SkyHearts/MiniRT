/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_uns_dec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:36:10 by jyim              #+#    #+#             */
/*   Updated: 2022/11/20 16:21:52 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_unslen(unsigned int nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

int	ft_putnbr_uns_dec(unsigned int nb)
{
	int	count;

	count = get_unslen(nb);
	if (nb > 9)
	{
		ft_putnbr_uns_dec(nb / 10);
		ft_putnbr_uns_dec(nb % 10);
	}
	else
		ft_putchar(nb + 48);
	return (count);
}
