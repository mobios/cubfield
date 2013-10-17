#include "common.h"
#include <fstream>

struct image{
	virtual bool load(const char*)=0;
	virtual std::size_t getSize()=0;
	virtual std::size_t getHeight()=0;
	virtual std::size_t getWidth()=0;
	
	virtual unsigned char* getData()=0;
	bool load(const std::string str){return load(str.c_str());};
	
private:
	unsigned char* data;
}

struct BMP_HEADER;

struct BMP_IMG: public image{
	BMP_IMG();
	~BMP_IMG();
	bool load(const char*);
	std::size_t getSize();
	unsigned char * 
private:
	BMP_HEADER* header;
}

struct __attribute__ ((__packed__)) BMP_HEADER{
private:
	BMP_HEADER();
	unsigned char magic[2];
	unsigned int fileSize;
	unsigned int reserved;
	unsigned int dataOffset;
	unsigned int headerSize;
	unsigned int width;
	unsigned int height;
	unsigned short colorPlane;
	unsigned short bitsPerPixel;
	unsigned int compression;
	unsigned int dataSize;
	char unused[4*4];
	friend BMP_IMG;
}

class texture: public glClass{
	GLuint textureID;
	
public:
	texture();
	void genTexture();
	void pack(const image*);
	const GLuint getID() const;
};
	