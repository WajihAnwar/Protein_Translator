#include "controller/app_controller.h"
#include <iostream>
#include <iomanip>

AppController::AppController() {}

void AppController::printSeparator() const {
    std::cout << "────────────────────────────────────────────────\n";
}

void AppController::processSequence(const Sequence& seq, bool verbose, bool visualize) const {
    if (!seq.isValid()) {
        std::cerr << "Error: invalid DNA sequence";
        if (!seq.getName().empty())
            std::cerr << " '" << seq.getName() << "'";
        std::cerr << " (contains non-ATGC characters)\n";
        return;
    }

    TranslationResult result = translator_.translate(seq);

    if (!seq.getName().empty())
        std::cout << "Sequence : " << seq.getName() << "\n";
    if (!seq.getDescription().empty())
        std::cout << "Desc     : " << seq.getDescription() << "\n";

    std::cout << "Protein  : " << result.protein << "\n";

    if (verbose) {
        std::cout << "DNA      : " << result.dna << "\n";
        std::cout << "mRNA     : " << result.mrna << "\n";
        std::cout << "Length   : " << result.dna.size() << " bp ("
                  << result.dna.size() / 3 << " codons)\n";
        std::cout << "GC%      : " << std::fixed << std::setprecision(1)
                  << result.gcContent << "%\n";
    }

    if (visualize) {
        visualizer_.displayFull(result);
    }
}

int AppController::runFile(const std::string& filepath, bool verbose, bool visualize) const {
    std::vector<Sequence> sequences = parser_.parseFile(filepath);

    if (sequences.empty())
        return 2;

    for (size_t i = 0; i < sequences.size(); i++) {
        if (i > 0) printSeparator();
        processSequence(sequences[i], verbose, visualize);
    }

    return 0;
}

int AppController::runString(const std::string& dna, bool verbose, bool visualize) const {
    Sequence seq = parser_.parseString(dna);

    if (!seq.isValid()) {
        std::cerr << "Error: invalid DNA string (contains non-ATGC characters)\n";
        return 3;
    }

    processSequence(seq, verbose, visualize);
    return 0;
}
