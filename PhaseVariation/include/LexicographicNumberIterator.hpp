#ifndef LEXICOGRAPHICNUMBERITERATOR_HPP_
#define LEXICOGRAPHICNUMBERITERATOR_HPP_

#include <vector>

using namespace std;

// Class for iterating over all the numbers up to the given limit
// considering that each number is followed by an "_"

namespace multiscale {

	class LexicographicNumberIterator {

	private:

		unsigned int upperBound;

		vector<unsigned char> upperBoundDigits;
		vector<unsigned char> currentNumberDigits;

	public:

		LexicographicNumberIterator(unsigned int upperBound);
		~LexicographicNumberIterator();

		bool 			hasNext();
		unsigned int 	number();
		void 			reset();

	private:

		void 			numberToDigits			(unsigned int number, vector<unsigned char>& digits);
		void			reverseDigits			(vector<unsigned char>& digits);
		unsigned int 	digitsToNumber			(vector<unsigned char>& digits);
		bool 			isLargerThanUpperBound	(unsigned char lastDigit);
		void 			padWithZeros  			();

	};

};

#endif
