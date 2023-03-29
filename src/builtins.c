/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:22:48 by luhumber          #+#    #+#             */
/*   Updated: 2023/03/29 13:14:12 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_builtins(t_data *data)
{
	if (!ft_strncmp(data->cmd[0], "exit", ft_strlen(data->cmd[0])))
		exit(1);
}
