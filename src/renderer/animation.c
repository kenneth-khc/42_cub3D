/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:01:21 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/14 02:51:35 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"
#include "Animation.h"
#include "Renderer.h"

t_animation	animation(t_game *game, const char *img_name)
{
	int			i;
	t_animation	anim;
	char		*frame_filename;
	char		*num;

	i = 0;
	num = ft_itoa(i);
	frame_filename = ft_strjoin_multiple(3, img_name, num, ".xpm");
	free(num);
	while (open(frame_filename, O_RDONLY) != -1)
	{
		i++;
		num = ft_itoa(i);
		free(frame_filename);
		frame_filename = ft_strjoin_multiple(3, img_name, num, ".xpm");
		free(num);
	}
	anim.frame_count = i;
	anim.frames = malloc(anim.frame_count * sizeof(t_image));
	i--;
	while (i >= 0)
	{
		num = ft_itoa(i);
		frame_filename = ft_strjoin_multiple(3, img_name, num, ".xpm");
		free(num);
		load_image(game, &anim.frames[i], frame_filename);
		free(frame_filename);
		i--;
	}
	anim.frame_index = 0;
	anim.ticks = 0;
	anim.ticks_to_advance = 1;
	return (anim);
}

void	advance_animations(t_renderer *renderer, t_animation animations[4])
{
	renderer->textures[NORTH] = *get_current_frame(&animations[NORTH]);
	renderer->textures[WEST] = *get_current_frame(&animations[WEST]);
	renderer->textures[EAST] = *get_current_frame(&animations[EAST]);
	renderer->textures[SOUTH] = *get_current_frame(&animations[SOUTH]);
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
	return (&animation->frames[animation->frame_index]);
}
