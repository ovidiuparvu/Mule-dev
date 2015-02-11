#ifndef POLARGNUPLOTSCRIPTGENERATOR_HPP
#define POLARGNUPLOTSCRIPTGENERATOR_HPP

#include "multiscale/visualisation/circular/AnnularSector.hpp"

#include <vector>


namespace multiscale {

    namespace visualisation {

        //! Gnuplot script generator from the provided annular sectors
        class PolarGnuplotScriptGenerator {

            public:

                //! Generate the script
                /*!
                 * \param annularSectors Annular sectors
                 * \param simulationTime Simulation time
                 * \param outputFilepath Path of the output file
                 */
                static void generateScript(const std::vector<AnnularSector> &annularSectors,
                                           double simulationTime,
                                           const std::string &outputFilepath);

            private:

                //! Generate the header of the script
                /*!
                 * \param fout Output file stream
                 * \param outputFilepath Path to the output file
                 * \param simulationTime Simulation time
                 */
                static void generateHeader(std::ofstream &fout, const std::string &outputFilepath,
                                           double simulationTime);

                //! Generate the body/content of the script
                /*!
                 * \param annularSectors Annular sectors
                 * \param fout Output file stream
                 */
                static void generateBody(const std::vector<AnnularSector> &annularSectors,
                                         std::ofstream &fout);

                //! Generate the footer of the script
                /*!
                 * \param fout Output file stream
                 */
                static void generateFooter(std::ofstream &fout);

                //! Output the header of the script
                /*!
                 * \param fin Input file stream
                 * \param outputFilename Name of the output file
                 * \param simulationTime Simulation time
                 * \param fout Output file stream
                 */
                static void outputHeader(std::ifstream &fin, const std::string &outputFilename,
                                         double simulationTime, std::ofstream &fout);

                //! Output the content of the script
                /*!
                 * \param annularSectors Annular sectors
                 * \param contentTemplate Template used for generating output for each annular sector
                 * \param fout Output file stream
                 */
                static void outputContent(const std::vector<AnnularSector> &annularSectors,
                                          const std::string &contentTemplate,
                                          std::ofstream &fout);

                //! Output the footer of the script
                /*!
                 * \param fin Input file stream
                 * \param fout Output file stream
                 */
                static void outputFooter(std::ifstream &fin, std::ofstream &fout);

                //! Read content template
                /*!
                 * \param fin Input file stream
                 */
                static std::string readContentTemplate(std::ifstream &fin);

            private:

                // Constants
                static const std::string HEADER_IN;
                static const std::string CONTENT_IN;
                static const std::string FOOTER_IN;

                static const std::string REPLACE_HEADER_FILENAME;
                static const std::string REPLACE_HEADER_SIM_TIME;

                static const std::string REPLACE_CONTENT_INDEX;
                static const std::string REPLACE_CONTENT_RADIUS;
                static const std::string REPLACE_CONTENT_START_ANGLE;
                static const std::string REPLACE_CONTENT_END_ANGLE;
                static const std::string REPLACE_CONTENT_CONCENTRATION;

                static const std::string GNUPLOT_EXTENSION;

        };

    };

};


#endif
