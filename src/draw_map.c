/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:01:43 by gkwon             #+#    #+#             */
/*   Updated: 2023/07/11 16:15:01 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_img_minimap *minimap, int x, int y, int color)
{
	char	*dst;

	dst = minimap->addr + (y * minimap->line_len + x
			*(minimap->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	pixel_put_while(t_img_minimap *minimap, unsigned int w, unsigned int h, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < minimap->pixel_size)
	{
		y = 0;
		while (y < minimap->pixel_size)
		{
			my_mlx_pixel_put(minimap, h * minimap->pixel_size + x,
				w * minimap->pixel_size + y, color);
			y++;
		}
		x++;
	}
}

void	get_map_line_max(t_map *map)
{
	int	w;
	int	h;
	int	max;

	max = -2147483648;
	h = 0;
	while (h < (int)map->x)
	{
		w = ft_strlen(map->map_char[h]);
		if (w > max)
			max = w;
		h++;
	}
	map->max_map_line = max;
}

void	set_minimap(t_map *map, t_img_minimap *minimap)
{
	int				c_color;
	int				f_color;
	unsigned int	w;
	unsigned int	h;

	c_color = create_rgb(255, 192, 203);
	f_color = create_rgb(255, 255, 255);
	h = 0;
	printf("map->player->x : %f, map->player->y : %f\n", map->player->pos_x, map->player->pos_y);
	while (h < map->x)
	{
		w = 0;
		while (w < ft_strlen(map->map_char[h]))
		{
			if (map->map_char[h][w] == '1') // ceiling
				pixel_put_while(minimap, (h - 6), w, c_color);
			else if (map->map_char[h][w] == '0') // floor
				pixel_put_while(minimap, (h - 6), w, f_color);
			else if (w == map->player->pos_x && h == map->player->pos_y)
				pixel_put_while(minimap, (h - 6), w, create_rgb(255, 103, 129));
			w++;
		}
		h++;
	}
}

int		get_pixel_size(t_map *map)
{
	if (map->x > (unsigned int)map->max_map_line)
		return (300 / map->x);
	return (400 / map->max_map_line);
}

void	draw_map(t_map *map)
{
	t_img_minimap	minimap;

	get_map_line_max(map);
	minimap.pixel_size = get_pixel_size(map);
	minimap.img = mlx_new_image(map->mlx, minimap.pixel_size * map->max_map_line, minimap.pixel_size * map->x);
	minimap.addr = mlx_get_data_addr(minimap.img, &minimap.bits_per_pixel,
			&minimap.line_len, &minimap.endian);
	set_minimap(map, &minimap);
	mlx_put_image_to_window(map->mlx, map->win, minimap.img, 0, 0);
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
