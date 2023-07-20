/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:44:01 by jyim              #+#    #+#             */
/*   Updated: 2022/11/07 15:44:02 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*temp_s;

	temp_s = (char *)s;
	while (*temp_s != (char)c)
	{
		if (!*temp_s)
			return (NULL);
		temp_s++;
	}
	return (temp_s);
}
