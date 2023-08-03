/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:00:03 by lucas             #+#    #+#             */
/*   Updated: 2023/08/03 15:56:05 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	empty_echo(t_data *data)
{
	if (!data->iterator->content[1])
	{
		printf("\n");
		return (1);
	}
	else if (ft_compare_str(data->iterator->content[1], "-n")
		&& !data->iterator->content[2])
		return (1);
	return (0);
}

void	ft_echo(t_data *data)
{
	char	*ret;
	int		i;
	int		option;

	i = 0;
	ret = "";
	if (empty_echo(data) == 1)
		return ;
	if (ft_compare_str(data->iterator->content[1], "-n"))
	{
		option = 1;
		i++;
	}
	else
		option = 0;
	while (data->iterator->content[++i])
		ret = new_join(ret, data->iterator->content[i], data->res_split[i]);
	if (option == 1)
		printf("%s", ret);
	else
		printf("%s\n", ret);
	free(ret);
	g_error_last = 0;
}
