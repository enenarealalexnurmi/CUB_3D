/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 07:25:02 by enena             #+#    #+#             */
/*   Updated: 2022/01/08 18:51:05 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handling_bonus.h"

void	free_resolution(void *plink)
{
	t_setting_link	*link;

	link = plink;
	link->get = ft_sec_free(link->get);
}

void	free_image(void *plink)
{
	t_setting_link	*link;

	link = plink;
	mlx_destroy_image(((t_game_master *)link->backlink)->mlx,
		((t_image *)link->get)->img);
	((t_image *)link->get)->img = NULL;
	((t_image *)link->get)->addr = NULL;
}

void	free_color(void *plink)
{
	t_setting_link	*link;

	link = plink;
	link->get = ft_sec_free(link->get);
}

void	free_matrix(char **mtrx, ssize_t count_row)
{
	ssize_t	i;

	i = -1;
	while (++i <= count_row)
		mtrx[i] = ft_sec_free(mtrx[i]);
	mtrx = ft_sec_free(mtrx);
}

void	free_anime(void *plink)
{
	t_setting_link	*link;
	size_t			i;

	link = plink;
	i = 0;
	while (i < ((t_anime *)link->get)->count)
	{
		mlx_destroy_image(((t_game_master *)link->backlink)->mlx,
			(((t_anime *)link->get)->anime[i])->img);
		(((t_anime *)link->get)->anime[i])->img = NULL;
		(((t_anime *)link->get)->anime[i])->addr = NULL;
		i++;
	}
}
