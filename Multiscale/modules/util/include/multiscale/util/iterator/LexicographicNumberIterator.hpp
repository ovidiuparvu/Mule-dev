#ifndef LEXICOGRAPHICNUMBERITERATOR_HPP
#define LEXICOGRAPHICNUMBERITERATOR_HPP

#include "multiscale/util/NumberIterator.hpp"

#include <vector>


namespace multiscale {

    //! Iterator class starting at 1 and ending at the provided upper bound considering that each number is followed by an "_"
    class LexicographicNumberIterator : public NumberIterator {

        private:

            std::vector<unsigned char> upperBoundDigits;     /*!< The digits of the upper bound */
            std::vector<unsigned char> currentNumberDigits;  /*!< The digits of the number to which the iterator points */

        public:

            LexicographicNumberIterator (unsigned int upperBound);
            ~LexicographicNumberIterator();

            //! Get the number pointed by the iterator
            unsigned int number();

        private:

            //! Initialise the vectors of digits
            void initialise();

            //! Check if there is a next number when in initialised state
            bool hasNextInitialised();

            //! Reset the digits of the current number to the initial value
            void resetCurrentNumber();

            //! Convert the number to a vector of digits
            /*!
             *  \param number The number
             *  \param digits The digits of the number
             */
            void numberToDigits(unsigned int number, std::vector<unsigned char> &digits);

            //! Reverse the order of the digits
            /*! Reverse the order of the digits such that the first one is swapped with the last one,
             *  the second one is swapped with the last but one and so on.
             *
             *  \param digits The digits
             */
            void reverseDigits (std::vector<unsigned char> &digits);

            //! Convert the vector of digits to the number they represent
            /*!
             *  \param digits The digits
             */
            unsigned int digitsToNumber(std::vector<unsigned char> &digits);

            //! Check if the current number with the provided last digit is greater than the upper bound
            /*!Check if the current number is greater than the upper bound
             * when replacing the last digit of the current number with the
             * provided digit
             *
             * \param lastDigit The last digit
             */
            bool isLargerThanUpperBound(unsigned char lastDigit);

            //! Pad the current number with zeros
            /*! Pad the current number with the maximum number of zeros such that it does
             *  not to become larger than the upper bound
             */
            void padWithZeros();

    };

};


#endif
