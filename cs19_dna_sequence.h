#ifndef CS_19_DnaSequence_H
#define CS_19_DnaSequence_H

#include <string>
#include <stdexcept>

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
    std::size_t length = 0;

    friend std::ostream& operator<<(std::ostream& os, const DnaSequence& seq);


 public:
    DnaSequence();
    ~DnaSequence();
    DnaSequence(const DnaSequence& other) : DnaSequence() {
        for (Node* i = other.head; i; i = i->next) {
            push_back(i->data);
        }
    }
    DnaSequence(const std::string& sequence);

    void release_nodes();
    void print() const;
    bool operator==(const DnaSequence& other);
    char& operator[](std::size_t pos);
    void remove_all(const DnaSequence& motif);
    void splice_after(DnaSequence& other);
    void splice_before(DnaSequence& other);
    void push_back(char val);
    std::size_t size();

    DnaSequence& operator=(DnaSequence& other);

    class Iterator {
     public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = char;
        using difference_type   = std::ptrdiff_t;
        using pointer           = char*;
        using reference         = char&;

        Iterator(Node* node) : ptr(node) {}

        Iterator& operator=(const Iterator& other) {
            if (this != &other) {
                ptr = other.ptr;
            }
            return *this;
        }

        char& operator*() const {
            if (!ptr) {
                throw std::out_of_range("Target out of range");
            }
            return ptr->data;
        }

        Iterator& operator++() {
            if (ptr) {
                ptr = ptr->next;
            }
                return *this;
        }
        Iterator& operator--() {
            if (ptr) {
                ptr = ptr->prev;
            }
                return *this;
        }

        bool operator==(const Iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }

     private:
        friend class DnaSequence;
        Node* ptr;
    };

    // Iterator operations
    // Points to first element
    Iterator begin();
    // Points past the end so we know once we've run off the end of the list
    Iterator end();

    // Instert a char before pos
    // Returns an iterator poointing to the newly inserted val
    Iterator insert(Iterator pos, char val);

    // Insert a range before pos
    template <typename InputIterator>
    Iterator insert(Iterator pos, InputIterator first, InputIterator last) {
      if (first == last) {
         // Nothing to insert
         return pos;
     }

     // Store the return position of pos
     Iterator result = pos;
     int count = 0;
     Iterator it = nullptr;
     while (first != last) {
        // Insert each element before pos
        result = insert(pos, *first++);
        if (count == 0) {
            it = result;
        }
        count++;
     }
     return it;
    }

    // Remove node at pos
    Iterator erase(Iterator pos);

    // Splice list into this once before the given pos
    void splice(Iterator position, DnaSequence& that);
};

}  // namespace cs19
#endif