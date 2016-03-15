/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_texcolor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 19:01:36 by cledant           #+#    #+#             */
/*   Updated: 2016/03/10 16:17:43 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_get_texcolor_sphere(t_mlx *e, t_sphere *obj, double *norm_vec)
{
	double	tmp_vec[3];
	double	phi;
	double	theta;
	double	u;
	double	v;
	double	x;
	double	y;
	int		color;
	char	*addr;
	double	check;

	norm_vec[0] = -norm_vec[0];
	norm_vec[1] = -norm_vec[1];
	norm_vec[2] = -norm_vec[2];
	/*debut init vecteur orientation texture*/
	obj->north_vec[0] = 0;
	obj->north_vec[1] = 0;
	obj->north_vec[2] = 1;
	ft_normalize_vec(&obj->north_vec);
	if (obj->north_vec[0] == 0 && obj->north_vec[1] == 0 && obj->north_vec[2] > 0)
	{
		obj->equ_vec[0] = 1;
		obj->equ_vec[1] = 0;
		obj->equ_vec[2] = 0;
	}
	else if (obj->north_vec[0] == 0 && obj->north_vec[1] == 0 && obj->north_vec[2] < 0)
	{
		obj->equ_vec[0] = -1;
		obj->equ_vec[1] = 0;
		obj->equ_vec[2] = 0;
	}
	else
	{
		tmp_vec[0] = 0;
		tmp_vec[1] = 0;
		tmp_vec[2] = 1;
		ft_scalar_product(obj->north_vec, tmp_vec, &obj->equ_vec);
		ft_normalize_vec(&obj->equ_vec);
	}
	/*fin init vecteur orientation texture*/
	/*debut calcul angle */
	phi = acos(-ft_dot_product(obj->north_vec, norm_vec));
	theta = (acos(ft_dot_product(norm_vec, obj->equ_vec) / sin(phi))) / (M_PI * 2);
	/*fin calcul angle */
	/*debut calcul position sur texture*/
	v = (double)phi / M_PI;
	ft_scalar_product(obj->north_vec, obj->equ_vec, &tmp_vec);
	if (ft_dot_product(tmp_vec ,norm_vec) > 0)
		u = theta;
	else
		u = 1 - theta;
//	ft_putnbrendl(e->globe_length);
//	ft_putnbrendl(e->globe_width);
	y = (v * e->globe_length);
	x = (u * e->globe_width);
	addr = e->c_globe + (int)round(x) * 4 + (int)round(y) * e->globe_width * 4;
	ft_memcpy(&color, addr, sizeof(int));
	return (color);
}
