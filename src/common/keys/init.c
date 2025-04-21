/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 06:37:05 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/22 06:37:11 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Keys.h"

/* Create a new keybinding, with interest specifying the state of the key
 * to call the function (PRESS or RELEASE) */
t_key	map_key(int interest, enum e_mlx_keycodes mlx_keycode, t_action action)
{
	t_key	new_keybinding;

	new_keybinding.mlx_keycode = mlx_keycode;
	new_keybinding.action = action;
	new_keybinding.state = NONE;
	new_keybinding.interest = interest;
	return (new_keybinding);
}
