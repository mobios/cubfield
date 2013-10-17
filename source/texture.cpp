#include "texture.h"

BMP_IMG::BMP_IMG(){
	header = new BMP_HEADER;
}

BMP_IMG::~BMP_IMG(){
	delete header;
}

bool BMP_IMG::load(const char* path){
	fstream bitmap = fstream(path);
	bitmap.read((char*)header, 18);
	bitmap.read((char*)header+18, header->headerSize-18);
	if(width || height == 0)
		return false;
	if(header->dataSize == 0)
		dataSize = width * height * 3;
	
	if(dataOffset == 0)
		dataOffset = 54;
	
	data = new char[dataSize];
	bitmap.read(data, dataSize);
}

texture::texture(){
	genTexture();
};

void texture::genTexture(){
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
};

void pack(const image* reference){
	glTexImage2D(	GL_TEXTURE_2D, 0, GL_RGB, reference->getWidth(), reference->getHeight(),
					0, GL_BGR, GL_UNSIGNED_BYTE, reference->getData());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
}