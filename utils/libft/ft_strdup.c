/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:44:31 by jyim              #+#    #+#             */
/*   Updated: 2022/11/07 15:44:54 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		size;
	int		c;
	char	*srccpy;

	size = 0;
	c = 0;
	while (src[size] != '\0')
		size++;
	srccpy = (char *) malloc(sizeof(char) * size + 1);
	if (srccpy)
	{
		while (src[c] != '\0')
		{
			srccpy[c] = src[c];
			c++;
		}
		srccpy[c] = '\0';
		return (srccpy);
	}
	else
		return (NULL);
}
