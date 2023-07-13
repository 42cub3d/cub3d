/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:23:58 by gkwon             #+#    #+#             */
/*   Updated: 2023/07/13 21:29:54 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int	set_tex_num(t_map *map, double ray_dir_x, double ray_dir_y)
{
	int	tex_num;

	if (map->dda->side == 1 && ray_dir_y > 0)
		tex_num = 2;
	if (map->dda->side == 1 && ray_dir_y < 0)
		tex_num = 3;
	if (map->dda->side == 0 && ray_dir_x > 0)
		tex_num = 0;
	if (map->dda->side == 0 && ray_dir_x < 0)
		tex_num = 1;
	return (tex_num);
}
