#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <string>
#include "model/translator.h"
#include "model/codon_table.h"

class Visualizer {
public:
    Visualizer();

    void displayFull(const TranslationResult& result) const;
    void displayCodonMap(const TranslationResult& result) const;
    void displayNucleotideComposition(const std::string& dna) const;
    void displayAlignment(const TranslationResult& result) const;
    void displayGCBar(double gcContent) const;

private:
    CodonTable codonTable_;
    int terminalWidth_;

    void printHeader(const std::string& title) const;
    void printSeparator() const;
    std::string makeBar(double fraction, int maxWidth) const;
};

#endif
