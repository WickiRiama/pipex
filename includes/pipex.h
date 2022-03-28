/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:03:50 by mriant            #+#    #+#             */
/*   Updated: 2022/03/28 13:18:34 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

void	ft_clean_array(char	**s_array);
void	ft_error(char *error, char **cmd[2]);
void	ft_parse_all(char **cmd[2], int fd_file[2], char **av, char **aenv);

#endif
