/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:03:50 by mriant            #+#    #+#             */
/*   Updated: 2022/04/11 17:06:03 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

void	ft_clean_all(char ***cmd, int *fd);
void	ft_clean_array(char	***s_array);
void	ft_error(char *error, char ***cmd, int *fd);
void	ft_init_fd(int *fd);
void	ft_parse_cmd(char ***cmd, char **av, char **aenv, int *fd);
void	ft_parse_file(int *fd, char **av);

#endif
