/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:55:15 by gkwon             #+#    #+#             */
/*   Updated: 2023/07/20 18:08:18 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	draw_buffer(int x, t_map *map)
{
	int	i;

	i = map->draw_info->draw_start;
	while (i < map->draw_info->draw_end)
	{
		map->img->addr[SCREENWIDTH * i + x] = map->buf[i][x];
		i++;
	}
	i = 0;
	while (i < map->draw_info->draw_start)
	{
		map->img->addr[SCREENWIDTH * i + x] = create_rgb(map->ceiling_color[0],
				map->ceiling_color[1], map->ceiling_color[2]);
		i++;
	}
	i = map->draw_info->draw_end;
	while (i + 1 < SCREENHEIGHT)
	{
		map->img->addr[SCREENWIDTH * i + x] = create_rgb(map->floor_color[0],
				map->floor_color[1], map->floor_color[2]);
		i++;
	}
}

void	calculate_wall_texture(t_map *map, double ray_dir_x, double ray_dir_y)
{
	if (map->dda->side == 0)
		map->dda->wall_x = map->player->pos_y + map->dda->perp_wall_dist
			* ray_dir_y;
	else
		map->dda->wall_x = map->player->pos_x + map->dda->perp_wall_dist
			* ray_dir_x;
	map->dda->wall_x -= floor(map->dda->wall_x);
	map->dda->tex_x = (int)(map->dda->wall_x * (double)TEXWIDTH);
	if (map->dda->side == 0 && ray_dir_x > 0)
		map->dda->tex_x = TEXWIDTH - map->dda->tex_x - 1;
	if (map->dda->side == 1 && ray_dir_y < 0)
		map->dda->tex_x = TEXWIDTH - map->dda->tex_x - 1;
}

void	set_color(int x, t_draw_info *draw_info, t_map *map, int tex_num)
{
	int		i;
	double	step;
	int		tex_y;
	int		color;

	step = 1.0 * TEXHEIGHT / draw_info->line_height;
	map->dda->tex_pos = (draw_info->draw_start - map->dda->pitch - SCREENHEIGHT
			/ 2 + draw_info->line_height / 2) * step;
	i = draw_info->draw_start;
	while (i < draw_info->draw_end)
	{
		tex_y = (int)map->dda->tex_pos & (TEXHEIGHT - 1);
		map->dda->tex_pos += step;
		color = map->texture[tex_num].addr[TEXHEIGHT * tex_y + map->dda->tex_x];
		if (map->dda->side == 1)
			color = (color >> 1) & 8355711;
		map->buf[i][x] = color;
		i++;
	}
}

void	ray_loop(t_map *map, int i)
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		tex_num;
	double	camera_x;

	camera_x = 2 * i / (double)SCREENWIDTH - 1;
	ray_dir_x = map->player->dir_x + map->player->plane_x * camera_x;
	ray_dir_y = map->player->dir_y + map->player->plane_y * camera_x;
	set_dda(map->dda, map->player, ray_dir_x, ray_dir_y);
	do_dda(map->dda, map);
	if (map->dda->side == 0)
		map->dda->perp_wall_dist = (map->dda->map_x - map->player->pos_x
				+ (1 - map->dda->step_x) / 2) / ray_dir_x;
	else
		map->dda->perp_wall_dist = (map->dda->map_y - map->player->pos_y
				+ (1 - map->dda->step_y) / 2) / ray_dir_y;
	set_draw_info(map);
	tex_num = set_tex_num(map, ray_dir_x, ray_dir_y);
	calculate_wall_texture(map, ray_dir_x, ray_dir_y);
	set_color(i, map->draw_info, map, tex_num);
	draw_buffer(i, map);
}

int	raycasting(t_map *map)
{
	int		i;

	i = -1;
	map->img->img = mlx_new_image(map->mlx, SCREENWIDTH, SCREENHEIGHT);
	map->img->addr = (unsigned int *)mlx_get_data_addr(map->img->img,
			&map->img->bits_per_pixel, &map->img->line_len, &map->img->endian);
	while (++i < SCREENWIDTH)
		ray_loop(map, i);
	mlx_put_image_to_window(map->mlx, map->win, map->img->img, 0, 0);
	mlx_destroy_image(map->mlx, map->img->img);
	reset_buffer(map);
	return (0);
}
