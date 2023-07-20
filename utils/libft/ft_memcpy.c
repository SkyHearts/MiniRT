/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:49:52 by jyim              #+#    #+#             */
/*   Updated: 2022/11/07 14:51:38 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*temp_dst;
	const char	*temp_src;
	size_t		i;

	i = 0;
	temp_dst = dst;
	temp_src = src;
	if (temp_dst == NULL && temp_src == NULL)
		return (0);
	while (n > 0)
	{
		temp_dst[i] = temp_src[i];
		i++;
		n--;
	}
	return ((void *) dst);
}
