#include <igloo/igloo.h>
#include <mymath.h>

using namespace igloo;


Context(AdditionFunction){
	Spec(NegOnePlusOneIsZero){
		Assert::That(add(-1, 1), Equals(0));
	};

	Spec(TwoPlusOneIsThree){
		Assert::That(add(2, 1), Equals(3));
	};
};

int main() {
	// Run all the tests defined above
	return TestRunner::RunAllTests();
}
