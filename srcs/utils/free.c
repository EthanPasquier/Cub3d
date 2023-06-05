/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:10:22 by jalevesq          #+#    #+#             */
/*   Updated: 2023/06/01 09:50:52 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_free_double(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
	map = NULL;
}

void	ft_delete_texture(t_map *game)
{
	if (game->texture->all_xpm[WEST])
		mlx_delete_xpm42(game->texture->all_xpm[WEST]);
	if (game->texture->all_xpm[EAST])
		mlx_delete_xpm42(game->texture->all_xpm[EAST]);
	if (game->texture->all_xpm[NORTH])
		mlx_delete_xpm42(game->texture->all_xpm[NORTH]);
	if (game->texture->all_xpm[SOUTH])
		mlx_delete_xpm42(game->texture->all_xpm[SOUTH]);
}

void	free_mlx(t_map *game)
{
	if (game->mlx->background)
		mlx_delete_image(game->mlx->main, game->mlx->background);
	if (game->mlx->image)
		mlx_delete_image(game->mlx->main, game->mlx->image);
	mlx_close_window(game->mlx->main);
}

void	ft_free_double_int(t_map *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4 && game->texture->get_pixel[i].tab)
	{
		j = 0;
		while (j < (int)game->texture->all_xpm[i]->texture.width)
		{
			free(game->texture->get_pixel[i].tab[j]);
			j++;
		}
		free(game->texture->get_pixel[i].tab);
		game->texture->get_pixel[i].tab = NULL;
		i++;
	}
}

void	free_n_exit(t_map *game)
{
	if (game->east_string)
		free(game->east_string);
	if (game->north_string)
		free(game->north_string);
	if (game->west_string)
		free(game->west_string);
	if (game->south_string)
		free(game->south_string);
	if (game->string_floor_color)
		free(game->string_floor_color);
	if (game->string_ceilling_color)
		free(game->string_ceilling_color);
	if (game->texture->get_pixel[0].tab != NULL)
		ft_free_double_int(game);
	ft_free_double(game->map);
	ft_delete_texture(game);
	free(game->texture);
	free(game->mlx);
	free(game);
	exit(EXIT_SUCCESS);
}
