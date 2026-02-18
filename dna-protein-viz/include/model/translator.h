#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <string>
#include "model/codon_table.h"
#include "model/sequence.h"

struct TranslationResult {
    std::string dna;
    std::string mrna;
    std::string protein;
    double gcContent;
};

class Translator {
public:
    Translator();

    std::string transcribeDNAtoRNA(const std::string& dna) const;
    std::string translateRNA(const std::string& mrna) const;
    double calculateGCContent(const std::string& dna) const;
    TranslationResult translate(const Sequence& sequence) const;

private:
    CodonTable codonTable_;
    std::string normalizeSequence(const std::string& sequence) const;
};

#endif
