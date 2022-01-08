/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_init_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:51:01 by enena             #+#    #+#             */
/*   Updated: 2022/01/08 18:44:44 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialization_bonus.h"

static void	init_key(t_key *key, int keycode, t_key_react react, t_bool lockbl)
{
	key->status = released;
	key->code = keycode;
	key->react = react;
	key->lockable = lockbl;
	key->reacted = false;
}

t_bool	keys_init(t_keys **keys)
{
	t_keys		*tmp;

	tmp = NULL;
	tmp = malloc(sizeof(t_keys));
	if (!(tmp))
		return (error_handler(err_alloc_fail));
	tmp->any_is_pressed = false;
	tmp->key = NULL;
	tmp->key = malloc((CNT_KEY_REACT) * sizeof(t_key));
	if (!(tmp->key))
		return (error_handler(err_alloc_fail));
	init_keys_group_1(tmp->key);
	init_keys_group_2(tmp->key);
	*keys = tmp;
	return (true);
}

void	init_keys_group_1(t_key *keys)
{
	init_key(&keys[w], 13, &move_forward, false);
	init_key(&keys[a], 0, &strafe_left, false);
	init_key(&keys[s], 1, &move_backward, false);
	init_key(&keys[d], 2, &strafe_right, false);
	init_key(&keys[left], 123, &rotate_counter_clock, false);
	init_key(&keys[right], 124, &rotate_clockwise, false);
	init_key(&keys[esc], 53, &exit_ok, true);
}

void	init_keys_group_2(t_key *keys)
{
	init_key(&keys[e], 14, &action, true);
	init_key(&keys[m], 46, &use_map, true);
	init_key(&keys[up], 125, &look_up, false);
	init_key(&keys[down], 126, &look_down, false);
}
