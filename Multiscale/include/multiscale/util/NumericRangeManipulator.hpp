#ifndef NUMERICRANGEMANIPULATOR_HPP_
#define NUMERICRANGEMANIPULATOR_HPP_

namespace multiscale {

	class NumericRangeManipulator {

	public:

		template <class T, class U>
		static U convertFromRange(T oldRangeMin, T oldRangeMax,
				                  U newRangeMin, U newRangeMax,
				                  T oldValue) {
			U normalisedValue = ((U)(oldValue - oldRangeMin)) /
					             (oldRangeMax - oldRangeMin);

			return (newRangeMin +
					normalisedValue * (newRangeMax - newRangeMin));
		}

	};

};

#endif
