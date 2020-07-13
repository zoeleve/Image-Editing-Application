#include <iostream>
#include <fstream>
#include "ppm.h"

using namespace std;
/*! Reads a PPM image file and returns a pointer to a newly allocated float array containing the image data. 
*
* Values in the returned array are in the range [0,1] and for each pixel, three values are stored.
*
*  \param filename is the null-terminated string of the name of the file to open.
*  \param w is the address of an integer parameter to return the width of the image into.
*  \param h is the address of an integer parameter to return the height of the image into.
*  
*  \return a pointer to a new float array of 3 X w X h floats, that contains the image data. 
*  If the reading operation failed the function returns nullptr.
*/
float * image::ReadPPM(const char * filename, int * pw, int * ph ) {
	int maxvalue;

	cout << "ReadPPM called " << endl;

	*pw = 0;
	*ph = 0;

	ifstream in(filename, ios::binary);

	if (in.is_open()) {
		char temp[50];
		in >> temp;
		in >> *pw;
		in >> *ph;
		in >> maxvalue;
		in.get();

		cout << "temp: " << temp << endl;
		cout << "*pw: " << *pw << endl;
		cout << "*ph: " << *ph << endl;
		cout << "maxvalue: " << maxvalue << endl << endl;

		cout << "Starting checks .... " << endl;
		if (strlen(temp) != 2) {
			cout << "First two bytes are not valid " << endl;
			return nullptr;
		}

		if (temp[0] != 'P' || temp[1] != '6') {
			cout << "First two bytes are not valid " << endl;
			return nullptr;
		}

		cout << "First two bytes are P6 " << endl;

		if (maxvalue != 255) {
			cout << "maxvalue is not valid " << endl;
			return nullptr;
		}

		cout << "Max value: " << maxvalue << endl;

		if (*pw < 0 || *ph < 0) {
			cout << "image size is not valid " << endl;
			return nullptr;
		}

		cout << "Image width: " << *pw << endl;
		cout << "Image height: " << *ph << endl;

		cout << "Image pixels: " << (*pw)*(*ph) << endl;

		int components = (*pw)*(*ph)*3;

		char * color_row = new char[components];

		in.read(color_row, components);

		// https://stackoverflow.com/questions/1937408/ifstream-bytes-read
		streamsize bytes = in.gcount();

		if (bytes != components) {
			cout << "incomplete file " << endl;
			return nullptr;
		}

		cout << "Image read successfully " << bytes <<  " bytes read " << endl;

		float * float_color_row = new float[components];

		for (int i=0;i<components;i++) {
			float_color_row[i] = color_row[i]/(float)255;
		}

		delete [] color_row;

		in.close();

		return float_color_row;
	} else {
		return nullptr;
	}
}
