/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animation.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:57:35 by kecheong          #+#    #+#             */
/*   Updated: 2025/01/03 17:13:58 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATION_H
# define ANIMATION_H

# include "Image.h"

typedef struct s_animation
{
	t_image	*frames; // array of frames
	int		frame_count; // number of frames
	int		frame_index; // which frame we are currently using
	int		ticks; // accumulating number of ticks
	int		ticks_to_advance; // number of ticks to swap to next frame
	t_vec2i	pos; // where the animation should be placed onto
}	t_animation;

typedef struct s_renderer	t_renderer;

t_animation	animation(t_game *game, const char *img1_filename);
void		destroy_animation(void *mlx, t_animation *animation);
int			count_animation_frames(const char *filename);
char		*extract_xpm_filename(const char *full_filename);
t_image		*advance_frame(t_animation *animation);
void		advance_animations(t_renderer *renderer, t_animation animations[4]);
void		put_animation_onto_img(t_animation *animation, t_image *img);

#endif
