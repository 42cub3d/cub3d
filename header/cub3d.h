/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:08:31 by subcho            #+#    #+#             */
/*   Updated: 2023/07/12 17:35:14 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <../minilibx/mlx.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define E_MAP_VAL "MAP ELEMENT IS NOT SUPOSSED TO BE"
# define E_FD "MAP OEPN FAILED"
# define PARSINGERR "PARSING FAILED"
# define E_MAP_COLSED "MAP IS NOT COLSED"

# define texWidth 64
# define texHeight 64
# define screenWidth 1280
# define screenHeight 720

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

typedef struct s_img_minimap
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_len;
	int				endian;
	int				pixel_size;
}					t_img_minimap;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}					t_player;

typedef struct s_DDA
{
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				pitch;
	double			tex_pos;
	int				tex_x;
	double			wall_x;
}					t_DDA;

typedef struct s_img_info
{
}					t_img_info;

typedef struct s_img
{
	void			*img;
	unsigned int	*addr;
	int				bits_per_pixel;
	int				endian;
	int				line_len;
}					t_img;

typedef struct s_draw_info
{
	int				line_height;
	int				draw_start;
	int				draw_end;
}					t_draw_info;

typedef struct s_map
{
	void			*mlx;
	void			*win;
	int				fd;
	unsigned int	x;
	t_player		*player;
	char			**map_argv;
	char			**map_char;
	int				max_map_line;
	bool			is_player_in_map;
	int				floor_color[3];
	int				ceiling_color[3];
	t_DDA			*dda;
	t_draw_info		*draw_info;
	double			move_speed;
	double			rot_speed;
	t_img			*img;
	t_img			*texture;
	int				t_i;
	int				t_j;
	int				buf[720][1280];
}					t_map;

/* ===============../src=============== */

void				ft_error(char *strerr);
int					exit_game(t_map *map);
int					press_key(int key_code, t_map *map);
void				next_mom(t_map *map, unsigned int *x, unsigned int *y,
						int key);
void				move(t_map *map, int key);
void				drow_window(t_map *map);
int					valid_argv(char **argv);
void				map_valid_check(t_map *map, unsigned int std,
						unsigned int j, unsigned int i);
int					init_arg(t_map *map, int i);
int					search_arg(t_map *map, int i, int j);
void				init_map(t_map *map, int fd, int cnt);
void				ft_putstr_fd(char *s, int fd);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_calloc(size_t count, size_t size);
void				*ft_memset(void *b, int c, size_t len);

// draw_map.c
int					create_rgb(int r, int g, int b);
void				my_mlx_pixel_put(t_img_minimap *minimap, int x, int y,
						int color);
void				pixel_put_while(t_img_minimap *minimap, unsigned int w,
						unsigned int h, int color);
void				set_minimap(t_map *map, t_img_minimap *minimap);
void				draw_map(t_map *map);
void				init_img(t_map *map);
void				get_map_line_max(t_map *map);
int					get_pixel_size(t_map *map);

void				set_texture(t_map *map);
int					raycasting(t_map *map);
void				set_player(t_player *player);

void				reset_buffer(int **buffer);
void				set_texture(t_map *map);
void				set_dda_attribute(t_DDA *dda, t_player *player,
						double ray_dir_x, double ray_dir_y);
void				set_dda(t_DDA *dda, t_player *player, double ray_dir_x,
						double ray_dir_y);
void				do_dda(t_DDA *dda, t_map *map);
void				set_draw_info(t_map *map);

int					find_longest_line(t_map *map);
void				check(t_map *map, char **argv);
char				**make_expand_map(t_map *map, int i, int j);
void				set_pro_attri(t_map *map, t_player *player, t_img *img,
						t_DDA *dda);
int					create_rgb(int r, int g, int b);
int					get_pixel_size(t_map *map);
int					set_tex_num(t_map *map, double ray_dir_x, double ray_dir_y);
#endif
