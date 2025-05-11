#include <cassert>
#include <string>
#include "cs19_dna_sequence.h"
 
int main() {
  // Basic Iteration
  {
    cs19::DnaSequence s;
    assert(s.begin() == s.end());
  }
  {
    cs19::DnaSequence s("GATTACA");
    assert(std::string(s.begin(), s.end()) == "GATTACA");
  }
  {
    cs19::DnaSequence s("A");
    auto it = s.begin();
    assert(it != s.end());
    assert(*it == 'A');
    *it = 'C';
    assert(*it == 'C');
    ++it;
    assert(it == s.end());
    assert(s == cs19::DnaSequence("C"));
  }
  // Inserting
  {
    cs19::DnaSequence s("CT");
    auto it = s.begin();
    ++it;
    it = s.insert(it, 'A');
    assert(*it == 'A');
    assert(s == cs19::DnaSequence("CAT"));
    ++it;
    assert(*it == 'T');
    ++it;
    assert(it == s.end());
  }
  {
    cs19::DnaSequence s1("GA");
    std::string insertion("ATTAC");
    auto it = s1.begin();
    ++it;
    it = s1.insert(it, insertion.cbegin(), insertion.cend());
    assert(s1 == cs19::DnaSequence("GATTACA"));
    assert(*it == 'A');
    ++it;
    assert(*it == 'T');
  }
  // Erasing
  {
    cs19::DnaSequence s("GGATTTACAA");
    auto it = s.erase(s.begin());
    assert(std::string(s.begin(), s.end()) == "GATTTACAA");
    ++it;
    ++it;
    it = s.erase(it);
    assert(std::string(s.begin(), s.end()) == "GATTACAA");
    ++it;
    ++it;
    ++it;
    ++it;
    ++it;
    it = s.erase(it);
    assert(std::string(s.begin(), s.end()) == "GATTACA");
    assert(it == s.end());
  }
  // Splicing
  {
    cs19::DnaSequence s1("A");
    cs19::DnaSequence s2("GATTAC");
    s1.splice(s1.begin(), s2);
    assert(s1 == cs19::DnaSequence("GATTACA"));
    assert(s2 == cs19::DnaSequence());
    assert(s2.size() == 0);
  }
  {
    cs19::DnaSequence s1("G");
    cs19::DnaSequence s2("ATTACA");
    s1.splice(s1.end(), s2);
    assert(s1 == cs19::DnaSequence("GATTACA"));
    assert(s2 == cs19::DnaSequence());
    assert(s2.size() == 0);
  }
  {
    cs19::DnaSequence s1("GA");
    cs19::DnaSequence s2("ATTA");
    cs19::DnaSequence s3("C");
    auto it = s1.begin();
    ++it;
    s1.splice(it, s2);
    s1.splice(it, s3);
    assert(s1 == cs19::DnaSequence("GATTACA"));
    assert(s2 == cs19::DnaSequence());
    assert(s2.size() == 0);
    assert(s3 == cs19::DnaSequence());
    assert(s3.size() == 0);
  }
}