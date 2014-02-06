#ifndef ATTRIBUTEVISITOR_HPP
#define ATTRIBUTEVISITOR_HPP

#include <boost/variant.hpp>


namespace multiscale {

	namespace verification {

		class AttributeVisitor : public boost::static_visitor<bool> {

			public:

				template <typename T>
				bool operator() (const T &attribute) const {
					return attribute.evaluate();
				}

		};

	};

};

#endif
