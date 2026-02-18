#include "view/visualizer.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

static const int BAR_WIDTH = 40;

Visualizer::Visualizer() : terminalWidth_(60) {}

std::string Visualizer::makeBar(double fraction, int maxWidth) const {
    int filled = std::min(static_cast<int>(fraction * maxWidth + 0.5), maxWidth);
    return "[" + std::string(filled, '#') + std::string(maxWidth - filled, '-') + "]";
}

void Visualizer::printHeader(const std::string& title) const {
    std::cout << "\n=== " << title << " ===\n\n";
}

void Visualizer::printSeparator() const {
    std::cout << std::string(terminalWidth_, '-') << "\n";
}

void Visualizer::displayCodonMap(const TranslationResult& result) const {
    printHeader("CODON MAP");
    std::cout << std::left
              << std::setw(6) << "#"
              << std::setw(8) << "DNA"
              << std::setw(8) << "mRNA"
              << std::setw(6) << "AA"
              << "Name\n";
    printSeparator();

    int codons = static_cast<int>(result.dna.size()) / 3;
    for (int i = 0; i < codons; i++) {
        std::string dna = result.dna.substr(i * 3, 3);
        std::string rna = result.mrna.substr(i * 3, 3);
        char aa = codonTable_.translateCodon(dna);

        std::cout << std::setw(6) << (i + 1)
                  << std::setw(8) << dna
                  << std::setw(8) << rna
                  << std::setw(6) << std::string(1, aa)
                  << codonTable_.getAminoAcidName(aa) << "\n";
        if (aa == '*') break;
    }
    std::cout << "\n";
}

void Visualizer::displayNucleotideComposition(const std::string& dna) const {
    printHeader("NUCLEOTIDE COMPOSITION");

    int counts[4] = {};
    for (char c : dna) {
        if (c == 'A') counts[0]++;
        else if (c == 'T') counts[1]++;
        else if (c == 'G') counts[2]++;
        else if (c == 'C') counts[3]++;
    }

    int total = static_cast<int>(dna.size());
    const char labels[] = {'A', 'T', 'G', 'C'};
    for (int i = 0; i < 4; i++) {
        double frac = total > 0 ? static_cast<double>(counts[i]) / total : 0.0;
        std::cout << "  " << labels[i] << " " << makeBar(frac, BAR_WIDTH)
                  << " " << std::fixed << std::setprecision(1)
                  << frac * 100.0 << "% (" << counts[i] << ")\n";
    }
    std::cout << "\n  Total: " << total << " bp\n\n";
}

void Visualizer::displayGCBar(double gcContent) const {
    printHeader("GC CONTENT");
    double frac = gcContent / 100.0;
    std::cout << "  GC " << makeBar(frac, BAR_WIDTH) << " "
              << std::fixed << std::setprecision(1) << gcContent << "%\n"
              << "  AT " << makeBar(1.0 - frac, BAR_WIDTH) << " "
              << 100.0 - gcContent << "%\n\n";
}

void Visualizer::displayAlignment(const TranslationResult& result) const {
    printHeader("SEQUENCE ALIGNMENT");

    int codons = static_cast<int>(result.dna.size()) / 3;
    int protLen = static_cast<int>(result.protein.size());
    const int perRow = 10;

    for (int start = 0; start < codons; start += perRow) {
        int end = std::min(start + perRow, codons);

        std::cout << std::setw(10) << "" << (start * 3 + 1);
        int span = (end - start) * 4 - 2;
        if (span > 0)
            std::cout << std::string(span, ' ') << end * 3;
        std::cout << "\n";

        std::cout << "  DNA:    ";
        for (int i = start; i < end; i++)
            std::cout << (i > start ? " " : "") << result.dna.substr(i * 3, 3);
        std::cout << "\n  mRNA:   ";
        for (int i = start; i < end; i++)
            std::cout << (i > start ? " " : "") << result.mrna.substr(i * 3, 3);
        std::cout << "\n  Protein:";
        for (int i = start; i < end; i++) {
            if (i < protLen)
                std::cout << " " << result.protein[i] << "  ";
            else { std::cout << " *  "; break; }
        }
        std::cout << "\n\n";
    }
}

void Visualizer::displayFull(const TranslationResult& result) const {
    displayAlignment(result);
    displayCodonMap(result);
    displayNucleotideComposition(result.dna);
    displayGCBar(result.gcContent);
}
