#include <iostream>
#include "jpgd.h"
#include "stb_image.c"
using namespace std;

int main()
{
	//std::cout << "Start decoding\n";
	int width,height,actual_comps;
    unsigned char *pImage_data = jpgd::decompress_jpeg_image_from_file("input.jpg", &width, &height, &actual_comps, 3);
    
    //printf("image resolution: %ix%i, actual comps: %i\n", width, height, actual_comps);

    //stbi_write_tga("output.bin", width, height, actual_comps, pImage_data);
    
    //printf("%s",pImage_data);

	for(int i=0; i<width*height*actual_comps; i++) {
		unsigned char ch = *pImage_data;
        printf("%c", ch);
        pImage_data++;
	}

	/*
    unsigned char ch;
    while(*pImage_data != null) {
        ch = *pImage_data;
        printf("%c", ch);
        pImage_data++;
    }
	*/

	return 0;
}
