/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:37:48 by subcho            #+#    #+#             */
/*   Updated: 2023/06/26 21:04:18 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minilibx/mlx.h"
# include "stdio.h"
# include "stdlib.h"
# include "math.h"
# include "sys/time.h"

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480
# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_KEY_EXIT 17
# define KEY_ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y; // 1인칭 슈팅게임에 적합
}	t_player;

typedef	struct  s_DDA
{
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}	t_DDA;

typedef struct s_draw_info
{
	int	line_height;
	int	draw_start;
	int	draw_end;
}	t_draw_info;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			endian;
	int			line_len;
}	t_img;

typedef struct s_map
{
	void		*mlx;
	void		*win;
	t_player	*player;
	t_DDA		*dda;
	t_draw_info	*draw_info;
	double		move_speed;
	double		rot_speed;
	t_img		*img;
}	t_map;

int	press_key(int key_code, t_map *map);

int	exit_game(t_map *map)
{
	mlx_destroy_window(map->mlx, map->win);
	exit(1);
}

void	drow_window(t_map	*map)
{
	mlx_hook(map->win, X_EVENT_KEY_PRESS, 0, press_key, map);
	mlx_hook(map->win, X_EVENT_KEY_EXIT, 0, exit_game, map);
	mlx_loop(map->mlx);
}

void	set_player(t_player *player)
{
	player->pos_x = 22; // player's start position
	player->pos_y = 12;
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

void	do_dda(t_DDA *dda)
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
		if (worldMap[dda->map_x][dda->map_y] > 0)
			dda->hit = 1;
	}
}

void	set_draw_info(t_map *map)
{
	t_draw_info *draw_info;
	t_DDA *dda;

	draw_info = map->draw_info;
	dda = map->dda;
	draw_info->line_height = (int)(screenHeight / dda->perp_wall_dist);
	draw_info->draw_start = -draw_info->line_height / 2 + screenHeight / 2;
	if (draw_info->draw_start < 0)
		draw_info->draw_start = 0;
	draw_info->draw_end = draw_info->line_height / 2 + screenHeight / 2;
	if (draw_info->draw_end >= screenHeight)
		draw_info->draw_end = screenHeight - 1;
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * screenWidth + x)
			*(img->bits_per_pixel / 8);
	*(unsigned int *)dst = color;
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	draw_pixel(int x, t_map *map, int color)
{
	int	i;

	i = 0;
	while (i < map->draw_info->draw_start)
	{
		my_mlx_pixel_put(map->img, x, i, create_rgb(255, 192, 203));
		i++;
	}
	i = map->draw_info->draw_start;
	while (i < map->draw_info->draw_end)
	{
		my_mlx_pixel_put(map->img, x, i, color);
		i++;
	}
	i = map->draw_info->draw_end;
	while (i < screenHeight)
	{
		my_mlx_pixel_put(map->img, x, i, create_rgb(255, 20, 147));
		i++;
	}
}

int	set_color(t_DDA *dda)
{
	if (worldMap[dda->map_x][dda->map_y] == 0)
		return create_rgb(255, 20, 147);
	if (worldMap[dda->map_x][dda->map_y] == 1)
		return create_rgb(255, 0, 0);
	if (worldMap[dda->map_x][dda->map_y] == 2)
		return create_rgb(0, 255, 0);
	if (worldMap[dda->map_x][dda->map_y] == 3)
		return create_rgb(0, 0, 255);
	if (worldMap[dda->map_x][dda->map_y] == 4)
		return create_rgb(255, 255, 255);
	return create_rgb(255, 255, 0);
}

void	raycasting(t_map *map, t_player *player)
{
	int		i;
	int		color;
	double	camera_x; // 광선 방향 계산에 이용
	double	ray_dir_x;
	double	ray_dir_y;

	i = 0;
	map->img->img = mlx_new_image(map->mlx, screenWidth, screenHeight);
	map->img->addr = mlx_get_data_addr(map->img->img, &map->img->bits_per_pixel, &map->img->line_len, &map->img->endian);
	while (i < screenWidth)
	{
		// cal ray position and direction
		camera_x = 2 * i / (double)screenWidth - 1;
		ray_dir_x = player->dir_x + player->plane_x * camera_x;
		ray_dir_y = player->dir_y + player->plane_y * camera_x;
		set_dda(map->dda, player, ray_dir_x, ray_dir_y);
		do_dda(map->dda);
		if (map->dda->side == 0)
			map->dda->perp_wall_dist = (map->dda->map_x - map->player->pos_x + (1 - map->dda->step_x) / 2) / ray_dir_x;
      	else
			map->dda->perp_wall_dist = (map->dda->map_y - map->player->pos_y + (1 - map->dda->step_y) / 2) / ray_dir_y;
		set_draw_info(map);
		color = set_color(map->dda);
		if (map->dda->side == 1)
			color = color / 2;
		draw_pixel(i, map, color);
		i++;
	}
	mlx_put_image_to_window(map->mlx, map->win, map->img->img, 0, 0);
	mlx_destroy_image(map->mlx, map->img->img);
}

int	press_key(int key_code, t_map *map)
{
	t_player	*player;
	double		padding;

	player = map->player;
	padding = 0.1;
	// 이동 시 padding 줄 것
	if (key_code == KEY_ESC)
		exit_game(map);
	if (key_code == KEY_W)
	{
		// forward
		printf("key w\n");
		if (worldMap[(int)(player->pos_x + player->dir_x * map->move_speed)][(int)player->pos_y] == 0)
			player->pos_x += player->dir_x * map->move_speed;
		if (worldMap[(int)player->pos_x][(int)(player->pos_y + player->dir_y * map->move_speed)] == 0)
			player->pos_y += player->dir_y * map->move_speed;
	}
	if (key_code == KEY_S)
	{
		//backward
		printf("key s\n");
		if (worldMap[(int)(player->pos_x - player->dir_x * map->move_speed)][(int)player->pos_y] == 0)
			player->pos_x -= player->dir_x * map->move_speed;
		if (worldMap[(int)player->pos_x][(int)(player->pos_y - player->dir_y * map->move_speed)] == 0)
			player->pos_y -= player->dir_y * map->move_speed;
	}
	if (key_code == KEY_D)
	{
		//right
		printf("key d\n");
		if (worldMap[(int)(player->pos_x + player->dir_y * map->move_speed)][(int)player->pos_y] == 0)
			player->pos_x += player->dir_y * map->move_speed;
		if (worldMap[(int)(player->pos_x)][(int)(player->pos_y - player->dir_x * map->move_speed)] == 0)
			player->pos_y -= player->dir_x * map->move_speed;
	}
	if (key_code == KEY_A)
	{
		//left
		printf("key a\n");
		if (worldMap[(int)(player->pos_x)][(int)(player->pos_y + player->dir_x * map->move_speed)] == 0)
			player->pos_y += player->dir_x * map->move_speed;
		if (worldMap[(int)(player->pos_x - player->dir_y * map->move_speed)][(int)(player->pos_y)] == 0)
			player->pos_x -= player->dir_y * map->move_speed;
	}
	if (key_code == KEY_RIGHT)
	{
		//camera right
		printf("key right\n");
		double old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(-(map->rot_speed)) - player->dir_y * sin(-(map->rot_speed));
		player->dir_y = old_dir_x * sin(-(map->rot_speed)) + player->dir_y * cos(-(map->rot_speed));
		double old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(-(map->rot_speed)) - player->plane_y * sin(-(map->rot_speed));
		player->plane_y = old_plane_x * sin(-(map->rot_speed)) + player->plane_y * cos(-(map->rot_speed));
	}
	if (key_code == KEY_LEFT)
	{
		//camera left
		printf("key left\n");
		double old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(map->rot_speed) - player->dir_y * sin(map->rot_speed);
		player->dir_y = old_dir_x * sin(map->rot_speed) + player->dir_y * cos(map->rot_speed);
		double old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(map->rot_speed) - player->plane_y * sin(map->rot_speed);
		player->plane_y = old_plane_x * sin(map->rot_speed) + player->plane_y * cos(map->rot_speed);
	}
	raycasting(map, map->player);
	return (0);
}

int main()
{
	t_map		map;
	//t_img		img;
	t_player	player;
	t_DDA		dda;
	t_draw_info	draw_info;

	set_player(&player);
	map.player = &player;
	map.move_speed = 0.5;
	map.rot_speed = 0.1;
	map.dda = &dda;
	map.draw_info = &draw_info;
	map.mlx = mlx_init();
	map.win = mlx_new_window(map.mlx, screenWidth, screenHeight, "raycasting");
	raycasting(&map, map.player);
	drow_window(&map);
	return 0;
}
