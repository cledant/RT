/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:41:57 by cledant           #+#    #+#             */
/*   Updated: 2016/03/09 20:19:51 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_load_texture(t_mlx *e)
{
	int		endian;
	int		bpp;
	int		sizeline;

	endian = 0;
	bpp = 0;
	sizeline = 0;
	e->i_globe = mlx_xpm_file_to_image(e->mlx, "./textures/globe.xpm",
			&e->globe_width, &e->globe_length);
	e->c_globe = mlx_get_data_addr(e->i_globe, &bpp, &sizeline, &endian);
}
