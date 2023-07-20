/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:27:12 by jyim              #+#    #+#             */
/*   Updated: 2022/11/07 15:27:40 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*temp_s;
	int		count;

	temp_s = (char *) s;
	count = ft_strlen(temp_s);
	while (count >= 0)
	{
		if (temp_s[count] == (unsigned char)c)
			return (temp_s + count);
		count--;
	}
	return (0);
}
