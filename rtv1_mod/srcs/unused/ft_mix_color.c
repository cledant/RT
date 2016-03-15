/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mix_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 19:53:57 by cledant           #+#    #+#             */
/*   Updated: 2016/02/25 20:17:24 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_mix_color(int color1, int color2, double ratio1)
{
	int		split_color1[4];
	int		split_color2[4];
	double	ratio2;	
	
	ratio2 = 1 - ratio1;
	split_color1[0] = color1 & 0xFF000000;
	split_color1[0] = split_color1[0] >> (4 * 6);
	split_color1[0] = split_color1[0] * ratio1;
	split_color1[0] = split_color1[0] << (4 * 6);
	split_color1[1] = color1 & 0x00FF0000;
	split_color1[1] = split_color1[1] >> (4 * 4);
	split_color1[1] = split_color1[1] * ratio1;
	split_color1[1] = split_color1[1] << (4 * 4);
	split_color1[2] = color1 & 0x0000FF00;
	split_color1[2] = split_color1[2] >> (4 * 2);
	split_color1[2] = split_color1[2] * ratio1;
	split_color1[2] = split_color1[2] << (4 * 2);
	split_color1[3] = color1 & 0x000000FF;
	split_color1[3] = split_color1[3] * ratio1;
	split_color2[0] = color2 & 0xFF000000;
	split_color2[0] = split_color2[0] >> (4 * 6);
	split_color2[0] = split_color2[0] * ratio2;
	split_color2[0] = split_color2[0] << (4 * 6);
	split_color2[1] = color2 & 0x00FF0000;
	split_color2[1] = split_color2[1] >> (4 * 4);
	split_color2[1] = split_color2[1] * ratio2;
	split_color2[1] = split_color2[1] << (4 * 4);
	split_color2[2] = color2 & 0x0000FF00;
	split_color2[2] = split_color2[2] >> (4 * 2);
	split_color2[2] = split_color2[2] * ratio2;
	split_color2[2] = split_color2[2] << (4 * 2);
	split_color2[3] = color2 & 0x000000FF;
	split_color2[3] = split_color2[3] * ratio2;
	return(split_color1[0] + split_color1[1] + split_color1[2] + split_color1[3] +
		split_color2[0] + split_color2[1] + split_color2[2] + split_color2[3]);
}
