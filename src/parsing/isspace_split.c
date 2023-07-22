/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isspace_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 12:51:48 by jyim              #+#    #+#             */
/*   Updated: 2023/07/22 13:46:27 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../inc/minirt.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == ' ' )
		return (1);
	if (c == '\v' || c == '\f' || c == '\r' )
		return (1);
	if (c == '\0')
		return (1);
	return (0);
}

int	count_words_isspace(char *str)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isspace(str[i + 1]) == 1
			&& ft_isspace(str[i]) == 0)
			words++;
		i++;
	}
	return (words);
}

void	write_word_isspace(char *dest, char *from)
{
	int	i;

	i = 0;
	while (ft_isspace(from[i]) == 0)
	{
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

void	write_split_isspace(char **split, char *str)
{
	int		i;
	int		j;
	int		word;

	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isspace(str[i]) == 1)
			i++;
		else
		{
			j = 0;
			while (ft_isspace(str[i + j]) == 0)
				j++;
			split[word] = (char *)malloc(sizeof(char) * (j + 1));
			write_word_isspace(split[word], str + i);
			i += j;
			word++;
		}
	}	
}

char	**isspace_split(const char *str)
{
	char	**res;
	int		words;
	char	*pstr;

	pstr = (char *)str;
	if (pstr == NULL)
		return (0);
	words = count_words_isspace(pstr);
	res = (char **)malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (0);
	res[words] = 0;
	write_split_isspace(res, pstr);
	return (res);
}
