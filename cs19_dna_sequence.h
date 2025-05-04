#ifndef CS_19_DnaSequenceuence_H
#define CS_19_DnaSequenceuence_H

#include <string>

namespace cs19 {

class DnaSequence {
 private:
    struct Node {
        char data;
        Node* prev;
        Node* next;

        Node(char d) : data(d), prev(nullptr), next(nullptr) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    std::size_t length;

 public:
    DnaSequence();
    ~DnaSequence();
    DnaSequence(const std::string& sequence);

    void realease_nodes();
    void print() const;
    bool operator==(const DnaSequence& other);
    char& operator[](std::size_t pos);
    void remove_all(const DnaSequence& motif);
    void splice_after(DnaSequence& other);
    void splice_before(DnaSequence& other);
    void push_back(char val);
    std::size_t size();
};
}  // namespace cs19
#endif