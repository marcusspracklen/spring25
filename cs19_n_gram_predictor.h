#ifndef CS19_N_GRAM_PREDICTOR_H_
#define CS19_N_GRAM_PREDICTOR_H_

#include <vector>
#include <string>
#include <memory>
#include <algorithm>

namespace cs19 {

class NGramPredictor {
    private:
    // Node Struct that represents a single word in the ngram sequence
    struct Node {
        std::string key_; // The word
        int rank_ = 0; // Frequency of the word
        bool terminal_ = false; // Whether the node marks the end of a ngram
        std::vector<std::shared_ptr<Node>> children_; // The next possible nodes in the ngram
        Node* parent = nullptr; // Previous node in the ngram
        
        // Constructor to intitalize a node with its key and optional parent node
        Node(const std::string& key, Node* parent = nullptr) 
            : key_(key), parent(parent) {}
    };

    // The root node of my ngram tree
    std::shared_ptr<Node> root_;

    // Collects all suggestion starting from a given node
    void collect_suggestions(std::shared_ptr<Node> node,
                std:: vector<std::string>& current,
                std::vector<std::vector<std::string>>& results) const;


     public:

    // Constructor intilizing an empty tree
    NGramPredictor();
    // DESTRUCTOR
    ~NGramPredictor();

    // Adds an ngrame represented by a sequence of words [begin, end)
    template <typename Iterator>
    void add(Iterator begin, Iterator end) {
        auto current = root_;
        // Increment count for the root node which will be total ngrams
        ++(current->rank_);

        // Search if the word already exsists among children
        for (; begin != end; ++begin) {
            std::shared_ptr<Node> next = nullptr;
            for (auto& child : current->children_) {
                if (child->key_ == *begin) {
                    next = child;
                    break;
                }
            }

            // If the word is not found create a new child node
            if (!next) {
                next = std::make_shared<Node>(*begin, current.get());
                current->children_.push_back(next);
            }

            // Move to the next node and increment its rank
            current = next;
            ++(current->rank_);
        }

        // Mark the last node as terminal (the end of a complete ngram)
        current->terminal_ = true;
    }

    // Returns a list of all the completion that being with the sequence [begin, end)
    template <typename Iterator>
    std::vector<std::vector<std::string>> suggestions(Iterator begin, Iterator end) const {
        auto current = root_;

        // Traverse the prefix path to reach our starting node
        for (; begin!= end; ++begin) {
            std::shared_ptr<Node> next = nullptr;

            // Find matching child node
            for (auto& child : current->children_) {
                if (child->key_ == *begin) {
                    next = child;
                    break;
                }
            }

            // If prefix is not found return empty suggestions
            if (!next) {
                return{};
            }
            current = next;
        }

        std::vector<std::vector<std::string>> results;
        std::vector<std::string> current_path;

        // Collect all paths starting from the current node
        collect_suggestions(current, current_path, results);

        // Sort by frequency --rank-- descending
        std::sort(results.begin(), results.end(), [&](const auto& a, const auto& b) {
            auto rank_of = [&](const std::vector<std::string>& path) {
                Node* node = current.get();
                for (const auto& word : path) {
                    for (auto& child : node->children_) {
                        if (child->key_ == word) {
                            node = child.get();
                            break;
                        }
                    }
                }
                return node->rank_;
            };

            return rank_of(a) > rank_of(b);
        });
            return results; 
        }

        // Returns the total number of ngrams added
        size_t size() const {
            return root_ ? root_->rank_ : 0;
        }
};

}  // namespace cs19
#endif