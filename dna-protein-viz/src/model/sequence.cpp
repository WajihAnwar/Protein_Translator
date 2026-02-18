#include "model/sequence.h"
#include <cctype>
#include <algorithm>

/**
 * Constructor - creates a sequence with DNA, optional name and description
 */
Sequence::Sequence(const std::string& dna,
                   const std::string& name,
                   const std::string& description)
    : dna_(dna), name_(name), description_(description), protein_("") {
}

/**
 * Default constructor - creates an empty sequence
 */
Sequence::Sequence()
    : dna_(""), name_(""), description_(""), protein_("") {
}

// === GETTERS ===

/**
 * Get the DNA sequence
 */
std::string Sequence::getDNA() const {
    return dna_;
}

/**
 * Get the translated protein sequence
 */
std::string Sequence::getProtein() const {
    return protein_;
}

/**
 * Get the sequence name/identifier
 */
std::string Sequence::getName() const {
    return name_;
}

/**
 * Get the sequence description
 */
std::string Sequence::getDescription() const {
    return description_;
}

/**
 * Get the length of the DNA sequence
 */
int Sequence::getLength() const {
    return dna_.length();
}

// === SETTERS ===

/**
 * Set the translated protein sequence
 */
void Sequence::setProtein(const std::string& protein) {
    protein_ = protein;
}

/**
 * Set the DNA sequence
 */
void Sequence::setDNA(const std::string& dna) {
    dna_ = dna;
}

// === VALIDATION ===


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