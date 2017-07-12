#pragma once

#include <iostream>

typedef struct	_GenericImage
{
	uint32_t	width;
	uint32_t	height;
	uint8_t		*data;
	uint32_t	data_size;
	uint32_t	mipMapCount;
	uint32_t	format;
} 				GenericImage;

static void set_bmp_header(FILE *file, unsigned char header[54])
{
	if (fread(header, 1, 54, file) != 54)
		std::cerr << "Incorrect BMP file\n";
	if (header[0]!='B' || header[1] != 'M')
		std::cerr << "Incorrect BMP file\n";
	if (*(int*)&(header[0x1E]) != 0)
		std::cerr << "Incorrect BMP file\n";
	if (*(int*)&(header[0x1C]) != 24)
		std::cerr << "Incorrect BMP file\n";
}

GenericImage load_bmp(const char *path)
{
	t_generic_image	result;
	unsigned char 	header[54];
	unsigned int 	dataPos;
	FILE 			*file;

	std::cout << "Lodaing texture: " << path << std::endl;
	if (!(file = fopen(path, "rb")))
		std::cout << "Could not open texture: " << path << std::endl;
	set_bmp_header(file, header);
	dataPos = *(int*)&(header[0x0A]);
	result.data_size = *(int*)&(header[0x22]);
	result.width = *(int*)&(header[0x12]);
	result.height = *(int*)&(header[0x16]);
	if (result.data_size == 0)
		result.data_size = result.width * result.height * 3;
	if (dataPos == 0)
		dataPos = 54;
	result.data = new uint8_t[result.data_size];
	fread(result.data, 1, result.data_size, file);
	fclose (file);
	return result;
}
