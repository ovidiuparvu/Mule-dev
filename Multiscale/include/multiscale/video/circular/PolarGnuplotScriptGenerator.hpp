#ifndef POLARGNUPLOTSCRIPTGENERATOR_HPP_
#define POLARGNUPLOTSCRIPTGENERATOR_HPP_

#include "multiscale/video/circular/AnnularSector.hpp"

#include <vector>

using namespace std;

#define HEADER_IN       "config/video/circular/header.in"
#define CONTENT_IN      "config/video/circular/content.in"
#define FOOTER_IN       "config/video/circular/footer.in"

#define REPLACE_HEADER_FILENAME         "OUTPUT_FILENAME"
#define REPLACE_HEADER_SIM_TIME         "OUTPUT_SIM_TIME"

#define REPLACE_CONTENT_INDEX           "OBJ_INDEX"
#define REPLACE_CONTENT_RADIUS          "OBJ_END_RADIUS"
#define REPLACE_CONTENT_START_ANGLE     "OBJ_START_ANGLE"
#define REPLACE_CONTENT_END_ANGLE       "OBJ_END_ANGLE"
#define REPLACE_CONTENT_CONCENTRATION   "OBJ_CONCENTRATION"

#define GNUPLOT_EXTENSION               ".plt"


namespace multiscale {

    namespace video {

        //! Gnuplot script generator from the provided annular sectors
        class PolarGnuplotScriptGenerator {

            public:

                //! Generate the script
                /*!
                 * \param annularSectors Annular sectors
                 * \param simulationTime Simulation time
                 * \param outputFilepath Path of the output file
                 */
                static void generateScript(const vector<AnnularSector> &annularSectors,
                                           double simulationTime,
                                           const string &outputFilepath)
                                           throw (string);

            private:

                //! Generate the header of the script
                /*!
                 * \param fout Output file stream
                 * \param outputFilepath Path to the output file
                 * \param simulationTime Simulation time
                 */
                static void generateHeader(ofstream &fout, const string &outputFilepath,
                                           double simulationTime);

                //! Generate the body/content of the script
                /*!
                 * \param annularSectors Annular sectors
                 * \param fout Output file stream
                 */
                static void generateBody(const vector<AnnularSector> &annularSectors,
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
                 * \param fout Output file stream
                 */
                static void outputHeader(ifstream &fin, const string &outputFilename,
                                         double simulationTime, ofstream &fout);

                //! Output the content of the script
                /*!
                 * \param annularSectors Annular sectors
                 * \param contentTemplate Template used for generating output for each annular sector
                 * \param fout Output file stream
                 */
                static void outputContent(const vector<AnnularSector> &annularSectors,
                                          const string &contentTemplate,
                                          ofstream &fout);

                //! Output the footer of the script
                /*!
                 * \param fin Input file stream
                 * \param fout Output file stream
                 */
                static void outputFooter(ifstream &fin, ofstream &fout);

                //! Read content template
                /*!
                 * \param fin Input file stream
                 */
                static string readContentTemplate(ifstream &fin);

        };

    };

};


#endif
