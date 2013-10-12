#ifndef CUBE_H_INCLUDED
#define CUBE_H_INCLUDED
#include "common.h"


class cube{
	bool mine;

	unsigned char mines;
	bool disp;

public:
	static void addVerticies(GLfloat*, int, int, int, unsigned char);
	static constexpr GLfloat size = .1f;
	static const std::size_t numBytesCube = 6*2*3*3;
	static constexpr GLfloat spacing = 0.4f;
	static void cubeSides(unsigned char, int, int, int, GLfloat*);
	static void sidesToVert(GLfloat*, GLfloat*);
	static void vertsToTri(GLfloat*, GLfloat*);
	inline static void loadTri(GLfloat*, GLfloat*, GLfloat*, GLfloat*);
	inline static void incrementTri(GLfloat**);
	inline static void loadVert(GLfloat*, float, float, float);
};

struct field{
	unsigned char width;
	unsigned char height;
	unsigned char depth;

	field(unsigned char, unsigned char, unsigned char);

	void genVerticies();
	void freeVerticies();
	const GLfloat* getVerticies() const;

	std::size_t vertexArraySize(){return arrlen * cube::numBytesCube;};
	
private:
	int arrlen;
	GLfloat* verticies;
	cube* array;
};

#endif