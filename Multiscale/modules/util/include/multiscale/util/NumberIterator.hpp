#ifndef NUMBERITERATOR_HPP
#define NUMBERITERATOR_HPP

namespace multiscale {

    //! Abstract class representing a number iterator
    class NumberIterator {

        protected:

            bool         isInitialised; /*!< Flag for checking if the iterator was initialised */
            unsigned int upperBound;    /*!< Upper bound of the iterator */

        public:

            NumberIterator(unsigned int upperBound);
            virtual ~NumberIterator() {};

            //! Initialise the iterator considering the given upper bound
            /*!
             *  \param upperBound The upper bound
             */
            void init(unsigned int upperBound);

            //! Check if there is a next number
            bool hasNext();

            //! Get the number pointed by the iterator
            virtual unsigned int number() = 0;

            //! Reset the iterator
            /*! Reset the iterator such that it is not initialised
             *  and the value of the current number is reset to its
             *  initial value
             */
            void reset();

        private:

            //! Initialisation of the members of the class
            virtual void initialise() = 0;

            //! Check if there is a next number when in initialised state
            virtual bool hasNextInitialised() = 0;

            //! Check if there is a next number when in not initialised state
            bool hasNextNotInitialised();

            //! Reset the current number to its initial value
            virtual void resetCurrentNumber() = 0;

    };

};


#endif
