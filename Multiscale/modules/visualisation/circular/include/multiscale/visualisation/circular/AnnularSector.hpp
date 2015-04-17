#ifndef ANNULARSECTOR_HPP
#define ANNULARSECTOR_HPP

#include <string>


namespace multiscale {

    namespace visualisation {

        //! An annular sector is the basic element in the considered circular geometry
        /*!
         *  More information about annuli and sectors of annuli can be found online (e.g. Wikipedia).
         */
        class AnnularSector {

            private:

                double startingRadius;  /*< The distance from the origin to the lower part of the sector */
                double endingRadius;    /*< The distance from the origin to the upper part of the sector */
                double startingAngle;   /*< The angle from which the sector starts */
                double endingAngle;     /*< The angle at which the sector ends */
                double concentration;   /*< Concentration in the sector */

            public:

                AnnularSector ();
                ~AnnularSector();

                //! Initialize the members of the class
                /*!
                 * \param startingRadius Starting radius
                 * \param endingRadius  Ending radius
                 * \param startingAngle Starting angle
                 * \param endingAngle Ending angle
                 * \param concentration Concentration
                 */
                void initialize(double startingRadius, double endingRadius,
                                double startingAngle,  double endingAngle,
                                double concentration);

                //! Get the value of the concentration
                double getConcentration () const;

                //! Get the value of the ending angle
                double getEndingAngle   () const;

                //! Get the value of the ending radius
                double getEndingRadius  () const;

                //! Get the value of the starting angle
                double getStartingAngle () const;

                //! Get the value of the starting radius
                double getStartingRadius() const;

                //! Get the string representation of the annular sector
                std::string toString();

        };

    };

};


#endif
