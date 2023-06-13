/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:25:53 by luhumber          #+#    #+#             */
/*   Updated: 2023/06/13 10:50:09 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_special_char(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
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
	write(2, "exit\n", 6);
	ft_free_for_end(data);
	exit(1);
}

void	ft_syntax_error(char *str)
{
	char	*join;

	g_error_last = 2;
	join = ft_strjoin("bash: syntax error near unexpected token ", str);
	write(2, join, ft_strlen(join));
	write(2, "\n", 2);
	free(join);
	return ;
}
