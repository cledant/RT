/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane_material.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 16:22:34 by cledant           #+#    #+#             */
/*   Updated: 2016/03/06 12:41:21 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_plane_material(double amb, double diff, double spec, t_plane *plane)
{
	plane->diffuse = diff;
	plane->ambiant = amb;
	plane->specular = spec;
}
