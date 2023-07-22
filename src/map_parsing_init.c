/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:29:27 by gkwon             #+#    #+#             */
/*   Updated: 2023/07/22 18:50:43 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int	str_count(char *str, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] == c)
			cnt++;
		i++;
	}
	return (cnt);
}

int	set_default_color(t_map *map, char *tmp, int i, int digit)
{
	char	**tmp_rgb;

	if (str_count(tmp, ',') != 2)
		ft_error(PARSINGERR);
	tmp_rgb = ft_split(tmp, ',');
	if (tmp_rgb[3] != 0 || tmp_rgb[0] == 0 || tmp_rgb[1] == 0
		|| tmp_rgb[2] == 0)
		ft_error(PARSINGERR);
	while (++i < 3)
	{
		if (digit)
			map->floor_color[i] = ft_atoi(tmp_rgb[i]);
		else
			map->ceiling_color[i] = ft_atoi(tmp_rgb[i]);
		if (map->floor_color[i] < 0 || map->floor_color[i] > 255
			|| map->ceiling_color[i] < 0 || map->ceiling_color[i] > 255)
			ft_error(PARSINGERR);
	}
	while (i--)
		free(tmp_rgb[i]);
	free(tmp_rgb);
	return (0);
}

int	init_arg(t_map *map)
{
	set_default_color(map, map->map_argv[4], -1, 1);
	set_default_color(map, map->map_argv[5], -1, 0);
	return (0);
}

int	search_arg(t_map *map, int i, int j)
{
	static char	*campass[] = {"NO", "SO", "WE", "EA", "F", "C"};

	map->map_argv = malloc(sizeof(char *) * 6);
	map->x -= 6;
	while (i >= 0 && j < 6 && map->map_char[i])
	{
		j = 6;
		while (--j != -1)
		{
			if (ft_strncmp(map->map_char[i], campass[j],
					ft_strlen(campass[j])) == 0)
			{
				map->map_argv[j] = ft_strtrim(map->map_char[i] + 2, " \n\t\v\f\r");
				if (ft_strlen(campass[j]) == 2)
					check_extension(map->map_argv[j], "xpm");
				break ;
			}
		}
		i--;
	}
	if (i != -1)
		return (1);
	return (init_arg(map));
}

void	init_map(t_map *map, int fd, int cnt)
{
	char	*line;

	line = get_next_line(fd);
	if (cnt == 0 && !line)
		ft_error(PARSINGERR);
	while (line && *line == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
	{
		map->map_char = malloc(sizeof(char *) * (cnt + 1));
		map->x = cnt;
	}
	if (line)
		init_map(map, fd, cnt + 1);
	map->map_char[cnt] = line;
	if ((unsigned int)cnt != map->x && (unsigned int)cnt != map->x - 1)
		map->map_char[cnt][ft_strlen(line) - 1] = 0;
}
