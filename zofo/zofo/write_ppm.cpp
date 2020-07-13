#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ppm.h"

using namespace std;
/*! Writes an image buffer as a PPM file.
*
*  \param data contains the image buffer. The data are RGB float tripplets with values in the range [0,1].
*  \param w is the width of the image in pixels.
*  \param h is the height of the image in pixels.
*  \param filename is the null-terminated string of the name of the file to create.
*
*  \return true if the image save operation was successful, false otherwise. If the data parameter is nulltr, the 
*  function returns immediately with a false return value.
*/
bool image::WritePPM(const float * float_color_row, int w, int h, const char * filename) {
	cout << "WritePPM called " << endl;


	ofstream out(filename, ios::binary);

	// https://www.systutorials.com/131/convert-string-to-int-and-reverse/
	std::string out_string;
	std::stringstream ss;
	ss << w;
	string out_w = ss.str();

	std::string out_string_h;
	std::stringstream ss_h;
	ss_h << h;
	string out_h = ss_h.str();


	if (out.is_open()) {
		char temp[3] = "P6";
		char out_max[4] = "255";
		out << temp;
		out << endl;
		out << out_w;
		out << endl;
		out << out_h;
		out << endl;
		out << out_max;
		out << endl;

		cout << "temp: " << temp << endl;
		cout << "out_w: " << out_w << endl;
		cout << "out_h: " << out_h << endl;
		cout << "out_max: " << out_max << endl << endl;

		cout << "Image width: " << w << endl;
		cout << "Image height: " << h << endl;

		cout << "Image pixels: " << w*h << endl;

		int components = (w)*(h)*3;

		char * color_row = new char[components];					

		for (int i=0;i<components;i++) {
			color_row[i] = (char) (float_color_row[i] * 255);			
		}

		// https://stackoverflow.com/questions/14238572/how-many-bytes-actually-written-by-ostreamwrite
		streamoff before = out.tellp();

		if (out.write(color_row, components)) {  
			streamoff bytes = out.tellp() - before;
			
			if (bytes != components) {
				cout << "incomplete output file " << endl;
				return nullptr;
			}

			cout << "Image written successfully " << bytes <<  " bytes read " << endl;

			delete [] color_row;
				
			out.close();

			return true;
		} else {
			return false;
		}		
	} else {
		return false;
	}	
}
