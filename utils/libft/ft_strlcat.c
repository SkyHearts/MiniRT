/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:51:05 by jyim              #+#    #+#             */
/*   Updated: 2022/11/07 15:45:36 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;
	size_t	max_len;

	i = 0;
	src_len = ft_strlen(src);
	if (!dst && dstsize == 0)
		return (src_len);
	dst_len = ft_strlen(dst);
	if (dstsize <= dst_len)
		return (src_len + dstsize);
	max_len = dstsize - dst_len - 1;
	while (max_len != 0 && src[i] != '\0')
	{
		dst[dst_len + i] = src[i];
		i++;
		max_len--;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
