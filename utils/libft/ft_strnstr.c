/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:51:05 by jyim              #+#    #+#             */
/*   Updated: 2022/11/07 15:26:14 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*findneedle(const char *haystack, const char *needle, size_t len)
{
	char	*temp_hay;
	size_t	i;
	size_t	j;

	temp_hay = (char *)haystack;
	j = 0;
	while (*temp_hay != '\0')
	{
		if (*temp_hay == *needle)
		{
			i = 0;
			while ((i + j) < len && needle[i] != '\0')
			{
				if (temp_hay[i] == needle[i])
					i++;
				else
					break ;
			}
			if (needle[i] == '\0')
				return (temp_hay);
		}
		temp_hay++;
		j++;
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*temp_hay;

	temp_hay = (char *)haystack;
	if (temp_hay == 0 && len == 0)
		return (0);
	if (*needle == '\0')
		return (temp_hay);
	return (findneedle (haystack, needle, len));
}
