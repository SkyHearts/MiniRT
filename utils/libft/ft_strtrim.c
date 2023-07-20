/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:27:54 by jyim              #+#    #+#             */
/*   Updated: 2022/11/07 15:28:35 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ps1;
	int		start;
	int		end;
	int		len;

	if (s1 == NULL || set == NULL)
		return (ft_strdup(""));
	ps1 = (char *) s1;
	start = 0;
	while (ft_strchr(set, ps1[start]) != NULL)
		start++;
	end = ft_strlen(s1);
	while ((ft_strchr(set, ps1[end]) != NULL))
		end--;
	len = end - start + 1 ;
	return (ft_substr(ps1, start, len));
}
