/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:02:16 by jyim              #+#    #+#             */
/*   Updated: 2023/06/28 15:51:40 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	join_len;
	size_t	i;
	size_t	j;
	char	*strjoin;

	if (s1 == NULL && s2 == NULL)
		return (ft_strdup(""));
	join_len = ft_strlen(s1) + ft_strlen(s2);
	strjoin = malloc(sizeof(char) * (join_len) + 1);
	if (!strjoin)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		strjoin[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		strjoin[i++] = s2[j++];
	strjoin[i] = '\0';
	return (strjoin);
}
