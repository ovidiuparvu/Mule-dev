#ifndef NUMERICRANGEMANIPULATOR_HPP_
#define NUMERICRANGEMANIPULATOR_HPP_

namespace multiscale {

	class NumericRangeManipulator {

	public:
		static double convertFromRange(double oldRangeMin, double oldRangeMax,
				                	   double newRangeMin, double newRangeMax,
				                	   double value);
		static double convertFromRange(int    oldRangeMin, int    oldRangeMax,
						        	   double newRangeMin, double newRangeMax,
						        	   int value);
		static int    convertFromRange(int oldRangeMin, int oldRangeMax,
									   int newRangeMin, int newRangeMax,
									   int value);

	};

};

#endif
