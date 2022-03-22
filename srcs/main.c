/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:58:40 by mriant            #+#    #+#             */
/*   Updated: 2022/03/22 16:05:31 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

char	**ft_get_path(char **aenv)
{
	char	**result;
	int		i;

	i = 0;
	while (ft_strncmp(aenv[i], "PATH=", 5) != 0)
		i++;
	result = ft_split(aenv[i] + 5, ':');
	return (result);
}


int	main(int ac, char ** av, char ** aenv)
{
	int	i;
	char	**paths;

	(void)ac;
	(void)av;
	paths = ft_get_path(aenv);
	i = 0;
	while (paths[i])
	{
		ft_printf("%s\n", paths[i]);
		free(paths[i]);
		i++;
	}
	free(paths);
	return (0);
}