/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:09:16 by luhumber          #+#    #+#             */
/*   Updated: 2023/04/03 14:09:05 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_init_data(t_data *data, char **envp)
{
	data->env_path = envp;
	data->env = NULL;
	data->lst = NULL;
	ft_struct_env(data);
}
