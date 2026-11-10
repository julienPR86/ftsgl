#include "ftsglQuad.h"

t_ftsglQuad	ftsglQuad(t_ftsglVec2 p1, t_ftsglVec2 p2, t_ftsglVec4 col)
{
	t_ftsglQuad	quad = {
		{p1,			col},
		{{p2.x, p1.y},	col},
		{{p1.x, p2.y},	col},
		{p2,			col},
	};

	return (quad);
}
