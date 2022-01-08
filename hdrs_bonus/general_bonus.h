/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 05:13:40 by enena             #+#    #+#             */
/*   Updated: 2022/01/08 17:42:26 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_BONUS_H
# define GENERAL_BONUS_H
# include "libft.h"
# include "defines_bonus.h"
# include "structs_bonus.h"
# include "error_handling_bonus.h"
# include "instruments_bonus.h"
# include "sprite_bonus.h"

int		key_press(int keycode, t_keys *keys);
int		key_release(int keycode, t_keys *keys);
int		key_check(t_game_master *gm);

int		exit_ok(void *pgm);
int		move_forward(void *pgm);
int		move_backward(void *pgm);
int		strafe_right(void *pgm);
int		strafe_left(void *pgm);

int		rotate_counter_clock(void *pgm);
int		rotate_clockwise(void *pgm);

int		action(void *pgm);
int		use_map(void *pgm);
int		look_up(void *pgm);
int		look_down(void *pgm);

void	game(t_game_master *gm);

void	render_frame(t_game_master *gm);
#endif
