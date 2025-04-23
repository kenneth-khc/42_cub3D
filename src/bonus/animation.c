/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:01:21 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/24 02:46:09 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "Animation.h"
#include "Renderer.h"
#include "Utils.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

static t_animation
animate_from_frames(const char *filename, int frame_count, t_game *game);

/* Try creating an Animation. If many frames exist, we load them into an
 * Animation after counting the number of frames. If none can be found, we
 * try loading it as a single Image, however it still goes into an Animation,
 * just that its frame count is set to only 1 and it never changes - a "static
 * Animation", I guess. I suppose this is where polymorphism could be useful. */
t_animation	animation(t_game *game, const char *filepath)
{
	t_animation	anim;
	char		*filename;

	filename = extract_xpm_filename(filepath);
	anim.frame_count = count_animation_frames(filename);
	if (anim.frame_count == 0)
	{
		anim.frames = xmalloc(sizeof(*anim.frames));
		load_image(game, anim.frames, filepath);
		anim.frame_count = 1;
		anim.frame_index = 0;
		anim.ticks = 0;
		anim.ticks_to_advance = 1;
	}
	else
	{
		anim = animate_from_frames(filename, anim.frame_count, game);
	}
	return (anim);
}

void	destroy_animation(void *mlx, t_animation *animation)
{
	int	count;

	count = 0;
	while (count < animation->frame_count)
	{
		destroy_image(mlx, &animation->frames[count]);
		count++;
	}
}

static
t_animation	animate_from_frames(const char *filename, int frame_count,
								t_game *game)
{
	int			num;
	char		*num_suffix;
	char		*frame_filename;
	t_animation	animation;

	animation.frames = xmalloc(sizeof(t_image) * frame_count);
	animation.frame_count = frame_count;
	num = 0;
	while (num < frame_count)
	{
		num_suffix = ft_itoa(num);
		frame_filename = ft_strjoin_multiple(3, filename, num_suffix, ".xpm");
		load_image(game, &animation.frames[num], frame_filename);
		num++;
		free(num_suffix);
		free(frame_filename);
	}
	animation.frame_index = 0;
	animation.ticks = 0;
	animation.ticks_to_advance = 1;
	return (animation);
}

void	advance_animations(t_renderer *renderer, t_animation animations[4])
{
	renderer->wall_textures[NORTH] = *get_current_frame(&animations[NORTH]);
	renderer->wall_textures[WEST] = *get_current_frame(&animations[WEST]);
	renderer->wall_textures[EAST] = *get_current_frame(&animations[EAST]);
	renderer->wall_textures[SOUTH] = *get_current_frame(&animations[SOUTH]);
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
