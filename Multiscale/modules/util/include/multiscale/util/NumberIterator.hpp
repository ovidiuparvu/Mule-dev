#ifndef NUMBERITERATOR_HPP
#define NUMBERITERATOR_HPP

namespace multiscale {

    //! Abstract class representing a number iterator
    class NumberIterator {

        protected:

            bool         isInitialized; /*!< Flag for checking if the iterator was initialized */
            unsigned int upperBound;    /*!< Upper bound of the iterator */

        public:

            NumberIterator(unsigned int upperBound);
            virtual ~NumberIterator() {};

            //! Initialize the iterator considering the given upper bound
            /*!
             *  \param upperBound The upper bound
             */
            void init(unsigned int upperBound);

            //! Check if there is a next number
            bool hasNext();

            //! Get the number pointed by the iterator
            virtual unsigned int number() = 0;

            //! Reset the iterator
            /*! Reset the iterator such that it is not initialized
             *  and the value of the current number is reset to its
             *  initial value
             */
            void reset();

        private:

            //! Initialisation of the members of the class
            virtual void initialize() = 0;

            //! Check if there is a next number when in initialized state
            virtual bool hasNextInitialized() = 0;

            //! Check if there is a next number when in not initialized state
            bool hasNextNotInitialized();

            //! Reset the current number to its initial value
            virtual void resetCurrentNumber() = 0;

    };

};


#endif
