/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_padding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 00:53:13 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/22 01:26:02 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map.h"
#include "libft.h"
#include "Utils.h"
#include <stdlib.h>

static char	*pad_until_max_width(char *row, int width);
static char	*pad_sides(char *row);
static char	**create_padded_layout(size_t size);
static char	*create_padded_row(size_t size);
void		error(const char *msg);

void	pad_borders(t_map *map)
{
	int		y;
	char	**padded_layout;

	y = 0;
	while (y < map->height)
	{
		if ((int)ft_strlen(map->layout[y]) != map->width)
			map->layout[y] = pad_until_max_width(map->layout[y], map->width);
		map->layout[y] = pad_sides(map->layout[y]);
		y++;
	}
	map->width += 2;
	map->height += 2;
	padded_layout = create_padded_layout(map->height);
	padded_layout[0] = create_padded_row(map->width);
	padded_layout[map->height - 1] = create_padded_row(map->width);
	y = 1;
	while (y < map->height - 1)
	{
		padded_layout[y] = map->layout[y - 1];
		y++;
	}
	free(map->layout);
	map->layout = padded_layout;
}

static char	*pad_until_max_width(char *row, int width)
{
	char	*padded_row;
	int		row_len;
	int		x;

	padded_row = xmalloc(sizeof (*padded_row) * width);
	row_len = ft_strlen(row);
	x = 0;
	while (x < row_len)
	{
		padded_row[x] = row[x];
		x++;
	}
	while (x < width)
	{
		padded_row[x] = ' ';
		x++;
	}
	free(row);
	return (padded_row);
}

static char	*pad_sides(char *row)
{
	int		x;
	int		width;
	char	*padded_row;

	x = 1;
	width = ft_strlen(row);
	padded_row = xmalloc(sizeof (*padded_row) * (width + 2));
	padded_row[0] = ' ';
	padded_row[width + 1] = ' ';
	while (x < width + 1)
	{
		padded_row[x] = row[x - 1];
		x++;
	}
	free(row);
	return (padded_row);
}

static char	**create_padded_layout(size_t size)
{
	char	**padded_layout;

	padded_layout = xmalloc(sizeof (*padded_layout) * (size));
	return (padded_layout);
}

static char	*create_padded_row(size_t size)
{
	char	*padded_row;

	padded_row = xmalloc(sizeof (*padded_row) * size);
	ft_memset(padded_row, ' ', size);
	return (padded_row);
}
