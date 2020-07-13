#include <iostream>
#include <string>
#include "ppm.h"
#include "array2d.h"
#include "Filter.h"
#include "Image.h"
#include "FilterGamma.h"
#include "FilterLinear.h"

using namespace std;
using namespace image;

int main(int argc, char * argv[]) {
	if (argc != 5 && argc != 10) {
		cout << "This program does not support multiple filters, ooops " << endl;
	} else {
		if (strcmp(argv[1], "-f") != 0) {
			cout << "First argument should be -f, ooops " << endl;
		} else {	
			bool is_gamma;
			char * ppm_file = nullptr;

			if (strcmp(argv[2], "gamma") == 0) {
				is_gamma = true;
				ppm_file = argv[4];
			} else if (strcmp(argv[2], "linear") == 0) {
				is_gamma = false;
				ppm_file = argv[9];
			} else {
				cout << "Second argument should be gamma or linear, ooops " << endl;
				return 0;
			}
			

			image::Image origin;

			cout << "Going to read " << ppm_file << endl;

			bool complete = origin.load(ppm_file, "ppm");
			if (!complete) {
				cout << "Filename not found or file does have invalid size" << endl;
				return 0;
			}

			

			if (is_gamma) {
				cout << "Going to apply gamma filter on the image " << endl;
			} else {
				cout << "Going to apply linear filter on the image " << endl;
			}

			Filter * base = nullptr;

			if (is_gamma) {
				float gamma_value = (float) atof(argv[3]);
				base = new FilterGamma(gamma_value);
			} else {

				float ax = (float) atof(argv[3]);
				float ay = (float) atof(argv[4]);
				float az = (float) atof(argv[5]);
				float cx = (float) atof(argv[6]);
				float cy = (float) atof(argv[7]);
				float cz = (float) atof(argv[8]);
				base = new FilterLinear(ax, ay, az, cx, cy, cz);
			}

			if (base !=nullptr) {
				cout << "going to apply filter ... " << endl;

				cout << "Going to write " << ppm_file << endl;

				string resultfilename = "filtered_" + string(ppm_file);

				image::Image final = base->operator<<(origin);
				final.save(resultfilename, "ppm");	
			}					
		}
	}

	system("pause");
	

	return 0;
}