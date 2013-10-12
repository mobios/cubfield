#include "cube.h"
#include <iostream>

field::field(unsigned char widthParam, unsigned char heightParam, unsigned char depthParam){
	width = widthParam;
	height = heightParam;
	depth = depthParam;
	arrlen = height * width * depth;
	verticies = nullptr;
}

void field::genVerticies(){
	__debug(genVerticies() setup,"...")
	freeVerticies();
	verticies = new GLfloat[vertexArraySize()];
	unsigned long position = 0;
	unsigned char flags = 0;

	if(height % 2 == 1)
		flags =flags | 1;
	if(width % 2 == 1)
		flags = flags | 0b10;
	if(depth % 2 == 1)
		flags = flags | 0b100;
	__debug(Pre cube initialization,"...")
	for(unsigned char iTemp = 0; iTemp< depth; ++iTemp){
		int iEffective = iTemp - depth/2;
		for(unsigned char jTemp = 0; jTemp < width; ++jTemp){
			int jEffective = jTemp - width/2;
			for(unsigned char kTemp = 0; kTemp < height; ++kTemp){
				int kEffective = kTemp - height/2;
				cube::addVerticies(verticies+position*cube::numBytesCube, iEffective, jEffective, kEffective, flags);
				++position;
			}
		}
	}
	__debug(genVerticies return,"...")
}

const GLfloat* field::getVerticies() const{
	return verticies;
}

void field::freeVerticies(){
	if(verticies)
		delete verticies;
	verticies = nullptr;
}

void cube::addVerticies(GLfloat* space, int i, int j, int k, unsigned char flags){
	GLfloat sides[3];
	GLfloat verticies[8*3];
	GLfloat* triangles = space;
	cubeSides(flags, i, j, k, sides);
	sidesToVert(sides, verticies);
	vertsToTri(verticies, space);
}

void cube::cubeSides(unsigned char flags, int iParam, int jParam, int kParam, GLfloat* sides){
	auto i = (float)iParam;
	auto j = (float)jParam;
	auto k = (float)kParam;

	i *= cube::spacing;
	j *= cube::spacing;
	k *= cube::spacing;

	if(flags & 0b1)
		k+=0.5*cube::size;

	if(flags & 0b10)
		j+=0.5*cube::size;

	if(flags & 0b100)
		i+=0.5*cube::size;

	sides[0]=i;
	sides[1]=j;
	sides[2]=k;
}

void cube::loadVert(GLfloat* vert, GLfloat i, GLfloat j, GLfloat k){
	vert[0] = i;
	vert[1] = j;
	vert[2] = k;
}

void cube::sidesToVert(GLfloat* sides, GLfloat* vert){
	GLfloat* vertParam = vert;
	GLfloat i = sides[0];
	GLfloat j = sides[1];
	GLfloat k = sides[2];

	GLfloat iF = i+size;
	GLfloat jF = j+size;
	GLfloat kF = k+size;

	while(true){
		loadVert(vert, i, j, k);
		loadVert(vert+1*3, i, jF, k);
		loadVert(vert+2*3, iF, jF, k);
		loadVert(vert+3*3, iF, j, k);
	
		if(vert != vertParam)
			return;
		k = kF;
		vert += 4*3;
	}
}

void cube::vertsToTri(GLfloat* verts, GLfloat* triangles){
	loadTri(triangles, verts, verts+(1*3), verts+(2*3));
	incrementTri(&triangles);

	loadTri(triangles, verts, verts+(3*3), verts+(2*3));
	incrementTri(&triangles);

	loadTri(triangles, verts, verts+(4*3), verts+(5*3));
	incrementTri(&triangles);

	loadTri(triangles, verts, verts+(1*3), verts+(5*3));
	incrementTri(&triangles);

	loadTri(triangles, verts, verts+(4*3), verts+(7*3));
	incrementTri(&triangles);

	loadTri(triangles, verts, verts+(3*3), verts+(7*3));
	incrementTri(&triangles);

	loadTri(triangles, verts+(6*3), verts+(2*3), verts+(1*3));
	incrementTri(&triangles);

	loadTri(triangles, verts+(6*3), verts+(5*3), verts+(1*3));
	incrementTri(&triangles);
	
	loadTri(triangles, verts+(6*3), verts+(7*3), verts+(3*3));
	incrementTri(&triangles);
	
	loadTri(triangles, verts+(6*3), verts+(2*3), verts+(3*3));
	incrementTri(&triangles);
	
	loadTri(triangles, verts+(6*3), verts+(5*3), verts+(4*3));
	incrementTri(&triangles);
	
	loadTri(triangles, verts+(6*3), verts+(7*3), verts+(4*3));
}


void cube::loadTri(GLfloat* tri, GLfloat* vert0, GLfloat* vert1, GLfloat* vert2){
	tri[0] = vert0[0];
	tri[1] = vert0[1];
	tri[2] = vert0[2];

	tri[3] = vert1[0];
	tri[4] = vert1[1];
	tri[5] = vert1[2];

	tri[6] = vert2[0];
	tri[7] = vert2[1];
	tri[8] = vert2[2];
}

void cube::incrementTri(GLfloat** triPtr){
	*triPtr+=3*3;
}
