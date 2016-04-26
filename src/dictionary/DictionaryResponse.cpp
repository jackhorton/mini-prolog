#include <vector>
#include <iostream>

#include "nodes/AbstractNode.h"
#include "dictionary/QueryContext.h"
#include "dictionary/DictionaryResponse.h"

using namespace prolog;
using std::map;
using std::cerr;
using std::cout;
using std::endl;
using std::cin;

DictionaryResponse::DictionaryResponse(AbstractNode const* root, QueryContext context) : root(root), context(context) {
    // the dictionaryresponse owns the root node
}

DictionaryResponse::~DictionaryResponse() {
    delete root;
}

void DictionaryResponse::prompt() const {
    cout << context.to_string() << endl;
}
