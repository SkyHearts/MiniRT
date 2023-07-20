/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:33:05 by jyim              #+#    #+#             */
/*   Updated: 2022/11/07 15:48:57 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const char		*temp_src;
	char			*temp_dst;
	unsigned int	i;

	temp_dst = dst;
	temp_src = src;
	if (temp_dst == NULL && temp_src == NULL)
		return (0);
	if (src < dst)
	{
		i = len - 1;
		while (len > 0)
		{
			temp_dst[i] = temp_src[i];
			i--;
			len--;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
