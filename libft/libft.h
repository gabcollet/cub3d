/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 10:38:52 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/06 13:38:54 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
	int				pos;
}					t_dlist;

/* verification */
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isint(char *str);
int			ft_isllong(char *str);
int			ft_isprint(int c);

/* conversion data type */
double		ft_atof(const char *str);
int			ft_atoi(const char *nptr);
long		ft_atol(const char *nptr);
long long	ft_atoll(const char *nptr);
char		*ft_itoa(int n);
int			ft_tolower(int c);
int			ft_toupper(int c);

/* memory manipulation */
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memccpy(void *dest, const void *src, int c, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		*ft_free(void *ptr);

/* writing */
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);

/* string manipulation */
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoin_free_s1(char *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strcpy(char *dst, const char *src);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *s);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char	*big, const char *little, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);

/* matrix manipulation */
void		ft_sort_tab(char **arr);
void		ft_free_tab(char **tab);
void		*ft_free_array(void **ptr, void *(f)(void *));
int			ft_array_size(void **arr);
void		*ft_array_clear(void **ptr, void *(f)(void *));
void		*ft_free(void *ptr);

/* file */
int			get_next_line(char **line, int fd);

/* linked list */
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **alst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **alst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* double linked list */
t_dlist		*dlst_last(t_dlist *lst);
int			dlst_len(t_dlist *lst);
void		dlst_add_back(t_dlist **head, t_dlist *new);
void		dlst_add_front(t_dlist **head, t_dlist *new);
t_dlist		*dlst_new(int content);
t_dlist		*dlst_iter(t_dlist *dlst, void *(iter)(void *), \
			void *(d)(void *));
t_dlist		*dlst_new_node(void *content);
void		*dlst_clear(t_dlist *dlst, void *(d)(void *));
void		*dlst_clear_node(t_dlist **dlst, t_dlist *node, \
			void *(d)(void *));
t_dlist		*dlst_unlink_node(t_dlist **dlst, t_dlist *node);

#endif