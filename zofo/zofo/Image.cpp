#include <iostream>
#include "Image.h"
#include "ppm.h"

using namespace std;

/*!
* Loads the image data from the specified file, if the extension of the filename matches the format string.
*
* Only the "ppm" extension is supported for now. The extension comparison should be case-insensitive. 
*
* \param filename is the string of the file to read the array data from.
* \param format specifies the file format according to which the array data should be decoded from the file.
* Only the "ppm" format is a valid format string for now.
*
* \return true if the loading completes successfully, false otherwise.
*/

bool image::Image::load(const std::string & filename, const std::string & format) {
	const char * ppm_file = filename.c_str();

	if (format != "ppm" && format != "PPM") {
		return false;
	}

	int w = 0, h = 0;

	float * data = image::ReadPPM(ppm_file, &w, &h);

	if (data == nullptr || w == 0 || h == 0) {
		cout << "Filename not found or file does have invalid size" << endl;
		return false;
	}

	int data_size = w*h*3;

	int loops = data_size/3; // w*h
	
	buffer.clear();

	buffer.resize(w*h);

	this->width = w;
	this->height = h;

	for (int ii=0;ii<loops;ii++) {
		buffer[ii].r = data[ii*3];
		buffer[ii].g = data[ii*3 + 1];
		buffer[ii].b = data[ii*3 + 2];
	}

	delete [] data;

	return true;
}

/*!
* Stores the image data to the specified file, if the extension of the filename matches the format string.
*
* Only the "ppm" extension is supported for now. The extension comparison should be case-insensitive. 
*
* \param filename is the string of the file to write the array data to.
* \param format specifies the file format according to which the array data should be encoded to the file.
* Only the "ppm" format is a valid format string for now.
*
* \return true if the save operation completes successfully, false otherwise.
*/
bool image::Image::save(const std::string & filename, const std::string & format) {
	const char * ppm_file = filename.c_str();

	if (format != "ppm" && format != "PPM") {
		return false;
	}

	float * data = new float[ getWidth()*getHeight()*3];

	for (unsigned int i =0;i<getWidth()*getHeight()*3;i=i+3) {
		data[i] = buffer[i/3].r;
		data[i+1] = buffer[i/3].g;
		data[i+2] = buffer[i/3].b;
	}
	
	image::WritePPM(data, getWidth(), getHeight(), ppm_file);

	delete [] data;

	return true;
}
