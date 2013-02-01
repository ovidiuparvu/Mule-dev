#ifndef NUMBERITERATOR_HPP_
#define NUMBERITERATOR_HPP_

namespace multiscale {

    class NumberIterator {

        protected:

            bool         isInitialised;
            unsigned int upperBound;

        public:

            NumberIterator(unsigned int upperBound);
            virtual ~NumberIterator() {};

            void                    init   (unsigned int upperBound);
            bool                    hasNext();
            virtual unsigned int    number () = 0;
            void                    reset  ();

        private:

            virtual void            initialise           () = 0;
            virtual bool            hasNextInitialised   () = 0;
            bool                    hasNextNotInitialised();
            virtual void            resetCurrentNumber   () = 0;

    };

};

#endif
