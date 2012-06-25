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
    
    /*
    if(cinfo.progressive_mode) {
    fprintf(stdout, "progressive image: true\n");
    cinfo.buffered_image = false;
    } else {
    fprintf(stdout, "progressive image: false\n");
    }
    */

    int width = cinfo.output_width;
    int height = cinfo.output_height;
    fprintf(stdout, "width: %d , height: %d \n", width, height);

	// Can only handle RGB JPEG images at this stage
	if (cinfo.output_components != 3) {
        fprintf(stderr, "output components != 3\n");	
	    return(1);
	}

	// buffer for one scan line
	row_stride = cinfo.output_width * cinfo.output_components;

  	if ((buffer = (JSAMPLE*) malloc(row_stride * sizeof(JSAMPLE))) == NULL) {
		fprintf(stderr, "malloc failed\n");	
		return(2);
	}

	j = cinfo.output_height-1;

	while (cinfo.output_scanline < cinfo.output_height) {
		n = jpeg_read_scanlines(&cinfo,&buffer,1);
		for (i=0;i<cinfo.output_width;i++) {
			fputc(buffer[3*i], outfile);
			fputc(buffer[3*i+1], outfile);
			fputc(buffer[3*i+2], outfile);
		}
		j--;
	}

	// Finish
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	free(buffer);

	fclose(infile);
	fclose(outfile);

	return(0);
}


int read_JPEG_file(char* filename, char* filename_out) {
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr cError;

  FILE* infile;	
  FILE* outfile;	
  JSAMPARRAY buffer;
  unsigned char* row;
  int row_stride;
  int i;
  int tmp;
  
  cinfo.err = jpeg_std_error(&cError);
  	
  // Open the file
fprintf(stdout, "open files\n");
  infile = fopen(filename, "rb");
  outfile = fopen(filename_out, "wb");
fprintf(stdout, "create decompress\n");
  jpeg_create_decompress(&cinfo);
  jpeg_stdio_src(&cinfo, infile);
  jpeg_read_header(&cinfo, 1);
  jpeg_start_decompress(&cinfo);

  row_stride = cinfo.output_width * cinfo.output_components;
  buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, row_stride, 1);
fprintf(stdout, "read scanlines\n");  		
  jpeg_read_scanlines(&cinfo, buffer, 1);
  
  // print the first row's data of this jpg
  row = buffer[0];
  for(i = 0; i < row_stride; i++) {
    fprintf(stdout, "loop\n");  		
    tmp = row[i];
    fputc(tmp, outfile);
  }
  fprintf(stdout, "finish\n");  		
  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
  fclose(infile);
  fclose(outfile);
  return 1;
}

int main(int argc, char* argv[]) {
	fprintf(stdout, "main called\n");
	char szFileName[] = "/input.jpg";
	char szFileNameOut[] = "/output.bin";
	loadJpg(szFileName, szFileNameOut);
	return 1;
}
