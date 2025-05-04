#include "cs19_dna_sequence.h"
#include <string>

namespace cs19 {
    // Default constructor
    DnaSequence::DnaSequence() : head(nullptr), tail(nullptr), length(0) {}

    // Destructor
    DnaSequence::~DnaSequence() {
        realease_nodes();
    }

    void DnaSequence::realease_nodes() {
        for (Node* it = head; it != nullptr; ) {
            Node* next = it->next;
            delete it;
            it = next;
        }
        head = tail = nullptr;
        length = 0;
    }

    // Constructor that builds list from a string
    DnaSequence::DnaSequence(const std::string& sequence) : DnaSequence() {
        for (char i : sequence) {
            push_back(i);
        }
    }

    // Equality comparison, only returns true if the sequences are identical
    bool DnaSequence::operator==(const DnaSequence& another) {
        if (length != another.length) {
            return false;
        }
        Node* a = head;
        Node* b = another.head;

        while (a && b) {
            if (a->data != b->data) {
                return false;
                a = a->next;
                b = b->next;
            }
        }
        return true;
    }

    // Accesses the character at the position pos
    char& DnaSequence::operator[](std::size_t pos) {
        Node* it = head;
        for (std::size_t i = 0; i < pos && it; i++) {
            it = it->next;
        }
        return it->data;
    }

    // Adds a character to the end of the list
    void DnaSequence::push_back(char val) {
        Node* node = new Node(val);

        if (!tail) {
            head = tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        ++length;
    }

    // Returns size of the list
    std::size_t DnaSequence::size() {
        return length;
    }

    void DnaSequence::splice_after(DnaSequence& that) {
        if (that.length == 0) {
            return;
        }
        tail->next = that.head;
        that.head->prev = tail;
        tail = that.tail;

        length += that.length;

        that.head = that.tail = nullptr;
        that.length = 0;
    }

    void DnaSequence::splice_before(DnaSequence& that) {
        if (that.length == 0) {
            return;
        }

        Node* old_head = head;
        head = that.head;
        old_head->prev = that.tail;
        that.tail->next = old_head;

        length += that.length;

        that.head = that.tail = nullptr;
        that.length = 0;
    }

    void DnaSequence::remove_all(const DnaSequence& motif) {
        if (motif.length == 0 || motif.length > this->length) {
            return;
        }

        Node* it = head;

        while (it) {
            Node* start = it;
            Node* check = it;
            Node* motif_node = motif.head;

            // Match motif to it node
            while (check && motif_node && check->data == motif_node->data) {
                check = check->next;
                motif_node = motif_node->next;
            }

            // Match found
            if (!motif_node) {
                Node* after = check;

                // Delete match
                Node* to_delete = start;
                for (std::size_t i = 0; i < motif.length; i++) {
                    Node* next = to_delete->next;
                    delete to_delete;
                    to_delete = next;
                }

                length -= motif.length;
                it = after;
            // No match found move forward
            } else {
                it = it->next;
            }
        }
    }
}  // namespace cs19
