#ifndef CODON_TABLE_H
#define CODON_TABLE_H

#include <string>
#include <map>
#include <vector>

class CodonTable {
public:
    CodonTable();

    char translateCodon(const std::string& codon) const;
    bool isValidCodon(const std::string& codon) const;
    bool isStartCodon(const std::string& codon) const;
    bool isStopCodon(const std::string& codon) const;

    std::string getStartCodon() const;
    std::vector<std::string> getStopCodons() const;
    std::string getAminoAcidName(char aminoAcid) const;

private:
    std::map<std::string, char> codon_table_;
    void initializeCodonTable();
};

#endif
