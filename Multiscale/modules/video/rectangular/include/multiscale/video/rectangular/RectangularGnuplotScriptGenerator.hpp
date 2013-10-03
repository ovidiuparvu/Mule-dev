#ifndef RECTANGULARGNUPLOTSCRIPTGENERATOR_HPP
#define RECTANGULARGNUPLOTSCRIPTGENERATOR_HPP

#include <vector>
#include <string>

using namespace std;


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

            private:

                // Constants
                static const string HEADER_IN;
                static const string CONTENT_IN;
                static const string FOOTER_IN;

                static const string REPLACE_HEADER_FILENAME;
                static const string REPLACE_HEADER_HEIGHT;
                static const string REPLACE_HEADER_WIDTH;
                static const string REPLACE_HEADER_SIM_TIME;

                static const double REPLACE_DIMENSION_EXTRA;

                static const string OUTPUT_SEPARATOR;

                static const string GNUPLOT_EXTENSION;


        };

    };

};


#endif
