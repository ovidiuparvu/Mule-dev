#include "multiscale/core/MultiscaleTest.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/verification/spatial-temporal/Parser.hpp"

#include <string>
#include <vector>

using namespace multiscaletest;
using namespace multiscale::verification;


namespace multiscaletest {

    //! Class for testing the minimum enclosing triangle algorithm
    class ParserTest : public MultiscaleTest {

    	protected:

    		Parser				parser;			/*!< The tested parser */
    		ConstraintAttribute parseResult;	/*!< The result of the parsing process */
    		bool				testResult;		/*!< The result from the latest test */

		public:

    		ParserTest();
    		~ParserTest();

    		//! Test the scenario when there is no input
    		bool TestNoInput();

    		//! Test the scenario when the input is prefixed with an incorrect operator
    		bool TestIncorrectPrefix();

    		//! Test the scenario when the input is suffixed with an incorrect operator
    		bool TestIncorrectSuffix();

    		//! Test the scenario when erroneous input is added to the middle
    		bool TestErroneousInputInMiddle();

    		//! Test the scenario when a correct numeric state variable is provided
    		bool TestCorrectNumericStateVariable();

    		//! Test the scenario when correct input containing one/more binary operators is provided
    		bool TestUnaryOperators();

    		//! Test the scenario when correct input containing one/more binary operators is provided
    		bool TestBinaryOperators();

    		//! Test the scenario when correct enclosing parentheses are provided
    		bool TestCorrectEnclosingParentheses();

    		//! Test the scenario when incorrect enclosing parentheses are provided
    		bool TestIncorrectEnclosingParentheses();

    		//! Test the scenario when correct combinations of operators are provided
    		bool TestCorrectOperatorsCombinations();

    		//! Test the scenario when incorrect combinations of operators are provided
    		bool TestIncorrectOperatorsCombinations();

		protected:

			//! Run the test for the given set of points
			void RunTest() override;

			//! Check if the obtained results are valid
			void ValidateTestResults() override;


		private:

			// Constants
			static const int 						NR_RANDOM_TESTS;
			static const std::vector<std::string>	OPERATORS;
			static const std::vector<std::string>	BINARY_OPERATORS;
			static const std::vector<std::string>	UNARY_OPERATORS;

    };


    ParserTest::ParserTest() : parser(""), testResult(true) {}
    ParserTest::~ParserTest() {}


    bool ParserTest::TestNoInput() {
    	parser.setLogicalQuery("");

    	RunTest();
    	ValidateTestResults();

    	return testResult;
    }

    bool ParserTest::TestIncorrectPrefix() {
    	for (const auto &binaryOperator : BINARY_OPERATORS) {
    		parser.setLogicalQuery(binaryOperator + " A");

			RunTest();
			ValidateTestResults();
    	}

    	return testResult;
    }

    bool ParserTest::TestIncorrectSuffix() {
       	for (const auto &operator_ : OPERATORS) {
       		parser.setLogicalQuery(" A " + operator_);

   			RunTest();
   			ValidateTestResults();
       	}

       	return testResult;
    }

    bool ParserTest::TestErroneousInputInMiddle() {
    	for (const auto &operator_ : OPERATORS) {
    		parser.setLogicalQuery(" ABC " + operator_ + operator_ + "ABC");

			RunTest();
			ValidateTestResults();
		}

		return testResult;
    }

    bool ParserTest::TestCorrectNumericStateVariable() {
    	parser.setLogicalQuery("A");

    	RunTest();
		ValidateTestResults();

		return testResult;
    }

    bool ParserTest::TestUnaryOperators() {
    	for (const auto &unaryOperator : UNARY_OPERATORS) {
    		parser.setLogicalQuery(unaryOperator + "ABC");

			RunTest();
			ValidateTestResults();
		}

		return testResult;
    }

    bool ParserTest::TestBinaryOperators() {
    	for (const auto &binaryOperator : BINARY_OPERATORS) {
    		parser.setLogicalQuery(" ABC " + binaryOperator + "ABC");

			RunTest();
			ValidateTestResults();
		}

		return testResult;
    }

    bool ParserTest::TestCorrectEnclosingParentheses() {
    	std::vector<std::string> inputStrings = std::vector<std::string>(
    												{"(A)", "(A V B)", "((A ^ B) V (C ^ D))",
    												 "((((A))) V (B))", "((A)) => ((B))"});

    	for (const auto &input : inputStrings) {
    		parser.setLogicalQuery(input);

			RunTest();
			ValidateTestResults();
		}

		return testResult;
    }

    bool ParserTest::TestIncorrectEnclosingParentheses() {
		std::vector<std::string> inputStrings = std::vector<std::string>(
													{"((A)", ")A V B(", "((A ^ B) V (C ^ D)))",
													 "((((A())) V (B))", "((A))) => ((B)(())"});

		for (const auto &input : inputStrings) {
			parser.setLogicalQuery(input);

			RunTest();
			ValidateTestResults();
		}

		return testResult;
	}

    bool ParserTest::TestCorrectOperatorsCombinations() {
    	for (const auto &unaryOperator : UNARY_OPERATORS) {
    		for (const auto &binaryOperator : BINARY_OPERATORS) {
    			parser.setLogicalQuery(unaryOperator + " A " + binaryOperator + " B");

				RunTest();
				ValidateTestResults();
			}
    	}

		return testResult;
	}

    bool ParserTest::TestIncorrectOperatorsCombinations() {
      	for (const auto &unaryOperator : UNARY_OPERATORS) {
      		for (const auto &binaryOperator : BINARY_OPERATORS) {
  				parser.setLogicalQuery(" A " + unaryOperator + binaryOperator + " B");

  				RunTest();
  				ValidateTestResults();
  			}
      	}

  		return testResult;
  	}

    void ParserTest::RunTest() {
    	testResult = (testResult && parser.parse(parseResult));
    }

    void ParserTest::ValidateTestResults() {}


    //Constants
    const int ParserTest::NR_RANDOM_TESTS = 100;
    const std::vector<std::string> ParserTest::OPERATORS = std::vector<std::string>({"~", "V", "^", "=>", "<=>"});
    const std::vector<std::string> ParserTest::BINARY_OPERATORS = std::vector<std::string>({"V", "^", "=>", "<=>"});
    const std::vector<std::string> ParserTest::UNARY_OPERATORS = std::vector<std::string>({"~"});

};


// Tests
TEST_F(ParserTest, IncorrectInput) {
	EXPECT_THROW(TestNoInput(), multiscale::InvalidInputException);
	EXPECT_THROW(TestIncorrectPrefix(), multiscale::InvalidInputException);
	EXPECT_THROW(TestIncorrectSuffix(), multiscale::InvalidInputException);
	EXPECT_THROW(TestErroneousInputInMiddle(), multiscale::InvalidInputException);
}

TEST_F(ParserTest, NumericStateVariable) {
	EXPECT_TRUE(TestCorrectNumericStateVariable());
}

TEST_F(ParserTest, Operators) {
	EXPECT_TRUE(TestUnaryOperators());
	EXPECT_TRUE(TestBinaryOperators());
}

//TEST_F(ParserTest, EnclosingParentheses) {
//	EXPECT_TRUE(TestCorrectEnclosingParentheses());
//	EXPECT_THROW(TestIncorrectEnclosingParentheses(), multiscale::InvalidInputException);
//}
//
//TEST_F(ParserTest, OperatorsCombinations) {
//	EXPECT_TRUE(TestCorrectOperatorsCombinations());
//	EXPECT_THROW(TestIncorrectOperatorsCombinations(), multiscale::InvalidInputException);
//}


// Main method
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
