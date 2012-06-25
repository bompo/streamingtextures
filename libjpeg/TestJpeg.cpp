#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jpeglib.h"

int loadJpg(char* filename, char* filename_out){
    int i,j,n;
    int row_stride;
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    JSAMPLE *buffer;

    FILE* infile;	
    FILE* outfile;	

    // Open the file
    infile = fopen(filename, "rb");
    outfile = fopen(filename_out, "wb");

    // Error handler
    cinfo.err = jpeg_std_error(&jerr);

    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, infile);

    // Read header
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    int width = cinfo.output_width;
    int height = cinfo.output_height;

    fprintf(stdout, "width: %d , height: %d \n", width, height);

    // Can only handle RGB JPEG images at this stage
    if (cinfo.output_components != 3) 
    return(1);

    // buffer for one scan line
    row_stride = cinfo.output_width * cinfo.output_components;
    if ((buffer = (JSAMPLE*) malloc(row_stride * sizeof(JSAMPLE))) == NULL) 
        return(2);

    while (cinfo.output_scanline < cinfo.output_height) {
        jpeg_read_scanlines(&cinfo,&buffer,1);
	fwrite(buffer, 1, cinfo.output_width * 3,outfile);
    }

    // Finish
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    free(buffer);

    fclose(infile);
    fclose(outfile);

   return(0);
}

int main(int argc, char* argv[]) {
	fprintf(stdout, "main called\n");
	char szFileName[] = "/input.jpg";
	char szFileNameOut[] = "/output.bin";
	loadJpg(szFileName, szFileNameOut);
	return 1;
}
