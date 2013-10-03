#ifndef CUBE_H_INCLUDED
#define CUBE_H_INCLUDED
#include "common.h"

class cube;

struct field{
	unsigned char width;
	unsigned char height;
	unsigned char depth;

	field(unsigned char, unsigned char, unsigned char);

	GLfloat* getVerticies() const;
	const int getNumVerticies() const;

private:
	int arrlen;
	GLfloat* verticies;
	cube* array;
};

class cube{
	bool mine;

	unsigned char mines;
	bool disp;

public:
	static void addVerticies(GLfloat*, int, int, int, unsigned char);
	static constexpr GLfloat size = 1.f;
	static constexpr char numVerticies = 6*2*3*3;
	static constexpr GLfloat spacing = 0.4f;
	static void cubeSides(unsigned char, int, int, int, GLfloat*);
	static void sidesToVert(GLfloat*, GLfloat*);
	static void vertsToTri(GLfloat*, GLfloat*);
	inline void loadTri(GLfloat*, GLfloat*);
	inline void incrementTri(GLfloat**);
	inline static void loadVert(GLfloat*, float, float, float);
};
	
#endif
