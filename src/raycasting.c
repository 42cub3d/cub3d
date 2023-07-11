/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:55:15 by gkwon             #+#    #+#             */
/*   Updated: 2023/07/11 20:27:53 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int	buffer[screenHeight][screenWidth];

void	set_texture(t_map *map)
{
	int 		w;
	int			h;
	int			i;

	map->texture = malloc(sizeof(t_img) * 4);
	(map->texture)[0].img = mlx_xpm_file_to_image(map->mlx, "./image/EA.xpm", &w, &h);
	(map->texture)[1].img = mlx_xpm_file_to_image(map->mlx, "./image/WE.xpm", &w, &h);
	(map->texture)[2].img = mlx_xpm_file_to_image(map->mlx, "./image/SO.xpm", &w, &h);
	(map->texture)[3].img = mlx_xpm_file_to_image(map->mlx, "./image/NO.xpm", &w, &h);
	i = 0;
	while (i < 4)
	{
		(map->texture)[i].addr = (unsigned int *)mlx_get_data_addr((map->texture)[i].img,
		 &(map->texture)[i].bits_per_pixel, &(map->texture)[i].line_len,
		  &(map->texture)[i].endian);
		i++;
	}
}

void	set_player(t_player *player)
{
	//player->pos_x = player->pos_x + 0.5; // player's start position
	//player->pos_y = player->pos_y + 0.5;
	player->dir_x = -1; // initial direction vector
	player->dir_y = 0;
	player->plane_x = 0; // 2d raycaster version of camera plane
	player->plane_y = 0.66;
}

void	set_dda(t_DDA *dda, t_player *player, double ray_dir_x, double ray_dir_y)
{
	dda->map_x = (int)player->pos_x;
	dda->map_y = (int)player->pos_y;
	dda->delta_dist_x = fabs(1 / ray_dir_x);
	dda->delta_dist_y = fabs(1 / ray_dir_y);
	dda->hit = 0;
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
	map->draw_info->line_height = (int)(screenHeight / map->dda->perp_wall_dist);
	map->draw_info->draw_start = -map->draw_info->line_height / 2 + screenHeight / 2 + map->dda->pitch;
	if (map->draw_info->draw_start < 0)
		map->draw_info->draw_start = 0;
	map->draw_info->draw_end = map->draw_info->line_height / 2 + screenHeight / 2 + map->dda->pitch;
	if (map->draw_info->draw_end >= screenHeight || map->draw_info->draw_end < 0)
		map->draw_info->draw_end = screenHeight - 1;
}

void	draw_buffer(int x, t_map *map)
{
	int i;

	i = map->draw_info->draw_start;
	while (i < map->draw_info->draw_end)
	{
		map->img->addr[screenWidth * i + x] = buffer[i][x];
		i++;
	}
	i = 0;
	while (i < map->draw_info->draw_start)
	{
		// ceiling
		map->img->addr[screenWidth * i + x] = create_rgb(255, 230, 0);
		i++;
	}
	i = map->draw_info->draw_end;
	while (i + 1 < screenHeight)
	{
		// floor
		map->img->addr[screenWidth * i + x] = create_rgb(255, 192, 203);
		i++;
	}
}

void	calculate_wall_texture(t_map *map, double ray_dir_x, double ray_dir_y)
{
	if (map->dda->side == 0)
		map->dda->wall_x = map->player->pos_y + map->dda->perp_wall_dist * ray_dir_y;
	else
		map->dda->wall_x = map->player->pos_x + map->dda->perp_wall_dist * ray_dir_x;
	map->dda->wall_x -= floor(map->dda->wall_x);
	map->dda->tex_x = (int)(map->dda->wall_x * (double)texWidth);
	if (map->dda->side == 0 && ray_dir_x > 0)
		map->dda->tex_x = texWidth - map->dda->tex_x - 1;
	if (map->dda->side == 1 && ray_dir_y < 0)
		map->dda->tex_x = texWidth - map->dda->tex_x - 1;
}

void	set_color(int x, t_draw_info *draw_info, t_map *map, int texNum)
{
	int		i;
	double	step;
	int		tex_y;
	int		color;

	step = 1.0 * texHeight / draw_info->line_height;
	map->dda->tex_pos = (draw_info->draw_start - map->dda->pitch
			- screenHeight / 2 + draw_info->line_height / 2) * step;
	i = draw_info->draw_start;
	while (i < draw_info->draw_end)
	{
		tex_y = (int)map->dda->tex_pos & (texHeight - 1);
		map->dda->tex_pos += step;
		color = map->texture[texNum].addr[texHeight * tex_y + map->dda->tex_x];
		if (map->dda->side == 1)
			color = (color >> 1) & 8355711;
		buffer[i][x] = color;
		i++;
	}
}

void	reset_buffer()
{
	int	i;
	int	j;

	i = 0;
	while (i < screenHeight)
	{
		j = 0;
		while (j < screenWidth)
		{
			buffer[i][j] = 0;
			j++;
		}
		i++;
	}
}

int set_tex_num(t_map *map, double ray_dir_x, double ray_dir_y)
{
	int	texNum;

	if (map->dda->side == 1 && ray_dir_y > 0)
		texNum = 0;
	if (map->dda->side == 1 && ray_dir_y < 0)
		texNum = 1;
	if (map->dda->side == 0 && ray_dir_x > 0)
		texNum = 2;
	if (map->dda->side == 0 && ray_dir_x < 0)
		texNum = 3;
	return (texNum);
}

int	raycasting(t_map *map)
{
	int			i;
	double		camera_x; // 광선 방향 계산에 이용
	double		ray_dir_x;
	double		ray_dir_y;
	int			texNum;

	i = 0;
	map->img->img = mlx_new_image(map->mlx, screenWidth, screenHeight); // why always get new image?
	map->img->addr = (unsigned int *)mlx_get_data_addr(map->img->img, &map->img->bits_per_pixel, &map->img->line_len, &map->img->endian);
	while (i < screenWidth)
	{
		// cal ray position and direction
		camera_x = 2 * i / (double)screenWidth - 1;
		ray_dir_x = map->player->dir_x + map->player->plane_x * camera_x;
		ray_dir_y = map->player->dir_y + map->player->plane_y * camera_x;
		set_dda(map->dda, map->player, ray_dir_x, ray_dir_y);
		do_dda(map->dda, map);
		if (map->dda->side == 0)
			map->dda->perp_wall_dist = (map->dda->map_x - map->player->pos_x + (1 - map->dda->step_x) / 2) / ray_dir_x;
      	else
			map->dda->perp_wall_dist = (map->dda->map_y - map->player->pos_y + (1 - map->dda->step_y) / 2) / ray_dir_y;
		set_draw_info(map);
		texNum = set_tex_num(map, ray_dir_x, ray_dir_y);
		calculate_wall_texture(map, ray_dir_x, ray_dir_y);
		set_color(i, map->draw_info, map, texNum);
		draw_buffer(i, map);
		i++;
	}
	mlx_put_image_to_window(map->mlx, map->win, map->img->img, 0, 0);
	mlx_destroy_image(map->mlx, map->img->img);
	reset_buffer();
	return (0);
}

int	press_key(int key_code, t_map *map)
{
	double		padding;

	padding = 0.1;
	// 이동 시 padding 줄 것
	if (key_code == KEY_ESC)
		exit_game(map);
	if (key_code == KEY_W)
	{
		// forward
		if (map->map_char[(int)(map->player->pos_x + map->player->dir_x * map->move_speed)][(int)map->player->pos_y] == '0')
			map->player->pos_x += map->player->dir_x * map->move_speed;
		if (map->map_char[(int)map->player->pos_x][(int)(map->player->pos_y + map->player->dir_y * map->move_speed)] == '0')
			map->player->pos_y += map->player->dir_y * map->move_speed;
	}
	if (key_code == KEY_S)
	{
		//backward
		if (map->map_char[(int)(map->player->pos_x - map->player->dir_x * map->move_speed)][(int)map->player->pos_y] == '0')
			map->player->pos_x -= map->player->dir_x * map->move_speed;
		if (map->map_char[(int)map->player->pos_x][(int)(map->player->pos_y - map->player->dir_y * map->move_speed)] == '0')
			map->player->pos_y -= map->player->dir_y * map->move_speed;
	}
	if (key_code == KEY_D)
	{
		//right
		if (map->map_char[(int)(map->player->pos_x + map->player->dir_y * map->move_speed)][(int)map->player->pos_y] == '0')
			map->player->pos_x += map->player->dir_y * map->move_speed;
		if (map->map_char[(int)(map->player->pos_x)][(int)(map->player->pos_y - map->player->dir_x * map->move_speed)] == '0')
			map->player->pos_y -= map->player->dir_x * map->move_speed;
	}
	if (key_code == KEY_A)
	{
		//left
		if (map->map_char[(int)(map->player->pos_x)][(int)(map->player->pos_y + map->player->dir_x * map->move_speed)] == '0')
			map->player->pos_y += map->player->dir_x * map->move_speed;
		if (map->map_char[(int)(map->player->pos_x - map->player->dir_y * map->move_speed)][(int)(map->player->pos_y)] == '0')
			map->player->pos_x -= map->player->dir_y * map->move_speed;
	}
	if (key_code == KEY_RIGHT)
	{
		//camera right
		double old_dir_x = map->player->dir_x;
		map->player->dir_x = map->player->dir_x * cos(-(map->rot_speed)) - map->player->dir_y * sin(-(map->rot_speed));
		map->player->dir_y = old_dir_x * sin(-(map->rot_speed)) + map->player->dir_y * cos(-(map->rot_speed));
		double old_plane_x = map->player->plane_x;
		map->player->plane_x = map->player->plane_x * cos(-(map->rot_speed)) - map->player->plane_y * sin(-(map->rot_speed));
		map->player->plane_y = old_plane_x * sin(-(map->rot_speed)) + map->player->plane_y * cos(-(map->rot_speed));
	}
	if (key_code == KEY_LEFT)
	{
		//camera left
		double old_dir_x = map->player->dir_x;
		map->player->dir_x = map->player->dir_x * cos(map->rot_speed) - map->player->dir_y * sin(map->rot_speed);
		map->player->dir_y = old_dir_x * sin(map->rot_speed) + map->player->dir_y * cos(map->rot_speed);
		double old_plane_x = map->player->plane_x;
		map->player->plane_x = map->player->plane_x * cos(map->rot_speed) - map->player->plane_y * sin(map->rot_speed);
		map->player->plane_y = old_plane_x * sin(map->rot_speed) + map->player->plane_y * cos(map->rot_speed);
	}
	return (0);
}