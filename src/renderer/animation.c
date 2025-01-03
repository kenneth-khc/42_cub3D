/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:01:21 by kecheong          #+#    #+#             */
/*   Updated: 2025/01/03 17:32:04 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animation.h"

t_animation	animation(t_game *game,
		const char *img1_filename, const char *img2_filename)
{
	t_animation	anim;

	load_image(game, &anim.frames[0], img1_filename);
	load_image(game, &anim.frames[1], img2_filename);
	anim.frame_count = 2;
	anim.frame_index = 0;
	anim.ticks = 0;
	anim.ticks_to_advance = 10;
	return anim;
}

t_image	*get_current_frame(t_animation *animation)
{
	animation->ticks++;
	if (animation->ticks >= animation->ticks_to_advance)
	{
		animation->ticks = 0;
		animation->frame_index++;
		animation->frame_index %= animation->frame_count;
	}
	return &animation->frames[animation->frame_index];
}
