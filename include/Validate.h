/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Validate.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:30:27 by kytan             #+#    #+#             */
/*   Updated: 2025/03/12 16:43:08 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define FULFILLED 63

void	validate_data_file(t_parse *parser, t_game *game);

void	validate_data_elements_textures(char **file_data, t_game *game);
void	validate_data_elements_map(char **file_data, t_game *game);


int		id_idx(char *id_token, t_game *game);
int		empty_line(char *s);