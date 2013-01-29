#ifndef GNUPLOTSCRIPTGENERATOR_HPP_
#define GNUPLOTSCRIPTGENERATOR_HPP_

#include "multiscale/video/circular/AnnularSector.hpp"

#include <vector>

using namespace std;

#define HEADER_IN	 	"config/video/circular/header.in"
#define CONTENT_IN 		"config/video/circular/content.in"
#define FOOTER_IN	 	"config/video/circular/footer.in"

#define LINE_BUF_SIZE	1024

#define REPLACE_HEADER_FILENAME 		"OUTPUT_FILENAME"

#define REPLACE_CONTENT_INDEX			"OBJ_INDEX"
#define REPLACE_CONTENT_RADIUS			"OBJ_END_RADIUS"
#define REPLACE_CONTENT_START_ANGLE 	"OBJ_START_ANGLE"
#define REPLACE_CONTENT_END_ANGLE		"OBJ_END_ANGLE"
#define REPLACE_CONTENT_CONCENTRATION	"OBJ_CONCENTRATION"

#define GNUPLOT_EXTENSION				".plt"

// Gnuplot script generator from the provided annular sectors

namespace multiscale {

	namespace video {

		class GnuplotScriptGenerator {

			public:

				static void		generateScript      (vector<AnnularSector>& annularSectors,
													 string outputFilename)
													 throw (string);

			private:

				static void 	generateHeader		(ofstream& fout, string outputFilename);
				static void 	generateBody  		(vector<AnnularSector>& annularSectors,
													 ofstream& fout);
				static void 	generateFooter		(ofstream& fout);
				static void		outputHeader  		(ifstream& fin, string outputFilename,
													 ofstream& fout);
				static void		outputContent		(vector<AnnularSector>& annularSectors,
													 string& contentTemplate,
													 ofstream& fout);
				static void		outputFooter		(ifstream& fin, ofstream& fout);
				static string	readContentTemplate	(ifstream& fin);

		};

	};

};


#endif
