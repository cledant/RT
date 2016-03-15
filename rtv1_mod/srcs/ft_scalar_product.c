/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scalar_product.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 09:30:27 by cledant           #+#    #+#             */
/*   Updated: 2016/03/06 12:41:43 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_scalar_product(double v1[3], double v2[3], double (*res)[3])
{
	double	tmp[3];

	tmp[0] = v1[1] * v2[2] - v1[2] * v2[1];
	tmp[1] = v1[2] * v2[0] - v1[0] * v2[2];
	tmp[2] = v1[0] * v2[1] - v1[1] * v2[0];
	(*res)[0] = tmp[0];
	(*res)[1] = tmp[1];
	(*res)[2] = tmp[2];
}
