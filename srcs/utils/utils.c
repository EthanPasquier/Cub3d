/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:09:29 by jalevesq          #+#    #+#             */
/*   Updated: 2023/05/31 16:07:33 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_set_1(char **tmp_map, char *map_line, int max, int i)
{
	int	l;
	int	k;

	l = 0;
	k = ft_strlen(map_line) - 1;
	while (l < max)
	{
		tmp_map[i][k] = '2';
		k++;
		l++;
	}
	tmp_map[i][k] = '\0';
}

int	ft_strlen_space(const char *str)
{
	unsigned int	i;

	i = 0;
	while (ft_strchr(" \t", str[i]) != NULL)
		i++;
	return (i);
}

void	ft_set_index_start(t_map *game)
{
	int	i;

	i = 0;
	while (game->map[i] && ft_strnstr(game->map[i], "111",
			ft_strlen(game->map[i])) == NULL)
		i++;
	game->index_start_map = i;
}

void	ft_remove_newline(t_map *game)
{
	char	*tmp_texture;

	tmp_texture = ft_strtrim(game->north_string, "\n\t ");
	free(game->north_string);
	game->north_string = ft_strdup(tmp_texture);
	free(tmp_texture);
	tmp_texture = NULL;
	tmp_texture = ft_strtrim(game->east_string, "\n\t ");
	free(game->east_string);
	game->east_string = ft_strdup(tmp_texture);
	free(tmp_texture);
	tmp_texture = NULL;
	tmp_texture = ft_strtrim(game->west_string, "\n\t ");
	free(game->west_string);
	game->west_string = ft_strdup(tmp_texture);
	free(tmp_texture);
	tmp_texture = NULL;
	tmp_texture = ft_strtrim(game->south_string, "\n\t ");
	free(game->south_string);
	game->south_string = ft_strdup(tmp_texture);
	free(tmp_texture);
	tmp_texture = NULL;
}

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
