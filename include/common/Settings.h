/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:46:31 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/26 05:04:38 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

/******************************** Game ***************************************/
# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 1000
# endif

# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 1000
# endif

# ifndef WINDOW_TITLE
#  define WINDOW_TITLE "cute3D"
# endif

# ifndef TILE_WIDTH
#  define TILE_WIDTH 50
# endif

# ifndef TILE_HEIGHT
#  define TILE_HEIGHT 50
# endif

/******************************** Player *************************************/
# ifndef TURN_SPEED_RADS
//#  define TURN_SPEED_RADS 0.0174533 // 1 degrees
#  define TURN_SPEED_RADS 0.0872665 // 5 degrees
# endif

# ifndef MOUSE_TURN_SPEED_RADS
#  define MOUSE_TURN_SPEED_RADS 0.000872665 // 0.005 degrees
# endif

# ifndef VERTICAL_CAMERA_SPEED
#  define VERTICAL_CAMERA_SPEED 20
# endif

# ifndef PLAYER_SPEED
#  define PLAYER_SPEED 2.0
# endif

# ifndef FIELD_OF_VIEW_ANGLE
#  define FIELD_OF_VIEW_ANGLE 60
# endif

# ifndef PLAYER_TOUCH_MAGNITUDE
#  define PLAYER_TOUCH_MAGNITUDE 25
# endif

/******************************** Minimap ************************************/
# ifndef MINIMAP_SCALE
#  define MINIMAP_SCALE 0.3
# endif

# ifndef MINIMAP_X_OFFSET
#  define MINIMAP_X_OFFSET 10
# endif

# ifndef MINIMAP_Y_OFFSET
#  define MINIMAP_Y_OFFSET 10
# endif

# ifndef MINIMAP_BORDER_THICKNESS
#  define MINIMAP_BORDER_THICKNESS 10
# endif

# ifndef PLAYER_INDICATOR_MAGNITUDE
#  define PLAYER_INDICATOR_MAGNITUDE 25

# endif

/********************************** Cat **************************************/
# ifndef CAT_SPRITE_X_OFFSET
#  define CAT_SPRITE_X_OFFSET 150
# endif

# ifndef CAT_SPRITE_Y_OFFSET
#  define CAT_SPRITE_Y_OFFSET 150
# endif

# ifndef CAT_STANDING_ANIMATION
#  define CAT_STANDING_ANIMATION \
	"textures/white_cat/white_cat_standing_128x128_.xpm"
# endif

# ifndef CAT_WALKING_ANIMATION
#  define CAT_WALKING_ANIMATION \
	"textures/white_cat/white_cat_walking_128x128_.xpm"
# endif

# ifndef CAT_LAYING_ANIMATION
#  define CAT_LAYING_ANIMATION \
	"textures/white_cat/white_cat_laying_128x128_.xpm"
# endif

#endif
