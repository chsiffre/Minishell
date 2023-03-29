/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:22:48 by luhumber          #+#    #+#             */
/*   Updated: 2023/03/29 11:27:54 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_builtins(t_data *data)
{
	if (!ft_strncmp(data->line, "exit", ft_strlen(data->line)))
		exit(1);
}
