/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:21:50 by epasquie          #+#    #+#             */
/*   Updated: 2023/06/01 13:45:59 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_check_image(t_map *game)
{
	if (!game->mlx->image || !game->mlx->background)
	{
		ft_error("Problem with new_image.\n");
		free_mlx(game);
		free_n_exit(game);
	}
	if (mlx_image_to_window(game->mlx->main, game->mlx->image, 0, 0) == -1
		|| mlx_image_to_window(game->mlx->main, game->mlx->background, 0, 0)
		== -1)
	{
		ft_error("Probem with image_to_window.\n");
		free_mlx(game);
		free_n_exit(game);
	}
}

void	ft_init_mlx(t_map *game)
{
	game->mlx->main = mlx_init(game->size.screen_width,
			game->size.screen_height,
			"Cube3D",
			false);
	if (!game->mlx->main)
	{
		ft_error("mlx_init fatal\n");
		free_n_exit(game);
	}
	game->mlx->image = mlx_new_image(game->mlx->main, game->size.screen_width,
			game->size.screen_height);
	game->mlx->background = mlx_new_image(game->mlx->main,
			game->size.screen_width,
			game->size.screen_height);
	ft_check_image(game);
}

void	ft_affichage(t_map *game)
{
	int		x;
	double	w;

	x = -1;
	w = game->size.screen_width;
	while (++x < w)
	{
		ft_calculate_camera(game, x, w);
		ft_calculate_raydir(game);
		ft_calculate_dda(game);
		ft_calculate_distance(game);
		ft_wich_side(x, game);
	}
}

void	ft_activate(t_map *game)
{
	double	olddirx;
	double	oldplanex;

	olddirx = game->mlx->dirx;
	game->mlx->dirx = game->mlx->dirx * cos(0.01) - game->mlx->diry * sin(0.01);
	game->mlx->diry = olddirx * sin(0.01) + game->mlx->diry * cos(0.01);
	oldplanex = game->mlx->planex;
	game->mlx->planex = game->mlx->planex * cos(0.01) - game->mlx->planey
		* sin(0.01);
	game->mlx->planey = oldplanex * sin(0.01) + game->mlx->planey * cos(0.01);
	game->player.x_pos += game->mlx->dirx * 0.01;
	game->player.y_pos += game->mlx->diry * 0.01;
}

void	ft_game(t_map *game)
{
	ft_init_mlx(game);
	ft_background(game);
	ft_activate(game);
	mlx_loop_hook(game->mlx->main, ft_hook, (void *)game);
	mlx_loop(game->mlx->main);
}
