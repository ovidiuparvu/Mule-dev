#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

namespace multiscale {

	namespace verification {

		class Attribute {

			public:

				virtual ~Attribute() {};

				virtual bool evaluate() const = 0;

		};

	};

};


#endif
