#include "Model.h"

Model :: Model()
{
	vertex = vertexNorm = nullptr;
	FaceV = FaceT = FaceN = nullptr;
	vert_sha = nullptr;
	frag_sha = nullptr;
}

Model :: Model( const char* obj )
{
	
}