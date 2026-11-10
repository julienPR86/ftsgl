#include "ftsglVector.h"

t_ftsglVec2	ftsglVec2(GLfloat x, GLfloat y)
{
	return ((t_ftsglVec2){x, y});
}

t_ftsglVec3	ftsglVec3(GLfloat x, GLfloat y, GLfloat z)
{
	return ((t_ftsglVec3){x, y, z});
}

t_ftsglVec4	ftsglVec4(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	return ((t_ftsglVec4){x, y, z, w});
}
