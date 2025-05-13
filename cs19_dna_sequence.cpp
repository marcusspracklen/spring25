#include "cs19_dna_sequence.h"
#include <string>

namespace cs19 {
    // Default constructor
    DnaSequence::DnaSequence() : head(nullptr), tail(nullptr), length(0) {}

    // Destructor
    DnaSequence::~DnaSequence() {
        release_nodes();
    }

    void DnaSequence::release_nodes() {
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
            }
            a = a->next;
            b = b->next;
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

            // Match motif to node
            while (check && motif_node && check->data == motif_node->data) {
                check = check->next;
                motif_node = motif_node->next;
            }

            // Match found
            if (!motif_node) {
                Node* before = start->prev;
                Node* after = check;

                // Delete match
                Node* to_delete = start;
                for (std::size_t i = 0; i < motif.length; i++) {
                    Node* next = to_delete->next;
                    delete to_delete;
                    to_delete = next;
                }

                // Reconnect pointers
                if (before) {
                    before->next = after;
                } else {
                    head = after;
                }

                if (after) {
                    after->prev = before;
                } else {
                    tail = before;
                }

                length -= motif.length;
                it = after;
            // No match found move forward
            } else {
                it = it->next;
            }
        }
    }

    // Return starting address of the list
    DnaSequence::Iterator DnaSequence::begin() {
        return Iterator(head);
    }

    // Returns past the end of the list
    DnaSequence::Iterator DnaSequence::end() {
        return Iterator(nullptr);
    }

    // Inserts a value before the node pointed to by pos
    DnaSequence::Iterator DnaSequence::insert(Iterator pos, char val) {
        Node* new_node = new Node(val);
        Node* current = pos.ptr;

        if (!current) {
            if (!tail) {
                // Checks in case the list is empty
                head = tail = new_node;
            } else {
                // Inserts at the end if list is not empty
                tail->next = new_node;
                new_node->prev = tail;
                tail = new_node;
            }
        } else {
            // Inserts before a specific node
            // Links new_node between current->prev and current
            new_node->next = current;
            new_node->prev = current->prev;
            if (current->prev) {
                // Checks to make sure there is a node before current
                current->prev->next = new_node;
            } else {
                // Inserts at the head
                head = new_node;
            }
            // Update current->prev's pointer
            current->prev = new_node;
        }

        ++length;
        return Iterator(new_node);
    }

    // Removes the node pointed to by pos
    DnaSequence::Iterator DnaSequence::erase(Iterator pos) {
        Node* current = pos.ptr;
        if (!current) {
            // Nothing to erase
            return end();
        }

        Node* before = current->prev;
        Node* after = current->next;

        if (current = head) {
            head = after;
        }
        if (current = tail) {
            tail = before;
        }
        if (before) {
            // Update the link from the node before
            before->next = after;
        }
        if (after) {
            // Update link from node after
            after->prev = before;
        }

        delete current;
        --length;
        return Iterator(after);
    }

    // Splices in all nodes from that into this before pos
    void DnaSequence::splice(Iterator pos, DnaSequence& that) {
        if (that.length == 0) {
            // Nothing to splice
            return;
        }

        // Node before where splice
        Node* insert_point = pos.ptr;
        if (!insert_point) {
            // If we're at the end of the list splice at the end
            splice_after(that);
            return;
        }

        Node* before = insert_point->prev;

        if (before) {
            // Splices in the middle of the list
            before->next = that.head;
        } else {
            // Splices at the very beginning
            head = that.head;
        }

        // Reconnect nodes to complete the splice
        that.head->prev = before;
        insert_point->prev = that.tail;
        that.tail->next = insert_point;

        length += that.length;

        // Clear that
        that.head = that.tail = nullptr;
        that.length = 0;
    }
}  // namespace cs19
