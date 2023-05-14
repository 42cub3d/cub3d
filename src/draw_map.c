/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:01:43 by gkwon             #+#    #+#             */
/*   Updated: 2023/05/14 22:45:56 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	draw_map(t_map *map, unsigned int h)
{
	unsigned int	w;

	while (++h < map->y)
	{
		w = -1;
		while (++w < map->x)
		{
			if (map->map_char[h][w] == '1')
				mlx_put_image_to_window(map->mlx, map->window, map->img.wall, w
					* 64, h * 64);
			else if (map->map_char[h][w] == '0')
				mlx_put_image_to_window(map->mlx, map->window, map->img.land, w
					* 64, h * 64);
			else if (map->map_char[h][w] == 'C')
				mlx_put_image_to_window(map->mlx, map->window, map->img.bab, w
					* 64, h * 64);
			else if (map->map_char[h][w] == 'P')
				mlx_put_image_to_window(map->mlx, map->window, map->img.chara, w
					* 64, h * 64);
			else if (map->map_char[h][w] == 'E')
				mlx_put_image_to_window(map->mlx, map->window, map->img.exit, w
					* 64, h * 64);
		}
	}
}

void	init_img(t_map *map)
{
	int	img_w;
	int	img_h;

	map->img.land = mlx_xpm_file_to_image(map->mlx, "./img/land.xpm", &img_w,
			&img_h);
	map->img.wall = mlx_xpm_file_to_image(map->mlx, "./img/wall.xpm", &img_w,
			&img_h);
	map->img.chara = mlx_xpm_file_to_image(map->mlx, "./img/char.xpm", &img_w,
			&img_h);
	map->img.bab = mlx_xpm_file_to_image(map->mlx, "./img/gookbab.xpm", &img_w,
			&img_h);
	map->img.exit = mlx_xpm_file_to_image(map->mlx, "./img/exit.xpm", &img_w,
			&img_h);
}
