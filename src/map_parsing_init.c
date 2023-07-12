/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:29:27 by gkwon             #+#    #+#             */
/*   Updated: 2023/07/12 17:25:10 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int	init_arg(t_map *map, int i)
{
	char	**tmp_rgb;

	tmp_rgb = ft_split(map->map_argv[4], ',');
	while (++i < 3)
		map->floor_color[i] = ft_atoi(tmp_rgb[i]);
	i = -1;
	tmp_rgb = ft_split(map->map_argv[5], ',');
	while (++i < 3)
		map->ceiling_color[i] = ft_atoi(tmp_rgb[i]);
	return (0);
}

int	search_arg(t_map *map, int i, int j)
{
	static char	*campass[] = {"NO", "SO", "WE", "EA", "F ", "C "};

	map->map_argv = malloc(sizeof(char *) * 6);
	map->x -= 6;
	while (i >= 0 && j < 6 && map->map_char[i])
	{
		j = 6;
		while (--j != -1)
		{
			if (ft_strncmp(map->map_char[i], campass[j], 2) == 0)
			{
				map->map_argv[j] = ft_strtrim(map->map_char[i] + 2, " \n\t\v\f\r");
				break ;
			}
		}
		i--;
	}
	if (i != -1)
		return (1);
	return (init_arg(map, -1));
}

void	init_map(t_map *map, int fd, int cnt)
{
	char	*line;

	line = get_next_line(fd);
	if (cnt == 0 && !line)
		ft_error(PARSINGERR);
	while (line && *line == '\n')
		line = get_next_line(fd);
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
