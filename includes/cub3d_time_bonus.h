/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_time_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:07:49 by sfournie          #+#    #+#             */
/*   Updated: 2022/01/30 18:03:03 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_TIME_BONUS_H
# define CUB3D_TIME_BONUS_H
# include	<sys/time.h>

typedef struct timeval		t_time;

long long	time_to_long(t_time time);
long long	get_cur_time(void);
long long	get_time_between(t_time early, t_time later);
double		get_frame_time(void);
#endif                                                        