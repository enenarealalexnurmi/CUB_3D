/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:39:57 by enena             #+#    #+#             */
/*   Updated: 2022/01/08 19:05:56 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_BONUS_H
# define SPRITE_BONUS_H
# include <math.h>
# include "libft.h"
# include "defines_bonus.h"
# include "structs_bonus.h"
# include "error_handling_bonus.h"
# include "instruments_bonus.h"

void	calculate_edge_sprite(t_sprite *sp, int max, int value);
void	improve_quick_sort(t_sprite ***arr, size_t low, size_t high);
void	draw_sprite(t_sprite *sprite, t_ray *rays, t_image *texture,
			t_image *frame);
void	calculate_sprites(t_sprite ***sprites, t_player *pl,
			ssize_t count_s, t_image *frame);

#endif