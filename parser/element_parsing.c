/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:03:59 by pviegas-          #+#    #+#             */
/*   Updated: 2025/09/22 12:00:26 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static bool	is_texture_id(char *id)
{
	return (ft_strcmp(id, "NO") == 0 || ft_strcmp(id, "SO") == 0
		|| ft_strcmp(id, "WE") == 0 || ft_strcmp(id, "EA") == 0);
}

static bool	assign_texture_path(char *id, char *val, t_cub_elements *cub3d)
{
	if (!val || val[0] != '.' || val[1] != '/')
		return (false);
	if (ft_strcmp(id, "NO") == 0 && !cub3d->no_text->path)
		cub3d->no_text->path = ft_strdup(val);
	else if (ft_strcmp(id, "SO") == 0 && !cub3d->so_text->path)
		cub3d->so_text->path = ft_strdup(val);
	else if (ft_strcmp(id, "WE") == 0 && !cub3d->we_text->path)
		cub3d->we_text->path = ft_strdup(val);
	else if (ft_strcmp(id, "EA") == 0 && !cub3d->ea_text->path)
		cub3d->ea_text->path = ft_strdup(val);
	else
		return (false);
	return (true);
}

static bool	process_element_value(char *id, char *val, t_cub_elements *cub3d)
{
	if (!val)
		return (false);
	if (is_texture_id(id))
		return (assign_texture_path(id, val, cub3d));
	else if (check_color_id(id, cub3d))
		return (assign_color(id, val, cub3d));
	return (false);
}

static bool	check_element(char *line, t_cub_elements *cub3d)
{
	char	*trimmed;
	char	**sstr;
	char	*id;
	char	*val;
	bool	result;

	trimmed = trim_spaces(line);
	if (ft_strlen(trimmed) == 0)
		return (true);
	sstr = ft_split(trimmed, ' ');
	if (!sstr || !sstr[0])
	{
		if (sstr)
			free_array(sstr);
		return (false);
	}
	id = sstr[0];
	val = join_strings(sstr);
	result = process_element_value(id, val, cub3d);
	free_array(sstr);
	free(val);
	return (result);
}

bool	scan_cub_elements(char *filename, t_cub_elements *cub3d,
		t_color *ceil, t_color *floor)
{
	bool	map_started;
	int		i;
	char	*line;

	cub3d->cub_file = store_cub(filename);
	map_started = false;
	i = 0;
	while (cub3d->cub_file[i])
	{
		line = cub3d->cub_file[i];
		if (!map_started && is_map_line(line))
		{
			if (!elements_loaded(cub3d, ceil, floor))
				return (false);
			return (true);
		}
		if (!check_element(line, cub3d))
			return (false);
		i++;
	}
	return (false);
}
