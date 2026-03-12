#include "model/sequence.h"
#include <cctype>
#include <algorithm>

Sequence::Sequence(const std::string& dna,
                   const std::string& name,
                   const std::string& description)
    : dna_(dna), name_(name), description_(description), protein_("") {
}


//Constructor
Sequence::Sequence()
    : dna_(""), name_(""), description_(""), protein_("") {
}

// === GETTERS ===
std::string Sequence::getDNA() const {
    return dna_;
}


std::string Sequence::getProtein() const {
    return protein_;
}


std::string Sequence::getName() const {
    return name_;
}


std::string Sequence::getDescription() const {
    return description_;
}


int Sequence::getLength() const {
    return dna_.length();
}

// === SETTERS ===
void Sequence::setProtein(const std::string& protein) {
    protein_ = protein;
}
void Sequence::setDNA(const std::string& dna) {
    dna_ = dna;
}


bool Sequence::isValid() const {
    // Empty sequence is invalid
    if (dna_.empty()) {
        return false;
    }
    
    // Check each character
    for (char nucleotide : dna_) {
        // Convert to uppercase for comparison
        char upper = std::toupper(nucleotide);
        
        // Check if it's a valid nucleotide
        if (upper != 'A' && upper != 'T' && upper != 'G' && upper != 'C') {
            return false;  // Invalid nucleotide found
        }
    }
    
    // All nucleotides are valid
    return true;
}