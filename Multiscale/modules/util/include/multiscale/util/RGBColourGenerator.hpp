#ifndef RGBCOLOURGENERATOR_HPP
#define RGBCOLOURGENERATOR_HPP

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>


namespace multiscale {

    //! Generate a RGB colour
    /*! Generate a RGB colour given the possible range for
     *  concentrations and the value of one of the concentrations
     *
     *  The conversion HSV->RGB is based on the wikipedia page on this topic
     */
    class RGBColourGenerator {

        private:

            double red;      /*!< The amount of red */
            double green;    /*!< The amount of green */
            double blue;     /*!< The amount of blue */

        public:

            //! Generate a RGB colour for the given concentration
            /*! Generate a RGB colour considering the range of values a concentration can have
             *  and the value of the concentration
             *
             *  \param concentrationMin The minimum of the range of values a concentration can take
             *  \param concentrationMax The maximum of the range of values a concentration can take
             *  \param concentration    The concentration
             */
            std::string generate(double concentrationMin,
                                 double concentrationMax,
                                 double concentration);

            //! Generate a random RGB colour
            /*! Generate a random RGB colour using the given random number generator
             *
             * \param randomNumberGenerator Random number generator
             */
            cv::Scalar generate(cv::RNG &randomNumberGenerator);

        private:

            //! Convert a colour from HSV to RGB colour space
            /*!
             *  \param hue Hue
             *  \param saturation Saturation
             *  \param value Value
             */
            std::string convertHSVToRGB(double hue, double saturation, double value);

            //! Compute RGB values from HSV specific values
            /*!
             * \param huePrime Hue'
             * \param X X
             * \param chroma Chroma
             * \param m m
             */
            void computeRGBValues(int huePrime, double X, double chroma, double m);

            //! Convert the RGB colour to a string
            std::string convertRGBToString();

        public:

            // Constants
            static const int HUE_MIN;
            static const int HUE_MAX;
            static const int SATURATION;
            static const int VALUE;

    };

};


#endif
