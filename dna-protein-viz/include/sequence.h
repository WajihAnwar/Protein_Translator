#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>

/**
 * Represents a DNA sequence and its translated protein.
 * Stores sequence data typically loaded from FASTA format.
 */
class Sequence {
public:
    /** Constructs a sequence with DNA, optional name, and description. */
    Sequence(const std::string& dna,
             const std::string& name = "",
             const std::string& description = "");

    /** Default constructor. */
    Sequence();

    // --- Getters ---
    std::string getDNA() const;
    std::string getProtein() const; //Translated Protein Sequence 
    std::string getName() const; //Sequnce Identifier 
    std::string getDescription() const; // Description 
    int getLength() const;

    // --- Setters ---
    void setProtein(const std::string& protein);
    void setDNA(const std::string& dna);

    // --- Validation ---
    /** Returns true if the DNA sequence contains only valid bases (A, T, G, C). */
    bool isValid() const;
    
private:
    std::string dna_;            // The DNA sequence (A, T, G, C)
    std::string protein_;        // The translated protein sequence
    std::string name_;           // Sequence identifier from FASTA header
    std::string description_;    // Full FASTA description
};

#endif