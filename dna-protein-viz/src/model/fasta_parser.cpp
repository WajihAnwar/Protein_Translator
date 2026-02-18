#include "model/fasta_parser.h"
#include <fstream>
#include <iostream>
#include <cctype>

void FastaParser::parseHeader(const std::string& line,
                              std::string& name,
                              std::string& description) const {
    std::string content = line.substr(1);
    size_t pos = content.find_first_of(" \t");
    if (pos == std::string::npos) {
        name = content;
        description = "";
    } else {
        name = content.substr(0, pos);
        description = content.substr(pos + 1);
    }
}

std::vector<Sequence> FastaParser::parseFile(const std::string& filepath) const {
    std::vector<Sequence> sequences;
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Error: cannot open file '" << filepath << "'\n";
        return sequences;
    }

    std::string line, name, desc, dna;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == ';') continue;
        if (!line.empty() && line.back() == '\r') line.pop_back();

        if (line[0] == '>') {
            if (!dna.empty())
                sequences.emplace_back(dna, name, desc);
            parseHeader(line, name, desc);
            dna.clear();
        } else {
            for (char c : line)
                if (!std::isspace(static_cast<unsigned char>(c)))
                    dna += c;
        }
    }

    if (!dna.empty())
        sequences.emplace_back(dna, name, desc);

    if (sequences.empty())
        std::cerr << "Warning: no sequences found in '" << filepath << "'\n";

    return sequences;
}

Sequence FastaParser::parseString(const std::string& dna) const {
    std::string cleaned;
    for (char c : dna)
        if (!std::isspace(static_cast<unsigned char>(c)))
            cleaned += c;
    return Sequence(cleaned, "cli_input", "Direct CLI input");
}
