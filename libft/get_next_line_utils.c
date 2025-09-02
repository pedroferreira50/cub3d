/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 02:49:19 by pviegas-          #+#    #+#             */
/*   Updated: 2024/11/14 03:39:42 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen2(char const *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(ft_strlen2(s1) + ft_strlen2(s2) + 1);
	if (!str)
		return (NULL);
	while (s1 && s1[i] != '\0')
		str[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i] != '\0' && s2[i] != '\n')
		str[j++] = s2[i++];
	if (s2[i])
		str[j++] = '\n';
	str[j] = '\0';
	return (str);
}

void	buffer_shift_left(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
	{
		i++;
		while (buffer[i] != '\0')
			buffer[j++] = buffer[i++];
		buffer[j] = '\0';
	}
	else
		buffer[0] = '\0';
	while (j < BUFFER_SIZE)
		buffer[j++] = '\0';
}

int	newline_checker(char **line, char *buffer)
{
	int		i;
	int		check;
	char	*join;

	check = 0;
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
	{
		i++;
		check = 1;
	}
	join = ft_strjoin(*line, buffer);
	buffer_shift_left(buffer);
	free(*line);
	if (join == NULL)
		return (-1);
	*line = join;
	return (check);
}

char	*read_loop(char	*buffer, char *line, int fd)
{
	int	check;
	int	byte;

	while (1)
	{
		if (buffer[0] == '\0')
		{
			byte = read(fd, buffer, BUFFER_SIZE);
			if (byte < 1)
			{
				if (byte != -1)
					return (line);
				free(line);
				return (NULL);
			}
		}
		check = newline_checker(&line, buffer);
		if (check == 1)
			return (line);
		else if (check == -1)
			return (NULL);
	}
}
