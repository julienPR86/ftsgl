#ifndef FTSGL_QUAD_H
# define FTSGL_QUAD_H

# include "ftsglVertex.h"

typedef struct s_ftsglQuad
{
	t_ftsglVertex	a;
	t_ftsglVertex	b;
	t_ftsglVertex	c;
	t_ftsglVertex	d;
}	t_ftsglQuad;

t_ftsglQuad	ftsglQuad(t_ftsglVec2 p1, t_ftsglVec2 p2, t_ftsglVec4 col);

#endif
