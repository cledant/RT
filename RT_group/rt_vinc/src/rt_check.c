/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/29 11:09:00 by vlize             #+#    #+#             */
/*   Updated: 2016/02/29 11:18:51 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_is_object_char(char *str)
{
	if (ft_strcmp(str, "cone") == 0)
		return (1);
	else if (ft_strcmp(str, "torus") == 0)
		return (1);
	else if (ft_strcmp(str, "plane") == 0)
		return (1);
	else if (ft_strcmp(str, "sphere") == 0)
		return (1);
	else if (ft_strcmp(str, "cylinder") == 0)
		return (1);
	else if (ft_strcmp(str, "ellipsoid") == 0)
		return (1);
	else if (ft_strcmp(str, "paraboloid") == 0)
		return (1);
	else if (ft_strcmp(str, "hyperboloid") == 0)
		return (1);
	else if (ft_strcmp(str, "mobius_strip") == 0)
		return (1);
	else if (ft_strcmp(str, "hyperbolic") == 0)
		return (1);
	else if (ft_strcmp(str, "elliptic") == 0)
		return (1);
	return (0);
}

int		ft_is_object(int type)
{
	if (type == SPHERE || type == PLANE)
		return (1);
	if (type == CYLINDER || type == CONE)
		return (1);
	if (type == TORUS || type == HYPERBOLOID)
		return (1);
	if (type == PARABOLOID || type == ELLIPSOID || type == MOBIUS_STRIP)
		return (1);
	return (0);
}

int		ft_end_with_oid(int type)
{
	if (type == HYPERBOLOID)
		return (1);
	if (type == PARABOLOID)
		return (1);
	if (type == ELLIPSOID)
		return (1);
	return (0);
}

void	ft_check_color(int *color)
{
	if (!color)
		return ;
	if (color[0] > 0xFF)
		color[0] = 0xFF;
	else if (color[0] < 0)
		color[0] = 0;
	if (color[1] > 0xFF)
		color[1] = 0xFF;
	else if (color[1] < 0)
		color[1] = 0;
	if (color[2] > 0xFF)
		color[2] = 0xFF;
	else if (color[2] < 0)
		color[2] = 0;
}
