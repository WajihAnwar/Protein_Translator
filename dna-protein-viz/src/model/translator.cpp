#include "model/translator.h"
#include <cctype>
#include <algorithm>

Translator::Translator() {}

std::string Translator::normalizeSequence(const std::string& sequence) const {
    std::string result = sequence;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

std::string Translator::transcribeDNAtoRNA(const std::string& dna) const {
    std::string normalized = normalizeSequence(dna);
    std::string mrna;
    mrna.reserve(normalized.size());

    for (char nucleotide : normalized) {
        mrna += (nucleotide == 'T') ? 'U' : nucleotide;
    }
    return mrna;
}

std::string Translator::translateRNA(const std::string& mrna) const {
    std::string normalized = normalizeSequence(mrna);
    std::string protein;

    for (size_t i = 0; i + 2 < normalized.size(); i += 3) {
        std::string rnaCodon = normalized.substr(i, 3);

        // Convert RNA codon (U) back to DNA codon (T) for table lookup
        std::string dnaCodon;
        for (char c : rnaCodon) {
            dnaCodon += (c == 'U') ? 'T' : c;
        }

        char aminoAcid = codonTable_.translateCodon(dnaCodon);
        if (aminoAcid == '*') {
            break;
        }
        protein += aminoAcid;
    }
    return protein;
}

double Translator::calculateGCContent(const std::string& dna) const {
    if (dna.empty()) return 0.0;

    std::string normalized = normalizeSequence(dna);
    int gcCount = 0;

    for (char nucleotide : normalized) {
        if (nucleotide == 'G' || nucleotide == 'C') {
            gcCount++;
        }
    }
    return (static_cast<double>(gcCount) / normalized.size()) * 100.0;
}

TranslationResult Translator::translate(const Sequence& sequence) const {
    TranslationResult result;
    result.dna = normalizeSequence(sequence.getDNA());
    result.mrna = transcribeDNAtoRNA(result.dna);
    result.protein = translateRNA(result.mrna);
    result.gcContent = calculateGCContent(result.dna);
    return result;
}
