/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:12:25 by lucas             #+#    #+#             */
/*   Updated: 2023/04/06 13:43:14 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_redirection(t_data *data)
{
	
}

void	ft_check_cmd(t_data *data)
{
	t_lst	tmp;

	tmp = data->lst;
	while (tmp)
	{
		if (tmp->type == 0)
			ft_redirection();
		else if (tmp->type == 1)
			ft_command();
		else if (tmp->type == 2)
			ft_pipe();
		else if (tmp->type == 3)
			ft_builtins();
	}
}
