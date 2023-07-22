/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:57:01 by gkwon             #+#    #+#             */
/*   Updated: 2023/07/22 15:49:29 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	press_key3(int key_code, t_map *map, double old_dir_x,
double old_plane_x)
{
	old_dir_x = map->player->dir_x;
	old_plane_x = map->player->plane_x;
	if (key_code == KEY_RIGHT)
	{
		map->player->dir_x = map->player->dir_x * cos(-(map->rot_speed))
			- map->player->dir_y * sin(-(map->rot_speed));
		map->player->dir_y = old_dir_x * sin(-(map->rot_speed))
			+ map->player->dir_y * cos(-(map->rot_speed));
		map->player->plane_x = map->player->plane_x * cos(-(map->rot_speed))
			- map->player->plane_y * sin(-(map->rot_speed));
		map->player->plane_y = old_plane_x * sin(-(map->rot_speed))
			+ map->player->plane_y * cos(-(map->rot_speed));
	}
	if (key_code == KEY_LEFT)
	{
		map->player->dir_x = map->player->dir_x * cos(map->rot_speed)
			- map->player->dir_y * sin(map->rot_speed);
		map->player->dir_y = old_dir_x * sin(map->rot_speed)
			+ map->player->dir_y * cos(map->rot_speed);
		map->player->plane_x = map->player->plane_x * cos(map->rot_speed)
			- map->player->plane_y * sin(map->rot_speed);
		map->player->plane_y = old_plane_x * sin(map->rot_speed)
			+ map->player->plane_y * cos(map->rot_speed);
	}
}

void	press_key2(int key_code, t_map *map)
{
	if (key_code == KEY_D)
	{
		if (map->map_char[(int)(map->player->pos_x + map->player->dir_y
				* map->move_speed)][(int)map->player->pos_y] == '0')
			map->player->pos_x += map->player->dir_y * map->move_speed;
		if (map->map_char[(int)(map->player->pos_x)][(int)(map->player->pos_y
				- map->player->dir_x * map->move_speed)] == '0')
			map->player->pos_y -= map->player->dir_x * map->move_speed;
	}
	if (key_code == KEY_A)
	{
		if (map->map_char[(int)(map->player->pos_x)][(int)(map->player->pos_y
				+ map->player->dir_x * map->move_speed)] == '0')
			map->player->pos_y += map->player->dir_x * map->move_speed;
		if (map->map_char[(int)(map->player->pos_x - map->player->dir_y
				* map->move_speed)][(int)(map->player->pos_y)] == '0')
			map->player->pos_x -= map->player->dir_y * map->move_speed;
	}
	press_key3(key_code, map, 0, 0);
}

int	press_key(int key_code, t_map *map)
{
	if (key_code == KEY_ESC)
		exit_game(map);
	if (key_code == KEY_W)
	{
		if (map->map_char[(int)(map->player->pos_x + map->player->dir_x
				* map->move_speed)][(int)map->player->pos_y] == '0')
			map->player->pos_x += map->player->dir_x * map->move_speed;
		if (map->map_char[(int)map->player->pos_x][(int)(map->player->pos_y
			+ map->player->dir_y * map->move_speed)] == '0')
			map->player->pos_y += map->player->dir_y * map->move_speed;
	}
	if (key_code == KEY_S)
	{
		if (map->map_char[(int)(map->player->pos_x - map->player->dir_x
				* map->move_speed)][(int)map->player->pos_y] == '0')
			map->player->pos_x -= map->player->dir_x * map->move_speed;
		if (map->map_char[(int)map->player->pos_x][(int)(map->player->pos_y
			- map->player->dir_y * map->move_speed)] == '0')
			map->player->pos_y -= map->player->dir_y * map->move_speed;
	}
	press_key2(key_code, map);
	return (0);
}

int	exit_game(t_map *map)
{
	mlx_destroy_window(map->mlx, map->win);
	exit(0);
}
