#include "cs19_dna_sequence.h"
#include <string>
#include <iostream>

namespace cs19 {
    // Default constructor
    DnaSequence::DnaSequence() : head(nullptr), tail(nullptr), length(0) {}

    // Constructor that builds list from a string
    DnaSequence::DnaSequence(const std::string& sequence) : DnaSequence() {
        // std::cout << "called const. \n";
        for (char i : sequence) {
            push_back(i);
        }
    }

    // FOR TESTING
    void DnaSequence::print() const {
        Node* current = head;
        while (current) {
          std::cout << current->data;
          current = current->next;
        }
        std::cout << '\n';
      }
      

    // Equality comparison, only returns true if the sequences are identical
    bool DnaSequence::operator==(const DnaSequence& another) {
        // std::cout << "called == \n";
        if(length != another.length) {
            return false;
        }
        Node* a = head;
        Node* b = another.head;

        while (a && b) {
            if(a->data != b->data) {
                return false;
                a = a->next;
                b = b->next;
            }
        }
        return true;
    }

    // Accesses the character at the position pos
    char& DnaSequence::operator[](std::size_t pos) {
        // std::cout << "called [] \n";

        Node* current = head;
        for (std::size_t i = 0; i < pos && current; i++) {
            current = current->next;
        }
        return current->data;
    }

    // Adds a character to the end of the list
    void DnaSequence::push_back(char val) {
        // std::cout << "called pushback \n";

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

    // Returns size of the list!
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
        // std::cout << "called remove all \n";

        if (motif.length == 0 || motif.length > this->length) {
            return;
        }

        Node* current = head;

        while (current) {
            Node* start = current;
            Node* check = current;
            Node* motif_node = motif.head;

            // Match motif to current node
            while (check && motif_node && check->data == motif_node->data) {
                check = check->next;
                motif_node = motif_node->next;
            }

            // Match found
            if(!motif_node) {
                Node* before = start->prev;
                Node* after = check;

                // Delete match
                Node* to_delete = start;
                for (std::size_t i = 0; i < motif.length; i++) {
                    Node* next = to_delete->next;
                    delete to_delete;
                    to_delete = next;
                    // std::cout << "removed \n";
                }

                length -= motif.length;
                current = after;
            // No match found move forward
            } else {
                current = current->next;
                // std::cout << "not removed \n";
            }
        }
    }

}
