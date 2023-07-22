/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:43:44 by jyim              #+#    #+#             */
/*   Updated: 2023/07/20 12:43:44 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../inc/minirt.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

int	split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int open_file(char *file)
{
	int fd;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		perror("File error");
	return (fd);
		
}

int ft_strcmp_clist(char *line, char *cmp)
{
	int i;
	int j;

	i = 0;
	while (line[i])
	{
		j = 0;
		while (cmp[j])
		{
			if (line[i] == cmp[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

// "A C L sp pl cy"
int ft_strcmp_wlist(char *line, char **cmp)
{
	int i;
	int j;

	i = 0;
	while (cmp[i])
	{
		j = 0;
		while (cmp[j])
		{
			if (!ft_strcmp(line, cmp[j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

double ft_atof(char *num)
{
	int		sign;
	double	whole;
	double	decimal;
	char	*tmp;

	tmp = num;
	sign = 1;
	if (tmp[0] == '-')
	{
		sign *= -1;
		tmp++;
	}
	whole = atoi(tmp);
	while (*tmp != '.' && *tmp)
		tmp++;
	if ((*tmp))
	{
		decimal = ft_atoi(++tmp);
		while (decimal > 1)
			decimal /= 10;
	}
	else 
		decimal = 0.0;
	return (sign * (whole + decimal));
}

int str_has_aplha(char *str)
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

void free_darray(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

/* 
Check each element for correct number of arugment/parameter
if incorrect number, return 1
Check if each parameter has alphabets
if alphabet exit, return 1
 */
int	check_format(char **split)
{
	int	len;
	int	i;

	i = 1;
	len = split_len(split);
	if (!ft_strcmp(split[0], "A"))
	{
	// print error then return 1, Wrong number of element for A
		if (len != 3)
			return (printf("Incorrect number of parameters\n"),1);
	}
	else if (!ft_strcmp(split[0], "cy"))
	{
	// print error then return 1, Wrong number of element for cy
		if (len != 6)
			return (printf("Incorrect number of parameters\n"),1);
	}
	else if (len != 4)
	// print error then return 1, Wrong number of element for split[0]
		return (printf("Incorrect number of parameters\n"), 1);
	while (split[i])
	{
		if (str_has_aplha(split[i]))
		// print error then return 1, Element split[0] has alphabet in parameter
			return (printf("Element %s has an alphabet\n", split[0]), 1);
		i++;
	}
	return (0);
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
