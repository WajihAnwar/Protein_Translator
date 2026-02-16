#ifndef CODON_TABLE_H
#define CODON_TABLE_H

#include <string>
#include <map>
#include <vector>

/**
 * @class CodonTable
 * @brief The genetic code - maps codons (3 nucleotides) to amino acids
 * 
 * Hardcoded lookup table for the standard genetic code.
 * The genetic code is universal across all organisms.
 * 
 * Example entries:
 * - "ATG" → 'M' (Methionine, START codon)
 * - "AAA" → 'K' (Lysine)
 * - "TAA" → '*' (STOP codon)
 */
class CodonTable {
private:
    std::map<std::string, char> codon_table_;
    
    void initializeCodonTable();

public:
    // Constructor
    CodonTable();
    
    // Core translation
    char translateCodon(const std::string& codon) const;
    
    // Codon validation
    bool isValidCodon(const std::string& codon) const;
    
    // Start/Stop detection
    bool isStartCodon(const std::string& codon) const;
    bool isStopCodon(const std::string& codon) const;
    
    // Getters for special codons
    std::string getStartCodon() const; //Get the start Codon 
    std::vector<std::string> getStopCodons() const; //Get the stop Codons

    
};

#endif // CODON_TABLE_H