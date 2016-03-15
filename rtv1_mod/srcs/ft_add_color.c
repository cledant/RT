/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 14:20:23 by cledant           #+#    #+#             */
/*   Updated: 2016/03/06 12:31:06 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static	int		ft_add_priv(int split_color1[4], int split_color2[4])
{
	int		ret_color[4];

	ret_color[0] = split_color1[0] + split_color2[0];
	if (ret_color[0] > 0xFF)
		ret_color[0] = 0xFF;
	ret_color[1] = split_color1[1] + split_color2[1];
	if (ret_color[1] > 0xFF)
		ret_color[1] = 0xFF;
	ret_color[2] = split_color1[2] + split_color2[2];
	if (ret_color[2] > 0xFF)
		ret_color[2] = 0xFF;
	ret_color[3] = split_color1[3] + split_color2[3];
	if (ret_color[3] > 0xFF)
		ret_color[3] = 0xFF;
	ret_color[0] = ret_color[0] << (4 * 6);
	ret_color[1] = ret_color[1] << (4 * 4);
	ret_color[2] = ret_color[2] << (4 * 2);
	return (ret_color[0] + ret_color[1] + ret_color[2] + ret_color[3]);
}

int				ft_add_color(int color1, int color2)
{
	int		split_color1[4];
	int		split_color2[4];

	split_color1[0] = color1 & 0xFF000000;
	split_color1[0] = split_color1[0] >> (4 * 6);
	split_color1[1] = color1 & 0x00FF0000;
	split_color1[1] = split_color1[1] >> (4 * 4);
	split_color1[2] = color1 & 0x0000FF00;
	split_color1[2] = split_color1[2] >> (4 * 2);
	split_color1[3] = color1 & 0x000000FF;
	split_color2[0] = color2 & 0xFF000000;
	split_color2[0] = split_color2[0] >> (4 * 6);
	split_color2[1] = color2 & 0x00FF0000;
	split_color2[1] = split_color2[1] >> (4 * 4);
	split_color2[2] = color2 & 0x0000FF00;
	split_color2[2] = split_color2[2] >> (4 * 2);
	split_color2[3] = color2 & 0x000000FF;
	return (ft_add_priv(split_color1, split_color2));
}
