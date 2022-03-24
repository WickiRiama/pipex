/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:03:50 by mriant            #+#    #+#             */
/*   Updated: 2022/03/24 11:58:55 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

int		ft_parse_cmd(char **cmd1, char **cmd2, char **aenv);
void	ft_clean_array(char	**s_array);

#endif