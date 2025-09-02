/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:03:25 by pviegas-          #+#    #+#             */
/*   Updated: 2025/09/02 05:18:53 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_map_line(char *line)
{
	char	*trimmed;
	int		i;
	char	c;

	trimmed = trim_spaces(line);
	if (trimmed[0] == '\0')
		return (false);
	i = 0;
	while (trimmed[i])
	{
		c = trimmed[i];
		if (c != ' ' && c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E'
			&& c != 'W')
			return (false);
		i++;
	}
	return (true);
}

char	*trim_spaces(char *str)
{
	int	len;

	while (*str == ' ' || *str == '\t')
		str++;
	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t' || str[len
				- 1] == '\n' || str[len - 1] == '\r'))
		str[--len] = '\0';
	return (str);
}

char	**copy_map(char **map, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			free_array(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

char	*join_strings(char **strings)
{
	char	*result;
	size_t	total_len;
	size_t	i;

	if (!strings)
		return (NULL);
	total_len = 0;
	i = 1;
	while (strings[i])
	{
		total_len += strlen(strings[i]);
		i++;
	}
	result = malloc(total_len + 1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	i = 1;
	while (strings[i])
	{
		ft_strlcat(result, strings[i], total_len + 1);
		i++;
	}
	return (result);
}

bool	elements_loaded(t_cub_elements *cub3d, t_color *ceil, t_color *floor)
{
	if (!cub3d->no_text || !cub3d->so_text
		|| !cub3d->we_text || !cub3d->ea_text)
		return (false);
	if (!cub3d->no_text->path || !cub3d->so_text->path
		|| !cub3d->we_text->path || !cub3d->ea_text->path)
		return (false);
	if (!floor->color_set || !ceil->color_set)
		return (false);
	return (true);
}
