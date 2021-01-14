#include "Render_Utils.h"

#include <algorithm>

#include "glew.h"
#include "freeglut.h"

void Core::DrawVertexArray(const float * vertexArray, int numVertices, int elementSize )
{
	glVertexAttribPointer(0, elementSize, GL_FLOAT, false, 0, vertexArray);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, numVertices);
}

void Core::DrawVertexArrayIndexed( const float * vertexArray, const int * indexArray, int numIndexes, int elementSize )
{
	glVertexAttribPointer(0, elementSize, GL_FLOAT, false, 0, vertexArray);
	glEnableVertexAttribArray(0);

	glDrawElements(GL_TRIANGLES, numIndexes, GL_UNSIGNED_INT, indexArray);
}


void Core::DrawVertexArray( const VertexData & data )
{
	int numAttribs = std::min(VertexData::MAX_ATTRIBS, data.NumActiveAttribs);
	for(int i = 0; i < numAttribs; i++)
	{
		glVertexAttribPointer(i, data.Attribs[i].Size, GL_FLOAT, false, 0, data.Attribs[i].Pointer);
		glEnableVertexAttribArray(i);
	}
	glDrawArrays(GL_TRIANGLES, 0, data.NumVertices);
}

void Core::DrawModel( obj::Model * model )
{
	std::cout << "10" << std::endl;
	std::cout << "model: "<<model << std::endl;
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, &model->vertex[0]);
	std::cout << "11" << std::endl;
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, &model->texCoord[0]);
	std::cout << "12" << std::endl;
	glVertexAttribPointer(2, 3, GL_FLOAT, false, 0, &model->normal[0]);
	std::cout << "13" << std::endl;
	glEnableVertexAttribArray(0);
	std::cout << "14" << std::endl;
	glEnableVertexAttribArray(1);
	std::cout << "15" << std::endl;
	glEnableVertexAttribArray(2);
	std::cout << "16" << std::endl;

	unsigned short * tmp = &model->faces["default"][0];
	std::cout << "17" << std::endl;
	glDrawElements(GL_TRIANGLES, model->faces["default"].size(), GL_UNSIGNED_SHORT, tmp);
	std::cout << "18" << std::endl;
}
