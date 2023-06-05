/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:32:35 by jalevesq          #+#    #+#             */
/*   Updated: 2023/06/05 11:10:56 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include <../MLX42/include/MLX42/MLX42.h>
# include "../libft/libft.h"

typedef enum s_enum {
	EAST,
	WEST,
	NORTH,
	SOUTH,
}	t_enum;

typedef struct s_player {
	double		x_pos;
	double		y_pos;
	char		direction;
}	t_player;

typedef struct s_size {
	int	width;
	int	height;
	int	screen_width;
	int	screen_height;
}	t_size;

typedef struct s_getcxpm {
	int	**tab;
}	t_getcxpm;

typedef struct s_game {
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	double		camerax;
	double		raydirx;
	double		raydiry;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		perpwalldist;
	double		olddirx;
	double		oldplanex;
	double		rotspeed;
	int			mapx;
	int			mapy;
	int			hit;
	int			stepx;
	int			stepy;
	int			h;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			side;
	mlx_image_t	*image;
	mlx_image_t	*background;
	mlx_t		*main;
}	t_game;

typedef struct s_texture {
	xpm_t		*all_xpm[4];
	t_getcxpm	get_pixel[4];
}	t_texture;

typedef struct s_map {
	char				**map;
	char				*north_string;
	char				*south_string;
	char				*west_string;
	char				*east_string;
	char				*string_floor_color;
	char				*string_ceilling_color;
	int					rgb_floor;
	int					rgb_ceilling;
	int					index_start_map;
	struct s_game		*mlx;
	struct s_player		player;
	struct s_size		size;
	struct s_texture	*texture;
}	t_map;

// Main Parsing function
bool	ft_check_input(int ac, char *av);
bool	ft_check_map(t_map *game);
bool	ft_check_number(char *str, char check, t_map *game);
bool	ft_check_comma(char *str, char check);
bool	ft_is_map_info(t_map *game);
bool	ft_is_one_player(t_map *game);
int		ft_floor_rgb_to_int(t_map *game);
void	ft_set_index_start(t_map *game);
void	ft_fill_map(t_map *game);
char	**ft_copy_map(char *av);
void	ft_parsing(t_map *game, char **av);
int		ft_fill_struct(t_map *game);
bool	ft_is_close_with_one(t_map *game);
bool	ft_color_texture(t_map *game, int mode);
void	ft_reverse_map(t_map *game);
void	ft_find_player(t_map *game);

// Utils
void	ft_set_1(char **tmp_map, char *map_line, int max, int i);
int		ft_strlen_space(const char *str);
void	ft_set_index_start(t_map *game);
void	ft_remove_newline(t_map *game);
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

// Error Parsing
bool	ft_error_rgb(char check);
bool	ft_error(char *str);
void	ft_error_texture(int count, char *direction);
bool	ft_error_character(char c, int i);

// Free and exit Parsing
void	ft_free_double(char **map);
void	free_n_exit(t_map *game);

// RAYCASTING

void	ft_calculate_camera(t_map *game, int x, double w);
void	ft_calculate_raydir(t_map *game);
void	ft_calculate_dda(t_map *game);
void	ft_calculate_distance(t_map *game);
void	ft_wich_side(int x, t_map *game);
void	ft_drawline(int x, t_map *game, int mode);
void	ft_put_pixel(t_map *game, int mode, int texX, int x);
void	ft_background(t_map *game);
void	ft_hook(void *param);
void	ft_affichage(t_map *game);
void	ft_game(t_map *game);
void	free_mlx(t_map *game);
void	ft_set_dir_spawn(t_map *game);
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

#endif