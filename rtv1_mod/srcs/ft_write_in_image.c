/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_in_image.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 18:11:14 by cledant           #+#    #+#             */
/*   Updated: 2016/03/06 12:42:59 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_write_in_image(int counter[5], t_mlx *e)
{
	ft_memcpy(&counter[4], e->c_img + counter[1] * 4 +
		counter[0] * 4 * WIN_X, sizeof(int));
	counter[4] = ft_add_color(counter[4], counter[2]);
	ft_memcpy(e->c_img + counter[1] * 4 + counter[0] *
		4 * WIN_X, &counter[4], sizeof(int));
}
