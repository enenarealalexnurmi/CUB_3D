/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_work_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 03:21:47 by enena             #+#    #+#             */
/*   Updated: 2022/01/08 18:47:38 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_bonus.h"

int	key_press(int keycode, t_keys *keys)
{
	t_key	*key;
	ssize_t	i;

	key = keys->key;
	i = -1;
	while (++i < CNT_KEY_REACT)
	{
		if (key[i].code == keycode)
		{
			key[i].status = pressed;
			keys->any_is_pressed = true;
		}
	}
	return (0);
}

int	key_release(int keycode, t_keys *keys)
{
	t_key	*key;
	t_bool	all_released;
	ssize_t	i;

	key = keys->key;
	all_released = true;
	i = -1;
	while (++i < CNT_KEY_REACT)
	{
		if (key[i].code == keycode)
		{
			key[i].status = released;
			key[i].reacted = false;
		}
		all_released &= key[i].status == released;
	}
	keys->any_is_pressed = !(all_released);
	return (0);
}

int	key_check(t_game_master *gm)
{
	t_key	*key;
	ssize_t	i;

	key = gm->keys->key;
	i = -1;
	while (++i < CNT_KEY_REACT)
	{
		if (key[i].status == pressed)
		{
			if (!key[i].lockable || (key[i].lockable && (!(key[i].reacted))))
			{
				key[i].react(gm);
				key[i].reacted = true;
			}
		}
	}
	return (0);
}
