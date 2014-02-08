#ifndef NIL_HPP
#define NIL_HPP

//#include "multiscale/verification/spatial-temporal/attribute/Attribute.hpp"

#include <fstream>


namespace multiscale {

	namespace verification {

		//! A class used to avoid run-time errors when defining a variant type.
		/*!
		 * When defining a variable of variant type "V" the default constructor of the
		 * first type within "V" is called. In order to avoid run-time errors this type
		 * needs to be different from the boost::recursive_wrapper<T> type. In variants
		 * where all types are boost::recursive_wrapper<T_i> the Nil type can be added
		 * before them in order to avoid the potential run-time errors.
		 */
		class Nil {
//		class Nil : public Attribute {

//			public:

				//! Evaluate the constraint
//				bool evaluate() const override {
//					return true;
//				}

            friend std::ostream& operator<<(std::ostream& stdout, const Nil &nil);

		};

		// Define the output stream operator
		inline std::ostream& operator<<(std::ostream& out, const Nil &nil) {
			return out;
		}

	};

};

#endif
