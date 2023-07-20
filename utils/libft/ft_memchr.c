/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:35:43 by jyim              #+#    #+#             */
/*   Updated: 2023/07/19 18:24:23 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*temp_s;
	unsigned char	temp_c;

	temp_c = (unsigned char) c;
	temp_s = (unsigned char *) s;
	while (n > 0)
	{
		if (*temp_s != temp_c)
		{
			temp_s++;
			n--;
		}
		else
			return (temp_s);
	}
	return (NULL);
}
