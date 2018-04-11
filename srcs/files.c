/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumont- <ydumont-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 15:48:23 by ydumont-          #+#    #+#             */
/*   Updated: 2018/04/11 05:39:35 by nlt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

#include <stdlib.h>

void			freefile(t_file *file)
{
	free(file->path);
	free(file->name);
	free(file);
}

void			freetab(t_file **files)
{
	int		i;

	i = 0;
	while (files[i])
		freefile(files[i++]);
	free(files);
}

t_file			*getfile(char *p, char *n)
{
	t_file		*file;
	t_s			stat;
	char		*tmp;

	tmp = 0;
	if (!(file = malloc(sizeof(t_file)))
	|| !(tmp = ft_strjoin(p, n))
	|| lstat(tmp, &stat))
	{
		file ? free(file) : 0;
		tmp ? free(tmp) : 0;
		return (0);
	}
	file->path = ft_strdup(p);
	file->name = ft_strdup(n);
	file->stat = stat;
	free(tmp);
	return (file);
}

t_file			**insert(t_file **files, t_file *file, unsigned int o)
{
	t_file		**nfiles;
	int			i;
	int			l;

	l = 0;
	while (files[l])
		l++;
	if (!(nfiles = malloc(sizeof(t_file*) * (l + 2))))
		return (0);
	nfiles[l + 1] = 0;
	i = 0;
	while (i <= l)
	{
		if (file && (!files[i] || !cmp(file, files[i], o)) &&
		(nfiles[i] = file))
			file = 0;
		else
			nfiles[i] = files[i - (!file)];
		i++;
	}
	free(files);
	return (nfiles);
}
