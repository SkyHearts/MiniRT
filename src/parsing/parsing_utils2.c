/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:24:13 by jyim              #+#    #+#             */
/*   Updated: 2023/08/12 16:05:09 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../inc/minirt.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

int	str_has_aplha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	free_darray(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

int	isempty(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

/* 
Check each element for correct number of arugment/parameter
if incorrect number, return 1
Check if each parameter has alphabets
if alphabet exit, return 1
 */
// print error then return 1, Wrong number of element for A
// print error then return 1, Wrong number of element for cy
// print error then return 1, Wrong number of element for split[0]
// print error then return 1, Element split[0] has alphabet in parameter
int	check_format(char **split)
{
	int	len;
	int	i;

	i = 1;
	len = split_len(split);
	if (!ft_strcmp(split[0], "A"))
	{
		if (len != 3)
			return (printf("Incorrect number of parameters\n"), 1);
	}
	else if (!ft_strcmp(split[0], "cy") || !ft_strcmp(split[0], "cn"))
	{
		if (len != 6)
			return (printf("Incorrect number of parameters\n"), 1);
	}
	else if (len != 4)
		return (printf("Incorrect number of parameters\n"), 1);
	while (split[i])
	{
		if (str_has_aplha(split[i]))
			return (printf("Element %s has an alphabet\n", split[0]), 1);
		i++;
	}
	return (0);
}

// print error here, wrong extension
int	check_ext(char *file)
{
	char	*tmp;

	tmp = ft_strrchr(file, '.');
	if (tmp != NULL)
		if (!ft_strcmp(tmp, ".rt"))
			return (0);
	printf("File error: Invalid file extention\n");
	return (1);
}
