#ifndef ATTRIBUTEVISITOR_HPP
#define ATTRIBUTEVISITOR_HPP

/*
 *  TODO: Remove this file
 */

#include <boost/variant.hpp>


namespace multiscale {

    namespace verification {

        //! Variant for representing the attribute truth value
        typedef boost::variant<
            bool
        > AttributeTruthValue;


        //! Class used to evaluate attributes
        class AttributeVisitor : public boost::static_visitor<bool> {

            public:

                //! Overloading the operator ()
                /*!
                 * \param attribute The attribute
                 */
                template <typename T>
                bool operator() (const T &attribute) const {
                    return attribute.evaluate();
                }

                //! Overloading the operator ()
                /*!
                 * \param attribute     The attribute
                 * \param truthValue    Truth value considered when evaluating the attribute
                 */
                template <typename T, typename U>
                bool operator() (const T &attribute, const U &truthValue) const {
                    return attribute.evaluateConsideringTruthValue(truthValue);
                }

        };

    };

};

#endif
