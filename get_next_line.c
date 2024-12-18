/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayaalp <mkayaalp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:10:22 by mkayaalp          #+#    #+#             */
/*   Updated: 2024/12/18 11:36:31 by mkayaalp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static char	*ft_get_after_line(char *str)
{
	int		j;
	int		i;
	char	*tmp;

	j = 0;
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (free(str), NULL);
	tmp = malloc(ft_strlen(str) - i + 1);
	if (!tmp)
		return (free(str), NULL);
	i++;
	while (str[i] != '\0')
		tmp[j++] = str[i++];
	tmp[j] = '\0';
	return (free(str), tmp);
}

static char	*ft_get_line(char *str)
{
	char	*temp;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		temp = malloc(i + 2);
	else
		temp = malloc(i + 1);
	if (!temp)
		return (free(str), NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		temp[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		temp[i++] = '\n';
	temp[i] = '\0';
	return (temp);
}

static char	*ft_read_func(char *str, int fd)
{
	int		byte_readed;
	char	*buffer;

	byte_readed = 1;
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(str, '\n') && byte_readed != 0)
	{
		byte_readed = read(fd, buffer, BUFFER_SIZE);
		if (byte_readed == -1)
			return (free(str), free(buffer), NULL);
		buffer[byte_readed] = '\0';
		str = ft_strjoin(str, buffer);
	}
	return (free(buffer), str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	str = ft_read_func(str, fd);
	if (!str)
		return (NULL);
	line = ft_get_line(str);
	str = ft_get_after_line(str);
	return (line);
}
