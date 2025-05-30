#include "cs19_n_gram_predictor.h"

namespace cs19 {

// Constructor, creates empty root with no key
NGramPredictor::NGramPredictor() {
    root_ = std::make_shared<Node>(""); // empty root
}

// Destructor
NGramPredictor::~NGramPredictor() = default;

// Recursively Traverse the tree to gather all full ngram paths from this node
void NGramPredictor::collect_suggestions(std::shared_ptr<Node> node,
                                        std:: vector<std::string>& current,
                                        std::vector<std::vector<std::string>>& results) const {
    
    // If the node marks the end of an ngram it is added to results
    if (node->terminal_) {
        results.push_back(current);
    }

    // Recurse into each child
    for (const auto& child : node->children_) {
        current.push_back(child->key_);
        collect_suggestions(child, current, results); // Recursive call
        current.pop_back(); // Backtrack after exploration is complete
    }
}

} // namespace cs19