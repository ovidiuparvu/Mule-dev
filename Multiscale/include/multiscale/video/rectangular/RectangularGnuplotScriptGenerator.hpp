#ifndef RECTANGULARGNUPLOTSCRIPTGENERATOR_HPP
#define RECTANGULARGNUPLOTSCRIPTGENERATOR_HPP

#include <vector>
#include <string>

using namespace std;

const string HEADER_IN       = "config/video/rectangular/header.in";
const string CONTENT_IN      = "config/video/rectangular/content.in";
const string FOOTER_IN       = "config/video/rectangular/footer.in";

const string REPLACE_HEADER_FILENAME    = "OUTPUT_FILENAME";
const string REPLACE_HEADER_HEIGHT      = "OUTPUT_DIMENSION1";
const string REPLACE_HEADER_WIDTH       = "OUTPUT_DIMENSION2";
const string REPLACE_HEADER_SIM_TIME    = "OUTPUT_SIM_TIME";

const double REPLACE_DIMENSION_EXTRA = 0.5;

const string OUTPUT_SEPARATOR    = " ";

const string GNUPLOT_EXTENSION   = ".plt";


namespace multiscale {

    namespace video {

        //! Gnuplot script generator from the provided concentrations considering a rectangular geometry
        class RectangularGnuplotScriptGenerator {

            public:

                //! Generate the script
                /*!
                 * \param concentrations Concentrations
                 * \param simulationTime Simulation time
                 * \param height Height of the grid
                 * \param width Width of the grid
                 * \param outputFilepath Path of the output file
                 */
                static void generateScript(const vector<double> &concentrations,
                                           double simulationTime,
                                           unsigned long height,
                                           unsigned long width,
                                           const string &outputFilepath);

            private:

                //! Generate the header of the script
                /*!
                 * \param fout Output file stream
                 * \param outputFilepath Path to the output file
                 * \param simulationTime Simulation time
                 * \param height Height of the grid
                 * \param width Width of the grid
                 */
                static void generateHeader(ofstream &fout, const string &outputFilepath,
                                           double simulationTime, unsigned long height,
                                           unsigned long width);

                //! Generate the body/content of the script
                /*!
                 * \param concentrations The concentrations
                 * \param height The height of the grid
                 * \param width The width of the grid
                 * \param fout Output file stream
                 */
                static void generateBody(const vector<double> &concentrations,
                                         unsigned long height,
                                         unsigned long width,
                                         ofstream &fout);

                //! Generate the footer of the script
                /*!
                 * \param fout Output file stream
                 */
                static void generateFooter(ofstream &fout);

                //! Output the header of the script
                /*!
                 * \param fin Input file stream
                 * \param outputFilename Name of the output file
                 * \param simulationTime Simulation time
                 * \param height The height of the grid
                 * \param width The width of the grid
                 * \param fout Output file stream
                 */
                static void outputHeader(ifstream &fin,
                                         const string &outputFilename,
                                         double simulationTime,
                                         unsigned long height,
                                         unsigned long width,
                                         ofstream &fout);

                //! Output the content of the script
                /*!
                 * \param concentrations The concentrations
                 * \param height The height of the grid
                 * \param width The width of the grid
                 * \param fout Output file stream
                 */
                static void outputContent(const vector<double> &concentrations,
                                          unsigned long height,
                                          unsigned long width,
                                          ofstream &fout);

                //! Output the footer of the script
                /*!
                 * \param fin Input file stream
                 * \param fout Output file stream
                 */
                static void outputFooter(ifstream &fin, ofstream &fout);

        };

    };

};


#endif
