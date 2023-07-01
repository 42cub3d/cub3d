/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_textured.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:37:48 by subcho            #+#    #+#             */
/*   Updated: 2023/07/01 19:55:19 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minilibx/mlx.h"
# include "stdio.h"
# include "stdlib.h"
# include "math.h"
# include "sys/time.h"

// map info
#define mapWidth 24
#define mapHeight 24
#define texWidth 64
#define texHeight 64
#define screenWidth 1280
#define screenHeight 720

// key info
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

int	buffer[screenHeight][screenWidth];

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
	int		pitch;
	double	tex_pos;
	int		tex_x;
	int		wall_x;
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
	int			*addr;
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
	t_img		*texture;
}	t_map;

int		press_key(int key_code, t_map *map);
int		raycasting(t_map *map);

int	exit_game(t_map *map)
{
	mlx_destroy_window(map->mlx, map->win);
	exit(1);
}

void	drow_window(t_map	*map)
{
	mlx_loop_hook(map->mlx, raycasting, map);
	mlx_hook(map->win, X_EVENT_KEY_PRESS, 0, press_key, map);
	mlx_hook(map->win, X_EVENT_KEY_EXIT, 0, exit_game, map);
	mlx_loop(map->mlx);
}

void	set_player(t_player *player)
{
	player->pos_x = 22; // player's start position
	player->pos_y = 11.5;
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
	t_DDA		*dda;
	t_draw_info *draw_info;

	dda = map->dda;
	draw_info = map->draw_info;
	draw_info->line_height = (int)(screenHeight / dda->perp_wall_dist);
	draw_info->draw_start = -draw_info->line_height / 2 + screenHeight / 2 + dda->pitch;
	if (draw_info->draw_start < 0)
		draw_info->draw_start = 0;
	draw_info->draw_end = draw_info->line_height / 2 + screenHeight / 2 + dda->pitch;
	if (draw_info->draw_end >= screenHeight || draw_info->draw_end < 0)
		draw_info->draw_end = screenHeight - 1;
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	draw_buffer(int x, t_map *map)
{
	int	i;

	i = map->draw_info->draw_start;
	while (i < map->draw_info->draw_end)
	{
		map->img->addr[screenWidth * i + x] = buffer[i][x];
		i++;
	}
	i = 0;
	while (i < map->draw_info->draw_start)
	{
		map->img->addr[screenWidth * i + x] = create_rgb(255, 230, 245);
		i++;
	}
	i = map->draw_info->draw_end;
	while (i < screenHeight)
	{
		// floor
		map->img->addr[screenWidth * i + x] = create_rgb(255, 192, 203);
		i++;
	}
}

void	calculate_wall_texture(t_map *map, double ray_dir_x, double ray_dir_y)
{
	t_DDA	*dda;

	dda = map->dda;
	if (dda->side == 0)
		dda->wall_x = map->player->pos_y + dda->perp_wall_dist * ray_dir_y;
	else
		dda->wall_x = map->player->pos_x + dda->perp_wall_dist * ray_dir_x;
	dda->wall_x -= floor(dda->wall_x);
	dda->tex_x = (int)(dda->wall_x * (double)texWidth);
	if (dda->side == 0 && ray_dir_x > 0)
		dda->tex_x = texWidth - dda->tex_x - 1;
	if (dda->side == 1 && ray_dir_y < 0)
		dda->tex_x = texWidth - dda->tex_x - 1;
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

int	raycasting(t_map *map)
{
	int			i;
	double		camera_x; // 광선 방향 계산에 이용
	double		ray_dir_x;
	double		ray_dir_y;
	int			texNum;
	t_player	*player;

	i = 0;
	player = map->player;
	map->img->img = mlx_new_image(map->mlx, screenWidth, screenHeight);
	map->img->addr = (int *)mlx_get_data_addr(map->img->img, &map->img->bits_per_pixel, &map->img->line_len, &map->img->endian);
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
		texNum = worldMap[map->dda->map_x][map->dda->map_y] - 1;
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
		if (worldMap[(int)(player->pos_x + player->dir_x * map->move_speed)][(int)player->pos_y] == 0)
			player->pos_x += player->dir_x * map->move_speed;
		if (worldMap[(int)player->pos_x][(int)(player->pos_y + player->dir_y * map->move_speed)] == 0)
			player->pos_y += player->dir_y * map->move_speed;
	}
	if (key_code == KEY_S)
	{
		//backward
		if (worldMap[(int)(player->pos_x - player->dir_x * map->move_speed)][(int)player->pos_y] == 0)
			player->pos_x -= player->dir_x * map->move_speed;
		if (worldMap[(int)player->pos_x][(int)(player->pos_y - player->dir_y * map->move_speed)] == 0)
			player->pos_y -= player->dir_y * map->move_speed;
	}
	if (key_code == KEY_D)
	{
		//right
		if (worldMap[(int)(player->pos_x + player->dir_y * map->move_speed)][(int)player->pos_y] == 0)
			player->pos_x += player->dir_y * map->move_speed;
		if (worldMap[(int)(player->pos_x)][(int)(player->pos_y - player->dir_x * map->move_speed)] == 0)
			player->pos_y -= player->dir_x * map->move_speed;
	}
	if (key_code == KEY_A)
	{
		//left
		if (worldMap[(int)(player->pos_x)][(int)(player->pos_y + player->dir_x * map->move_speed)] == 0)
			player->pos_y += player->dir_x * map->move_speed;
		if (worldMap[(int)(player->pos_x - player->dir_y * map->move_speed)][(int)(player->pos_y)] == 0)
			player->pos_x -= player->dir_y * map->move_speed;
	}
	if (key_code == KEY_RIGHT)
	{
		//camera right
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
		double old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(map->rot_speed) - player->dir_y * sin(map->rot_speed);
		player->dir_y = old_dir_x * sin(map->rot_speed) + player->dir_y * cos(map->rot_speed);
		double old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(map->rot_speed) - player->plane_y * sin(map->rot_speed);
		player->plane_y = old_plane_x * sin(map->rot_speed) + player->plane_y * cos(map->rot_speed);
	}
	return (0);
}

void	set_texture(t_map *map)
{
	int 		w;
	int			h;
	int			i;
	t_img		*texture;

	texture = malloc(sizeof(t_img) * 4);
	(texture)[0].img = mlx_xpm_file_to_image(map->mlx, "./image/bluestone.xpm", &w, &h);
	(texture)[1].img = mlx_xpm_file_to_image(map->mlx, "./image/eagle.xpm", &w, &h);
	(texture)[2].img = mlx_xpm_file_to_image(map->mlx, "./image/greystone.xpm", &w, &h);
	(texture)[3].img = mlx_xpm_file_to_image(map->mlx, "./image/redbrick.xpm", &w, &h);
	i = 0;
	while (i < 4)
	{
		(texture)[i].addr = (int *)mlx_get_data_addr((texture)[i].img, &(texture)[i].bits_per_pixel, &(texture)[i].line_len, &(texture)[i].endian);
		i++;
	}
	map->texture = texture;
}

int main()
{
	t_map		map;
	t_player	player;
	t_DDA		dda;
	t_draw_info	draw_info;
	t_img		img;

	set_player(&player);
	map.player = &player;
	map.move_speed = 0.5;
	map.rot_speed = 0.3;
	map.img = &img;
	map.dda = &dda;
	map.dda->pitch = 100;
	map.draw_info = &draw_info;
	map.mlx = mlx_init();
	map.win = mlx_new_window(map.mlx, screenWidth, screenHeight, "raycasting");
	set_texture(&map);
	drow_window(&map);
	return (0);
}
