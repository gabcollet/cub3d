/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_time.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:07:49 by sfournie          #+#    #+#             */
/*   Updated: 2022/01/14 13:44:05 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_TIME_H
# define CUB3D_TIME_H
# include	<sys/time.h>

typedef struct timeval		t_time;

long long	time_to_long(t_time time);
long long	get_cur_time(void);
long long	get_time_between(t_time early, t_time later);
double		get_frame_time(void);
#endif                                                        