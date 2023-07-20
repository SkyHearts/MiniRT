/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:33:36 by jyim              #+#    #+#             */
/*   Updated: 2022/11/07 13:34:46 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	c_num(int n)
{
	int	count;

	count = 0;
	if (n < 0)
		count += 1;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		s_len;
	char	*str;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	s_len = c_num (n);
	str = malloc (sizeof(char) * s_len + 1);
	if (!str)
		return (0);
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	str[s_len] = '\0';
	while (n != 0)
	{
		str[--s_len] = (n % 10) + 48;
		n /= 10;
	}
	return (str);
}
