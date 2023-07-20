/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:29:44 by jyim              #+#    #+#             */
/*   Updated: 2022/11/07 15:29:45 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*subs;
	unsigned int	subs_len;
	unsigned int	c;

	if (s == NULL || len == 0)
		return (ft_strdup(""));
	subs_len = ft_strlen(s + start);
	c = 0;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	subs = malloc (sizeof(char) * len + 1);
	if (!subs)
		return (0);
	while (len > 0 && c < subs_len)
	{
		subs[c++] = s[start++];
		len--;
	}
	subs[c] = '\0';
	return (subs);
}
