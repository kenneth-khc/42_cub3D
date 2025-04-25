/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Doors.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:43:24 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/26 05:10:17 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOORS_H
# define DOORS_H

# include "Vector.h"
# include "Map.h"
# include <stdbool.h>

typedef struct s_door
{
	t_vec2i	tile_pos;
	bool	is_closed;
}	t_door;

typedef struct s_doors
{
	t_door	*ptr;
}	t_doors;

t_doors	init_doors(const t_map *map);
t_door	*get_door(t_doors *doors, int x, int y);
bool	is_open_door(t_vec2d *world_pos, t_doors *doors);
bool	is_closed_door(t_vec2d *world_pos, t_doors *doors);

#endif
