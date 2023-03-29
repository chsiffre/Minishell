/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:22:48 by luhumber          #+#    #+#             */
/*   Updated: 2023/03/29 14:26:57 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_builtins(t_data *data)
{
	int	i;

	i = 0;
	if (!ft_strncmp(data->cmd[0], "exit", ft_strlen(data->cmd[0])))
		exit(1);
	if (!ft_strncmp(data->cmd[0], "env", ft_strlen(data->cmd[0])))
	{
		while (data->env_path[i])
			printf("%s\n", data->env_path[i++]);
		return (NULL);
	}
	return (data->cmd[0]);
}
