/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:56:19 by mriant            #+#    #+#             */
/*   Updated: 2022/03/24 12:01:40 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pipex.h"

void	ft_clean_array(char	**s_array)
{
	int	i;

	if (!s_array)
		return ;
	i = 0;
	while (s_array[i])
	{
		free(s_array[i]);
		i++;
	}
	free(s_array);
}