/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:33:27 by jyim              #+#    #+#             */
/*   Updated: 2022/11/07 15:46:37 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	n;

	n = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src[n] != '\0' && --dstsize > 0)
	{
		dst[n] = src[n];
		n++;
	}
	dst[n] = '\0';
	while (src[n] != '\0')
		n++;
	return (n);
}
