/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:08:49 by gkwon             #+#    #+#             */
/*   Updated: 2023/07/20 18:08:18 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	set_texture(t_map *map)
{
	int	w;
	int	h;
	int	i;

	map->texture = malloc(sizeof(t_img) * 4);
	(map->texture)[0].img = mlx_xpm_file_to_image(map->mlx, map->map_argv[0],
			&w, &h);
	(map->texture)[1].img = mlx_xpm_file_to_image(map->mlx, map->map_argv[1],
			&w, &h);
	(map->texture)[2].img = mlx_xpm_file_to_image(map->mlx, map->map_argv[2],
			&w, &h);
	(map->texture)[3].img = mlx_xpm_file_to_image(map->mlx, map->map_argv[3],
			&w, &h);
	i = 0;
	while (i < 4)
	{
		(map->texture)[i].addr = (unsigned int *)mlx_get_data_addr(
				(map->texture)[i].img, &(map->texture)[i].bits_per_pixel,
				&(map->texture)[i].line_len, &(map->texture)[i].endian);
		i++;
	}
}

void	set_dda_attribute(t_DDA *dda, t_player *player, double ray_dir_x,
		double ray_dir_y)
{
	dda->map_x = (int)player->pos_x;
	dda->map_y = (int)player->pos_y;
	dda->delta_dist_x = fabs(1 / ray_dir_x);
	dda->delta_dist_y = fabs(1 / ray_dir_y);
	dda->hit = 0;
}

void	set_dda(t_DDA *dda, t_player *player, double ray_dir_x,
		double ray_dir_y)
{
	set_dda_attribute(dda, player, ray_dir_x, ray_dir_y);
	if (ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (player->pos_x - dda->map_x) * dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0 - player->pos_x)
			* dda->delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (player->pos_y - dda->map_y) * dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0 - player->pos_y)
			* dda->delta_dist_y;
	}
}

void	do_dda(t_DDA *dda, t_map *map)
{
	while (dda->hit == 0)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if (map->map_char[dda->map_x][dda->map_y] == '1')
			dda->hit = 1;
	}
}

void	set_draw_info(t_map *map)
{
	map->draw_info->line_height = (int)(SCREENHEIGHT
			/ map->dda->perp_wall_dist);
	map->draw_info->draw_start = -map->draw_info->line_height / 2 + SCREENHEIGHT
		/ 2 + map->dda->pitch;
	if (map->draw_info->draw_start < 0)
		map->draw_info->draw_start = 0;
	map->draw_info->draw_end = map->draw_info->line_height / 2 + SCREENHEIGHT
		/ 2 + map->dda->pitch;
	if (map->draw_info->draw_end >= SCREENHEIGHT
		|| map->draw_info->draw_end < 0)
		map->draw_info->draw_end = SCREENHEIGHT - 1;
}
