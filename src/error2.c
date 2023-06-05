/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:25:53 by luhumber          #+#    #+#             */
/*   Updated: 2023/06/05 14:35:07 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_special_char(char *cmd)
{
	char	*join;
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != '.' && cmd[i] != '/')
			return (0);
		i++;
	}
	if (cmd[0] == '/')
	{
		join = ft_strjoin("bash: ", cmd);
		join = ft_strjoin(join, ": is a directory\n");
		write(2, join, ft_strlen(join));
		free(join);
	}
	else if (cmd[0] == '.')
		ft_cmd_error(cmd);
	return (1);
}

int	ft_export_error(char *str)
{
	char	*join;

	join = ft_strjoin("bash: export: '", str);
	join = ft_strjoin(join, "' not a valid indentifier\n");
	write(2, join, ft_strlen(join));
	free(join);
	return (1);
}

void	ft_rl_error(t_data *data)
{
	ft_to_free(data);
	printf("exit\n");
	ft_free_for_end(data);
	exit(1);
}
