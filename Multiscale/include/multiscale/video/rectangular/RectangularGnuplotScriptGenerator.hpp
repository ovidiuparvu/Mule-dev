#ifndef RECTANGULARGNUPLOTSCRIPTGENERATOR_HPP_
#define RECTANGULARGNUPLOTSCRIPTGENERATOR_HPP_

#include <vector>
#include <string>

using namespace std;

#define HEADER_IN       "config/video/rectangular/header.in"
#define CONTENT_IN      "config/video/rectangular/content.in"
#define FOOTER_IN       "config/video/rectangular/footer.in"

#define REPLACE_HEADER_FILENAME         "OUTPUT_FILENAME"
#define REPLACE_HEADER_HEIGHT           "OUTPUT_DIMENSION1"
#define REPLACE_HEADER_WIDTH            "OUTPUT_DIMENSION2"
#define REPLACE_HEADER_SIM_TIME         "OUTPUT_SIM_TIME"

#define REPLACE_DIMENSION_EXTRA         0.5

#define OUTPUT_SEPARATOR                " "

#define GNUPLOT_EXTENSION               ".plt"

// Gnuplot script generator from the provided concentrations considering a rectangular geometry

namespace multiscale {

    namespace video {

        class RectangularGnuplotScriptGenerator {

            public:

                static void     generateScript      (const vector<double> &concentrations,
                                                     double simulationTime,
                                                     unsigned long height,
                                                     unsigned long width,
                                                     const string &outputFilepath)
                                                     throw (string);

            private:

                static void     generateHeader      (ofstream &fout, const string &outputFilepath,
                                                     double simulationTime, unsigned long height,
                                                     unsigned long width);
                static void     generateBody        (const vector<double> &concentrations,
                                                     unsigned long height,
                                                     unsigned long width,
                                                     ofstream &fout);
                static void     generateFooter      (ofstream &fout);
                static void     outputHeader        (ifstream &fin,
                                                     const string &outputFilename,
                                                     double simulationTime,
                                                     unsigned long height,
                                                     unsigned long width,
                                                     ofstream &fout);
                static void     outputContent       (const vector<double> &concentrations,
                                                     unsigned long height,
                                                     unsigned long width,
                                                     ofstream &fout);
                static void     outputFooter        (ifstream &fin, ofstream &fout);

        };

    };

};


#endif
