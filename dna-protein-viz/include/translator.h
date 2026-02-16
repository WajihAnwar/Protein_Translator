#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <string>
#include <vector>
#include "codon_table.h"
#include "sequence.h"


struct TranslationResult {
    std::string dna;        // Original DNA sequence
    std::string mrna;       // Transcribed mRNA (T→U)
    std::string protein;    // Translated amino acids
    double gcContent;       // Percentage of G+C nucleotides (0-100)
};

/**
 * @class Translator
 * @brief Converts DNA → mRNA → Protein
 * 
 * Three main operations:
 * 1. Transcription: DNA → mRNA (replace T with U)
 * 2. Translation: mRNA → Protein (read codons, lookup amino acids)
 * 3. Analysis: Calculate GC content
 */
class Translator {
private:
    CodonTable codonTable_;
    
    // Helper: convert string to uppercase
    std::string normalizeSequence(const std::string& sequence) const;

public:
    Translator();
    
    // DNA → mRNA (T becomes U)
    std::string transcribeDNAtoRNA(const std::string& dna) const;
    
    // mRNA → Protein (read 3 nucleotides at a time, lookup amino acid)
    std::string translateRNA(const std::string& mrna) const;
    
    // Calculate G+C percentage
    double calculateGCContent(const std::string& dna) const;
    
    // Complete pipeline: DNA → mRNA → Protein (+ stats)
    TranslationResult translate(const Sequence& sequence) const;
};

#endif // TRANSLATOR_H