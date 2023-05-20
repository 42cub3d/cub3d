/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:29:27 by gkwon             #+#    #+#             */
/*   Updated: 2023/05/20 20:48:48 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void _print(t_map *map)
{
	printf("n_wall :%s\n",map->img->n_wall);
	printf("e_wall :%s\n",map->img->e_wall);
	printf("w_wall :%s\n",map->img->w_wall);
	printf("s_wall :%s\n",map->img->s_wall);
	printf("y :%d\n",map->y);
	int i = -1;
	while (++i < 3)
	{
		printf("_f :%d\n",map->floor_color[i]);
		printf("_c :%d\n",map->ceiling_color[i]);
	}
}

int	init_arg(t_map *map, int i)
{
	char	**tmp_rgb;

	map->img = malloc(sizeof(t_img));
	map->img->n_wall = ft_strdup(map->map_argv[0]);
	map->img->s_wall = ft_strdup(map->map_argv[1]);
	map->img->w_wall = ft_strdup(map->map_argv[2]);
	map->img->e_wall = ft_strdup(map->map_argv[3]);
	tmp_rgb = ft_split(map->map_argv[4], ',');
	while (++i < 3)
		map->floor_color[i] = ft_atoi(tmp_rgb[i]);
	i = -1;
	tmp_rgb = ft_split(map->map_argv[5], ',');
	while (++i < 3)
		map->ceiling_color[i] = ft_atoi(tmp_rgb[i]);
	_print(map);
	return (0);
}

int	search_arg(t_map *map, int i, int j)
{
	static char	*campass[] = {"NO", "SO", "WE", "EA", "F ", "C "};

	map->y -= 6;
	while (i >= 0 && j < 6 && map->map_char[i])
	{
		j = 6;
		while (--j != -1)
		{
			if (ft_strncmp(map->map_char[i], campass[j], 2) == 0)
			{
				map->map_argv[j] = ft_strdup(map->map_char[i] +2);
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
		map->y = cnt;
	}
	while (line && *line == '\n')
		line = get_next_line(fd);
	if (line)
		init_map(map, fd, cnt + 1);
	map->map_char[cnt] = line;
}
