#ifndef RGBCOLOURGENERATOR_HPP_
#define RGBCOLOURGENERATOR_HPP_

#include <string>

using namespace std;

#define HUE_MIN       0
#define HUE_MAX    120
#define SATURATION 1
#define VALUE             1

/*
 * Class for generating a RGB colour given the possible range for
 * concentrations and the value of one of the concentrations
 *
 * The conversion HSV->RGB is based on the wikipedia page on this topic
 */
namespace multiscale {

    class RGBColourGenerator {

        private:

            static double red;
            static double green;
            static double blue;

        public:

            static string generate(double concentrationMin,
                                   double concentrationMax,
                                   double concentration);

        private:

            static string convertHSVToRGB   (double hue,
                                             double saturation,
                                             double value);
            static void   computeRGBValues  (int huePrime, double X,
                                             double chroma, double m);
            static string convertRGBToString();

    };

};

#endif
