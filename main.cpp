//
// Created by Filipp Ewseew on 1/30/21.
//

//#include "Vector.hpp"
#include "BTree.hpp"

int main()
{
	shitty::RBTree<int> tr;


	srand(time(NULL));
	for (int i = 0; i < 10; ++i) {
		tr.add(std::abs(rand() % 10));

	}


	tr.printInOrder();
	tr.prettyprint();
	return 0;
}
