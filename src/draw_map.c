/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:01:43 by gkwon             #+#    #+#             */
/*   Updated: 2023/06/05 19:34:46 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	draw_map(t_map *map, unsigned int h)
{
	//unsigned int	w;

	(void)map;
	(void)h;
	//while (++h < map->y)
	//{
	//	w = 0;
	//	while (w < ft_strlen(map->map_char[w]))
	//	{
	//		if (map->map_char[h][w] == '1')
	//			mlx_put_image_to_window(map->mlx, map->window, map->img->n_wall, w
	//				* 64, h * 64);
	//		else if (map->map_char[h][w] == '0')
	//			mlx_put_image_to_window(map->mlx, map->window, map->img->w_wall, w
	//				* 64, h * 64);
	//		w++;
	//	}
	//}
}

void	init_img(t_map *map)
{
	int	img_w;
	int	img_h;

	map->img->w_wall = mlx_xpm_file_to_image(map->mlx, map->img->w_wall, &img_w,
			&img_h);
	map->img->e_wall = mlx_xpm_file_to_image(map->mlx, map->img->e_wall, &img_w,
			&img_h);
	map->img->n_wall = mlx_xpm_file_to_image(map->mlx, map->img->n_wall, &img_w,
			&img_h);
	map->img->s_wall = mlx_xpm_file_to_image(map->mlx, map->img->s_wall, &img_w,
			&img_h);
}