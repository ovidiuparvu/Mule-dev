#ifndef LEXICOGRAPHICNUMBERITERATOR_HPP_
#define LEXICOGRAPHICNUMBERITERATOR_HPP_

#include "multiscale/util/NumberIterator.hpp"

#include <vector>

using namespace std;

/*
 * Iterator starting at 1 and ending at the provided upper bound
 * considering that each number is followed by an "_"
 */
namespace multiscale {

    class LexicographicNumberIterator : public NumberIterator {

        private:

            vector<unsigned char> upperBoundDigits;
            vector<unsigned char> currentNumberDigits;

        public:

            LexicographicNumberIterator (unsigned int upperBound);
            ~LexicographicNumberIterator();

            unsigned int number ();

        private:

            void            initialise              ();
            bool            hasNextInitialised      ();
            void            resetCurrentNumber      ();
            void            numberToDigits          (unsigned int number,
                                                     vector<unsigned char> &digits);
            void            reverseDigits           (vector<unsigned char> &digits);
            unsigned int    digitsToNumber          (vector<unsigned char> &digits);
            bool            isLargerThanUpperBound  (unsigned char lastDigit);
            void            padWithZeros            ();

    };

};

#endif
