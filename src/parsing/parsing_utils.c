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

int	open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		perror("File error");
	return (fd);
}

int	ft_strcmp_clist(char *line, char *cmp)
{
	int	i;
	int	j;

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
int	ft_strcmp_wlist(char *line, char **cmp)
{
	int	i;
	int	j;

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

double	ft_atof(char *num)
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
	whole = ft_atoi(tmp);
	while (*tmp != '.' && *tmp)
		tmp++;
	if ((*tmp))
	{
		decimal = ft_atoi(++tmp);
		while (decimal >= 1)
			decimal /= 10;
	}
	else
		decimal = 0.0;
	return (sign * (whole + decimal));
}
