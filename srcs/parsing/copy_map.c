/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:35:16 by jalevesq          #+#    #+#             */
/*   Updated: 2023/05/31 12:36:45 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	ft_count_line(char *av)
{
	int		fd;
	char	c;
	int		readbytes;
	int		countline;

	fd = open(av, O_RDONLY);
	countline = 1;
	while (1)
	{
		readbytes = read(fd, &c, 1);
		if (readbytes == 0)
			break ;
		if (readbytes < 0)
			return (-1);
		if (c == '\n')
			countline++;
	}
	close(fd);
	return (countline);
}

char	**ft_line_error(int count_line)
{
	if (count_line <= 1)
	{
		write(2, "Error\nMap is empty.\n", 20);
		return (NULL);
	}
	if (count_line <= 7)
	{
		write(2, "Error\nMap is missing information.\n", 34);
		return (NULL);
	}
	return (NULL);
}

char	**ft_copy_map(char *av)
{
	char	**map;
	int		fd;
	int		count_line;
	int		i;

	i = 0;
	count_line = ft_count_line(av);
	if (count_line <= 7)
		return (ft_line_error(count_line));
	map = (char **)malloc(sizeof(char *) * (count_line + 1));
	if (!map)
		return (NULL);
	fd = open(av, O_RDONLY);
	map[i] = get_next_line(fd);
	while (map[i])
	{
		i++;
		map[i] = get_next_line(fd);
	}
	map[i] = NULL;
	close(fd);
	return (map);
}
