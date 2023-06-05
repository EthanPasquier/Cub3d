/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:38:31 by jalevesq          #+#    #+#             */
/*   Updated: 2023/06/05 11:07:05 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_set_color(t_map *game, int mode, int *count, int y)
{
	int	x;
	int	color[5];

	x = 0;
	while (x < (int)game->texture->all_xpm[mode]->texture.width)
	{
		color[0] = game->texture->all_xpm[mode]->texture.pixels[*count];
		color[1] = game->texture->all_xpm[mode]->texture.pixels[*count + 1];
		color[2] = game->texture->all_xpm[mode]->texture.pixels[*count + 2];
		color[3] = game->texture->all_xpm[mode]->texture.pixels[*count + 3];
		color[4] = ft_pixel(color[0], color[1], color[2], color[3]);
		game->texture->get_pixel[mode].tab[y][x] = color[4];
		*count += 4;
		x++;
	}
}

bool	ft_while_loop(t_map *game, int mode)
{
	int	y;
	int	count;

	y = 0;
	count = 0;
	while (y < (int)game->texture->all_xpm[mode]->texture.height)
	{
		game->texture->get_pixel[mode].tab[y]
			= malloc(((int)game->texture->all_xpm[mode]->texture.width
					* sizeof(int)));
		if (!game->texture->get_pixel[mode].tab[y])
			return (ft_error("Can't malloc color texture.\n"));
		ft_set_color(game, mode, &count, y);
		y++;
	}
	return (true);
}

bool	ft_color_texture(t_map *game, int mode)
{
	game->texture->get_pixel[mode].tab
		= (int **)malloc(((int)game->texture->all_xpm[mode]->texture.height
				* sizeof(int *)));
	if (!game->texture->get_pixel[mode].tab)
		return (ft_error("Can't malloc color texture.\n"));
	if (ft_while_loop(game, mode) == false)
		return (false);
	mode++;
	if (mode >= 4)
		return (true);
	else
		ft_color_texture(game, mode);
	return (true);
}
