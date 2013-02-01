#ifndef STANDARDNUMBERITERATOR_HPP_
#define STANDARDNUMBERITERATOR_HPP_

#include "multiscale/util/NumberIterator.hpp"

/*
 * Iterator starting at 1 and iterating over all natural numbers until the
 * provided upper bound
 */
namespace multiscale {

    class StandardNumberIterator : public NumberIterator {

        private:

            unsigned int currentNumber;

        public:

            StandardNumberIterator (unsigned int upperBound);
            ~StandardNumberIterator();

            unsigned int number ();

        private:

            void initialise		   ();
            bool hasNextInitialised();
            void resetCurrentNumber();

    };

};

#endif
