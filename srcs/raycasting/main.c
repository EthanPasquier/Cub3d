/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:33:05 by jalevesq          #+#    #+#             */
/*   Updated: 2023/06/05 11:10:39 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_malloc_struct(t_map *game)
{
	game->texture = malloc(sizeof(t_texture));
	if (!game->texture)
	{
		ft_error("Malloc texture struct. no more space on device ?\n");
		free(game);
		exit(EXIT_FAILURE);
	}
	game->mlx = malloc(sizeof(t_game));
	if (!game->mlx)
	{
		ft_error("Malloc mlx struct. no more space on device ?\n");
		free(game->texture);
		free(game);
		exit(EXIT_FAILURE);
	}
}

void	ft_init_texture_n_mlx(t_map *game)
{
	game->texture->all_xpm[EAST] = NULL;
	game->texture->all_xpm[WEST] = NULL;
	game->texture->all_xpm[SOUTH] = NULL;
	game->texture->all_xpm[NORTH] = NULL;
	game->texture->get_pixel[EAST].tab = NULL;
	game->texture->get_pixel[SOUTH].tab = NULL;
	game->texture->get_pixel[WEST].tab = NULL;
	game->texture->get_pixel[NORTH].tab = NULL;
	game->mlx->dirx = -1;
	game->mlx->diry = 0;
	game->mlx->image = NULL;
	game->mlx->background = NULL;
	game->mlx->planex = 0;
	game->mlx->planey = 0.66;
	game->mlx->rotspeed = 0.05;
}

void	ft_init(t_map *game)
{
	game->map = NULL;
	game->east_string = NULL;
	game->north_string = NULL;
	game->south_string = NULL;
	game->west_string = NULL;
	game->string_ceilling_color = NULL;
	game->string_floor_color = NULL;
	game->player.direction = '\0';
	game->player.x_pos = 0;
	game->player.y_pos = 0;
	game->size.height = 0;
	game->size.width = 0;
	game->size.screen_width = 1020;
	game->size.screen_height = 720;
	game->index_start_map = 0;
	ft_init_texture_n_mlx(game);
}

int	main(int ac, char **av)
{
	t_map	*game;

	if (ft_check_input(ac, av[1]) == false)
		return (1);
	game = malloc(sizeof(t_map));
	if (!game)
	{
		ft_error("Malloc game struct. no more space on device ?\n");
		return (1);
	}
	ft_malloc_struct(game);
	ft_init(game);
	ft_parsing(game, av);
	ft_reverse_map(game);
	ft_game(game);
	free_n_exit(game);
}
// printf("\n\n");
// printf("Map design start:%d\n", game->index_start_map);
// for (int i = 0; game->map[i]; i++)
// 	printf("%s\n", game->map[i]);
// printf("\n\nVar get:\nSouth:%s\n", game->south_string);
// printf("North:%s\n", game->north_string);
// printf("West:%s\n", game->west_string);
// printf("East:%s\n", game->east_string);
// printf("Ceilling:%s", game->string_ceilling_color);
// printf("Floor:%s", game->string_floor_color);
// printf("RGB color Floor:%d\n", game->rgb_floor);
// printf("RGB color Ceilling:%d\n", game->rgb_ceilling);
// printf("Player Direction %c\n", game->player.direction);
// printf("Map Width %d\n", game->size.height);
// printf("Map Height %d\n", game->size.height);