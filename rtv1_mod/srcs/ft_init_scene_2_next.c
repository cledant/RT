/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 09:25:57 by cledant           #+#    #+#             */
/*   Updated: 2016/03/06 18:58:20 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		ft_init_scene_21(t_mlx *e)
{
	t_cylinder	*cyl;
	double		tmp_coord[3];
	double		tmp_vec[3];

	cyl = NULL;
	tmp_coord[0] = -70;
	tmp_coord[1] = -20;
	tmp_coord[2] = 5;
	tmp_vec[0] = 0;
	tmp_vec[1] = 0;
	tmp_vec[2] = 1;
	ft_normalize_vec(&tmp_vec);
	ft_add_obj_26(e, tmp_coord, tmp_vec, cyl);
	tmp_coord[0] = -70;
	tmp_coord[1] = 20;
	tmp_coord[2] = 5;
	tmp_vec[0] = 0;
	tmp_vec[1] = 0;
	tmp_vec[2] = 1;
	ft_normalize_vec(&tmp_vec);
	ft_add_obj_27(e, tmp_coord, tmp_vec, cyl);
	ft_add_obj_29(e);
	ft_add_obj_210(e);
	ft_add_obj_211(e);
	ft_add_obj_212(e);
}

void		ft_init_scene_22(t_mlx *e)
{
	t_cylinder	*cyl;
	double		tmp_coord[3];
	double		tmp_vec[3];

	cyl = NULL;
	ft_add_obj_213(e);
	ft_add_obj_214(e);
	tmp_coord[0] = -20;
	tmp_coord[1] = -20;
	tmp_coord[2] = 5;
	tmp_vec[0] = 0;
	tmp_vec[1] = 0;
	tmp_vec[2] = 1;
	ft_normalize_vec(&tmp_vec);
	ft_add_obj_25(e, tmp_coord, tmp_vec, cyl);
	tmp_coord[0] = -20;
	tmp_coord[1] = 20;
	tmp_coord[2] = 5;
	tmp_vec[0] = 0;
	tmp_vec[1] = 0;
	tmp_vec[2] = 1;
	ft_normalize_vec(&tmp_vec);
	ft_add_obj_28(e, tmp_coord, tmp_vec, cyl);
}
