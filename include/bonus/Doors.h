/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Doors.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:43:24 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/25 21:55:59 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOORS_H
# define DOORS_H

# include "Image.h"
# include "Config.h"
# include <stdbool.h>

typedef struct s_door
{
	bool	is_door;
	bool	is_closed;
}	t_door;

typedef struct s_door_states
{
	t_door	*doors;
	t_image	img;
	int		door_count;
	int		map_width;

}	t_door_states;

t_door_states	init_doors(t_config *config, t_game *game);
t_door			*get_door(t_door_states *doors, int x, int y);

#endif
