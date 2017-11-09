/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_alpha.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddufour <ddufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 14:47:49 by ddufour           #+#    #+#             */
/*   Updated: 2017/04/04 15:22:21 by ddufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	get_alpha(int shadow, double a)
{
	double alpha;

	if (shadow == 1)
		alpha = (1 / a > 0.8) ? 0.8 : 1 / a;
	else
		alpha = 1;
	return (alpha);
}
