#ifndef RGBCOLOURGENERATOR_HPP_
#define RGBCOLOURGENERATOR_HPP_

#include <string>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

#define HUE_MIN     0
#define HUE_MAX     120
#define SATURATION  1
#define VALUE       1


namespace multiscale {

    //! Generate a RGB colour
    /*! Generate a RGB colour given the possible range for
     *  concentrations and the value of one of the concentrations
     *
     *  The conversion HSV->RGB is based on the wikipedia page on this topic
     */
    class RGBColourGenerator {

        private:

            static double red;      /*!< The amount of red */
            static double green;    /*!< The amount of green */
            static double blue;     /*!< The amount of blue */

        public:

            //! Generate a RGB colour for the given concentration
            /*! Generate a RGB colour considering the range of values a concentration can have
             *  and the value of the concentration
             *
             *  \param concentrationMin The minimum of the range of values a concentration can take
             *  \param concentrationMax The maximum of the range of values a concentration can take
             *  \param concentration    The concentration
             */
            static string generate(double concentrationMin,
                                   double concentrationMax,
                                   double concentration);

            //! Generate a random RGB colour
            /*! Generate a random RGB colour using the given random number generator
             *
             * \param randomNumberGenerator Random number generator
             */
            static Scalar generate(RNG &randomNumberGenerator);

        private:

            //! Convert a colour from HSV to RGB colour space
            /*!
             *  \param hue Hue
             *  \param saturation Saturation
             *  \param value Value
             */
            static string convertHSVToRGB(double hue, double saturation, double value);

            //! Compute RGB values from HSV specific values
            /*!
             * \param huePrime Hue'
             * \param X X
             * \param chroma Chroma
             * \param m m
             */
            static void computeRGBValues(int huePrime, double X, double chroma, double m);

            //! Convert the RGB colour to a string
            static string convertRGBToString();

    };

};

#endif
