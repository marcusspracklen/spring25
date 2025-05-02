#include "cs19_dna_sequence.h"

namespace cs19 {
    DnaSequence::DnaSequence() : head(nullptr), tail(nullptr), length(0) {}

    DnaSequence::DnaSequence(const std::string& sequence) : DnaSequence() {
        for (char i : sequence) {
            push_back(i);
        }
    }

    bool DnaSequence::operator==(const DnaSequence& another) {
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
}
