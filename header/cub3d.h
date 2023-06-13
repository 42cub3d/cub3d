/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:08:31 by subcho            #+#    #+#             */
/*   Updated: 2023/06/13 16:25:59 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <../minilibx/mlx.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>

# define E_MAP_VAL "MAP ELEMENT IS NOT SUPOSSED TO BE"
# define E_FD "MAP OEPN FAILED"
# define PARSINGERR "PARSING FAILED"
# define E_MAP_COLSED "MAP IS NOT COLSED"

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_KEY_EXIT 17
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

typedef struct s_player
{
	unsigned int	x;
	unsigned int	y;
	char			direction;
}					t_player;

typedef struct s_img_wall
{
	void			*w_wall;
	void			*n_wall;
	void			*e_wall;
	void			*s_wall;
}					t_img_wall;

typedef struct s_img_minimap
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}				t_img_minimap;

typedef struct s_map
{
	void				*mlx;
	void				*window;
	int					fd;
	unsigned int		y;
	struct s_player		player;
	char				**map_argv;
	char				**map_char;
	bool				is_player_in_map;
	struct s_img_wall	*img;
	int					floor_color[3];
	int					ceiling_color[3];
}					t_map;

/* ===============../src=============== */

void	ft_error(char *strerr);
int		exit_game(t_map *map);
int		press_key(int key_code, t_map *map);
void	next_mom(t_map *map, unsigned int *x, unsigned int *y, int key);
void	move(t_map *map, int key);
void	drow_window(t_map *map);
int		valid_argv(char **argv);
int		map_valid_check(t_map *map, unsigned int i, unsigned int j);
int		init_arg(t_map *map, int i);
int		search_arg(t_map *map, int i, int j);
void	init_map(t_map *map, int fd, int cnt);
void	ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

// draw_map.c
int		create_rgb(int r, int g, int b);
void	my_mlx_pixel_put(t_img_minimap *minimap, int x, int y, int color);
void	pixel_put_while(t_img_minimap *minimap, unsigned int w, unsigned int h, int color);
void	set_minimap(t_map *map, t_img_minimap *minimap);
void	draw_map(t_map *map);
void	init_img(t_map *map);

#endif
