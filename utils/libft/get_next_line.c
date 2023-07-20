/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:04:33 by jyim              #+#    #+#             */
/*   Updated: 2022/12/22 15:15:45 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*join_str(char *buffer, char *stash)
{
	char	*line;

	line = ft_strjoin(buffer, stash);
	free(buffer);
	return (line);
}

//return the additional characther behind \n as starting text
char	*next_line(char	*buff)
{
	int		i;
	int		j;
	char	*next_buff;

	i = 0;
	j = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
	{
		free(buff);
		return (NULL);
	}
	next_buff = calloc((ft_strlen(buff) - i + 1), sizeof(char));
	i += 1;
	while (buff[i] != '\0')
	{
		next_buff[j++] = buff[i++];
	}
	free (buff);
	return (next_buff);
}

//return line without additional characthers behind \n and end with NULL
char	*get_line(char *buff)
{
	int		i;
	char	*line;

	i = 0;
	if (!buff[i])
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	line = calloc(i + 2, sizeof(char));
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		line[i] = buff[i];
		i++;
	}
	if (buff[i] && buff[i] == '\n')
		line[i++] = '\n';
	return (line);
}

//read and store upto buffer size repeats until first \n is reached
char	*read_file(int fd, char *buffer)
{
	int		status;
	char	*stash;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	stash = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	status = 1;
	while (status > 0)
	{
		status = read(fd, stash, BUFFER_SIZE);
		if (status == -1)
		{
			free(stash);
			return (NULL);
		}
		stash[status] = 0;
		buffer = join_str(buffer, stash);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	free(stash);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line(buffer);
	buffer = next_line(buffer);
	return (line);
}
