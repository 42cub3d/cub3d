/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:01:43 by gkwon             #+#    #+#             */
/*   Updated: 2023/06/12 15:51:12 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	draw_map(t_map *map, unsigned int h)
{
	(void)h;
	mlx_put_image_to_window(map->mlx, map->window, map->img->n_wall, 0, 0);
}

void	init_img(t_map *map)
{
	int		img_w;
	int		img_h;
	char	*str;

	str = map->img->w_wall;
	map->img->w_wall = mlx_xpm_file_to_image(map->mlx, str, &img_w, &img_h);
	free(str);
	str = map->img->n_wall;
	map->img->n_wall = mlx_xpm_file_to_image(map->mlx, str, &img_w, &img_h);
	free(str);
	str = map->img->s_wall;
	map->img->s_wall = mlx_xpm_file_to_image(map->mlx, str, &img_w, &img_h);
	free(str);
	str = map->img->e_wall;
	map->img->e_wall = mlx_xpm_file_to_image(map->mlx, str, &img_w, &img_h);
	free(str);
}
