/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:55:18 by jyim              #+#    #+#             */
/*   Updated: 2023/07/07 23:09:40 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	c;

	c = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[c] != '\0' || s2[c] != '\0')
	{	
		if (s1[c] != s2[c])
			return ((unsigned char)s1[c] - (unsigned char)s2[c]);
		c++;
	}
	return (0);
}
