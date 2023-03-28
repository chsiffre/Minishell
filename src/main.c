/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:20:17 by chsiffre          #+#    #+#             */
/*   Updated: 2023/03/28 15:33:21 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)**argv;
	data.env_path = envp;
	ft_get_env(&data);
	while (1)
	{
		data.line = readline("prompt>");
		if (!ft_strncmp(data.line, "exit", ft_strlen(data.line)))
			break ;
		data.cmd = ft_split(data.line, ' ');
		if (!data.cmd)
			return (1);
		data.cmd[0] = ft_try_path(&data, data.line, data.cmd[0]);
		if (data.line)
			ft_exec(&data, data.cmd);
		free(data.line);
	}
	free(data.line);
	return (0);
}
