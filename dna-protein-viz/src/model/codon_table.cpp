#include "codon_table.h"

/**
 * Constructor - initializes the genetic code table
 */
CodonTable::CodonTable() {
    initializeCodonTable();
}

/**
 * Initialize all 64 codons (the standard genetic code)
 */
void CodonTable::initializeCodonTable() {
    // === TTT, TTC (Phenylalanine - F) ===
    codon_table_["TTT"] = 'F';
    codon_table_["TTC"] = 'F';
    
    // === TTA, TTG (Leucine - L) ===
    codon_table_["TTA"] = 'L';
    codon_table_["TTG"] = 'L';
    
    // === TCT, TCC, TCA, TCG (Serine - S) ===
    codon_table_["TCT"] = 'S';
    codon_table_["TCC"] = 'S';
    codon_table_["TCA"] = 'S';
    codon_table_["TCG"] = 'S';
    
    // === TAT, TAC (Tyrosine - Y) ===
    codon_table_["TAT"] = 'Y';
    codon_table_["TAC"] = 'Y';
    
    // === TAA, TAG (STOP codons) ===
    codon_table_["TAA"] = '*';
    codon_table_["TAG"] = '*';
    
    // === TGT, TGC (Cysteine - C) ===
    codon_table_["TGT"] = 'C';
    codon_table_["TGC"] = 'C';
    
    // === TGA (STOP codon) ===
    codon_table_["TGA"] = '*';
    
    // === TGG (Tryptophan - W) ===
    codon_table_["TGG"] = 'W';
    
    // === CTT, CTC, CTA, CTG (Leucine - L) ===
    codon_table_["CTT"] = 'L';
    codon_table_["CTC"] = 'L';
    codon_table_["CTA"] = 'L';
    codon_table_["CTG"] = 'L';
    
    // === CCT, CCC, CCA, CCG (Proline - P) ===
    codon_table_["CCT"] = 'P';
    codon_table_["CCC"] = 'P';
    codon_table_["CCA"] = 'P';
    codon_table_["CCG"] = 'P';
    
    // === CAT, CAC (Histidine - H) ===
    codon_table_["CAT"] = 'H';
    codon_table_["CAC"] = 'H';
    
    // === CAA, CAG (Glutamine - Q) ===
    codon_table_["CAA"] = 'Q';
    codon_table_["CAG"] = 'Q';
    
    // === CGT, CGC, CGA, CGG (Arginine - R) ===
    codon_table_["CGT"] = 'R';
    codon_table_["CGC"] = 'R';
    codon_table_["CGA"] = 'R';
    codon_table_["CGG"] = 'R';
    
    // === ATT, ATC, ATA (Isoleucine - I) ===
    codon_table_["ATT"] = 'I';
    codon_table_["ATC"] = 'I';
    codon_table_["ATA"] = 'I';
    
    // === ATG (Methionine - M, START codon) ===
    codon_table_["ATG"] = 'M';
    
    // === ACT, ACC, ACA, ACG (Threonine - T) ===
    codon_table_["ACT"] = 'T';
    codon_table_["ACC"] = 'T';
    codon_table_["ACA"] = 'T';
    codon_table_["ACG"] = 'T';
    
    // === AAT, AAC (Asparagine - N) ===
    codon_table_["AAT"] = 'N';
    codon_table_["AAC"] = 'N';
    
    // === AAA, AAG (Lysine - K) ===
    codon_table_["AAA"] = 'K';
    codon_table_["AAG"] = 'K';
    
    // === AGT, AGC (Serine - S) ===
    codon_table_["AGT"] = 'S';
    codon_table_["AGC"] = 'S';
    
    // === AGA, AGG (Arginine - R) ===
    codon_table_["AGA"] = 'R';
    codon_table_["AGG"] = 'R';
    
    // === GTT, GTC, GTA, GTG (Valine - V) ===
    codon_table_["GTT"] = 'V';
    codon_table_["GTC"] = 'V';
    codon_table_["GTA"] = 'V';
    codon_table_["GTG"] = 'V';
    
    // === GCT, GCC, GCA, GCG (Alanine - A) ===
    codon_table_["GCT"] = 'A';
    codon_table_["GCC"] = 'A';
    codon_table_["GCA"] = 'A';
    codon_table_["GCG"] = 'A';
    
    // === GAT, GAC (Aspartic acid - D) ===
    codon_table_["GAT"] = 'D';
    codon_table_["GAC"] = 'D';
    
    // === GAA, GAG (Glutamic acid - E) ===
    codon_table_["GAA"] = 'E';
    codon_table_["GAG"] = 'E';
    
    // === GGT, GGC, GGA, GGG (Glycine - G) ===
    codon_table_["GGT"] = 'G';
    codon_table_["GGC"] = 'G';
    codon_table_["GGA"] = 'G';
    codon_table_["GGG"] = 'G';
}

/**
 * Translate a single codon to an amino acid
 * Returns 'X' if codon is not found (invalid)
 */
char CodonTable::translateCodon(const std::string& codon) const {
    auto it = codon_table_.find(codon);
    if (it != codon_table_.end()) {
        return it->second;
    }
    return 'X';  // Unknown/invalid codon
}

/**
 * Check if a codon exists in the table
 */
bool CodonTable::isValidCodon(const std::string& codon) const {
    return codon_table_.find(codon) != codon_table_.end();
}

/**
 * Check if a codon is a start codon (ATG)
 */
bool CodonTable::isStartCodon(const std::string& codon) const {
    return codon == "ATG";
}

/**
 * Check if a codon is a stop codon (TAA, TAG, TGA)
 */
bool CodonTable::isStopCodon(const std::string& codon) const {
    return codon == "TAA" || codon == "TAG" || codon == "TGA";
}

/**
 * Get the start codon
 */
std::string CodonTable::getStartCodon() const {
    return "ATG";
}

/**
 * Get all stop codons
 */
std::vector<std::string> CodonTable::getStopCodons() const {
    return {"TAA", "TAG", "TGA"};
}

/**
 * Convert single-letter amino acid code to full name
 */
std::string CodonTable::getAminoAcidName(char aminoAcid) const {
    switch(aminoAcid) {
        // Standard amino acids (alphabetical)
        case 'A': return "Alanine";
        case 'C': return "Cysteine";
        case 'D': return "Aspartic acid";
        case 'E': return "Glutamic acid";
        case 'F': return "Phenylalanine";
        case 'G': return "Glycine";
        case 'H': return "Histidine";
        case 'I': return "Isoleucine";
        case 'K': return "Lysine";
        case 'L': return "Leucine";
        case 'M': return "Methionine";
        case 'N': return "Asparagine";
        case 'P': return "Proline";
        case 'Q': return "Glutamine";
        case 'R': return "Arginine";
        case 'S': return "Serine";
        case 'T': return "Threonine";
        case 'V': return "Valine";
        case 'W': return "Tryptophan";
        case 'Y': return "Tyrosine";
        
        // Special cases
        case '*': return "STOP";
        case 'X': return "Unknown";
        
        default: return "Unknown";
    }
}