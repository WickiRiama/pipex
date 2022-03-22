/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:58:40 by mriant            #+#    #+#             */
/*   Updated: 2022/03/22 16:20:09 by mriant           ###   ########.fr       */
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

char	*ft_get_cmdpath(char *cmd)
{

}

int	main(int ac, char ** av, char ** aenv)
{
	int	i;
	char	**paths;

	(void)av;
	if (ac != 5)
	{
		ft_fprintf(2, "Error\nPipex takes 4 arguments file1 cmd1 cmd2 file2\n");
		return (1);
	}
	paths = ft_get_path(aenv);
	if (!paths)
		return (1);
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