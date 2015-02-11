#ifndef SPATIALMEASURECALCULATOR_HPP
#define SPATIALMEASURECALCULATOR_HPP

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <vector>


namespace multiscale {

    namespace analysis {

        //! Class for computing spatial measures
        class SpatialMeasureCalculator {

        public:

            //! Compute the area of the provided polygon
            /*! The area of the polygon is computed as the number of
             *  pixels on, respectively contained by its contour.
             *
             *  \param polygon  The polygon for which the area is computed
             */
            static int computePolygonArea(const std::vector<cv::Point> &polygon);

            //! Compute the area of the given hole within the provided polygon
            /*! The area of the hole is computed as the number of pixels on,
             *  respectively contained by the hole's contour and which are not
             *  on the polygon's contour.
             *
             * \param hole      The hole for which the area is computed
             * \param polygon   The polygon which contains the hole
             */
            static int computePolygonHoleArea(const std::vector<cv::Point> &hole,
                                              const std::vector<cv::Point> &polygon);

            //! Compute the area of the provided circle
            /*! The area of the circle is computed as the number of
             *  pixels on, respectively contained by its contour.
             *
             *  \param circleOrigin The origin of the circle
             *  \param circleRadius The radius of the circle
             */
            static int computeCircleArea(const cv::Point2f &circleOrigin, double circleRadius);

            //! Compute the perimeter of the provided polygon
            /*! The perimeter of the polygon is computed as the number of
             *  pixel sides which are exterior to the polygon.
             *
             * \param polygon    The polygon for which the perimeter is computed
             */
            static int computePolygonPerimeter(const std::vector<cv::Point> &polygon);

        private:

            //! Return an image in which the polygon was drawn
            /*! The filled white polygon is drawn at a minimum distance of 1
             *  pixel from each border of the image. The background of the image
             *  is black.
             *
             * \param polygon   The polygon which will be drawn on the image
             */
            static cv::Mat drawFilledPolygonOnImage(const std::vector<cv::Point> &polygon);

            //! Set the value of the image pixels defined by the polygon to the minimum value
            /*!
             * \param polygon   The polygon which will be drawn using minimum value
             *                  on the provided image
             * \param image     The considered image
             */
            static void subtractPolygonBorderFromImage(const std::vector<cv::Point> &polygon,
                                                       cv::Mat &image);

            //! Return an image in which the circle was drawn
            /*! The filled white circle is drawn at a minimum distance of 1
             *  pixel from each border of the image. The background of the image
             *  is black.
             *
             *  \param circleOrigin The origin of the circle
             *  \param circleRadius The radius of the circle
             */
            static cv::Mat drawFilledCircleOnImage(const cv::Point2f &circleOrigin, double circleRadius);

            //! Compute the number of minimum value sides of the point in the given image
            /*!
             * \param rowIndex  The point's row index
             * \param colIndex  The point's column index
             * \param image     The reference image
             */
            static int computeNrOfMinValuePointSides(int rowIndex, int colIndex, const cv::Mat &image);

            //! Check if there is a minimum value point above the given point
            /*!
             * \param rowIndex  The given point's row index
             * \param colIndex  The given point's column index
             * \param image     The reference image
             */
            static bool isMinValuePointUp(int rowIndex, int colIndex, const cv::Mat &image);

            //! Check if there is a minimum value point to the left of the given point
            /*!
             * \param rowIndex  The given point's row index
             * \param colIndex  The given point's column index
             * \param image     The reference image
             */
            static bool isMinValuePointLeft(int rowIndex, int colIndex, const cv::Mat &image);

            //! Check if there is a minimum value point below the given point
            /*!
             * \param rowIndex  The given point's row index
             * \param colIndex  The given point's column index
             * \param image     The reference image
             */
            static bool isMinValuePointDown(int rowIndex, int colIndex, const cv::Mat &image);

            //! Check if there is a minimum value point to the right of the given point
            /*!
             * \param rowIndex  The given point's row index
             * \param colIndex  The given point's column index
             * \param image     The reference image
             */
            static bool isMinValuePointRight(int rowIndex, int colIndex, const cv::Mat &image);


            // Constants
            static const int POINT_MIN_VALUE;
            static const int POINT_MAX_VALUE;

        };

    }

}


#endif
