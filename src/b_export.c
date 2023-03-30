/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 13:22:51 by luhumber          #+#    #+#             */
/*   Updated: 2023/03/30 14:59:24 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_export(t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	
}

void	ft_export(t_data *data, char *name)
{
	if (!data->cmd[1])
		ft_print_export(data);
}
