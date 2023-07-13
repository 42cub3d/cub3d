/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 21:28:12 by subcho            #+#    #+#             */
/*   Updated: 2023/07/13 21:29:10 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	set_direction_ew(t_map *map, char direction)
{
	if (direction == 'E')
	{
		map->player->dir_x = 0;
		map->player->dir_y = 1;
		map->player->plane_x = 0.66;
		map->player->plane_y = 0;
	}
	if (direction == 'W')
	{
		map->player->dir_x = 0;
		map->player->dir_y = -1;
		map->player->plane_x = -0.66;
		map->player->plane_y = 0;
	}
}

void	set_direction_sn(t_map *map, char direction)
{
	if (direction == 'S')
	{
		map->player->dir_x = 1;
		map->player->dir_y = 0;
		map->player->plane_x = 0;
		map->player->plane_y = -0.66;
	}
	if (direction == 'N')
	{
		map->player->dir_x = -1;
		map->player->dir_y = 0;
		map->player->plane_x = 0;
		map->player->plane_y = 0.66;
	}
}
