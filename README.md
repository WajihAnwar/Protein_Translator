# DNA Protein Translator & Visualizer

CLI tool that takes a DNA sequence and translates it into a protein, with optional ASCII visualization. Written in C++17 with no external dependencies.

```
DNA  -->  mRNA  -->  Protein
ATG       AUG        M (Methionine)
AAA       AAA        K (Lysine)
TAA       UAA        * (STOP)
```

## Quick start

```bash
cd dna-protein-viz

# build
g++ -std=c++17 -Iinclude -o build/dna-protein-viz.exe \
  src/main.cpp src/model/codon_table.cpp src/model/sequence.cpp \
  src/model/translator.cpp src/model/fasta_parser.cpp \
  src/controller/app_controller.cpp src/view/visualizer.cpp

# run
./build/dna-protein-viz.exe -s ATGAAAGGGCCCTTTTGCGATTAA
./build/dna-protein-viz.exe sequences.fasta -v -V
```

Or with CMake: `cmake -S . -B build && cmake --build build`

## Usage

```
dna-protein-viz <input.fasta> [options]
dna-protein-viz -s <DNA_STRING> [options]
```

| Flag | What it does |
|------|--------------|
| `-s <STRING>` | Translate a DNA string directly |
| `-v` | Show mRNA, GC%, and stats |
| `-V` | Show full ASCII visualization |
| `-h` | Help |

## What the output means

**Default** -- just gives you the protein:

```
Protein  : MKGPFCD
```

**Verbose** (`-v`) -- shows the intermediate steps:

```
DNA      : ATGAAAGGGCCCTTTTGCGATTAA
mRNA     : AUGAAAGGGCCCUUUUGCGAUUAA
Length   : 24 bp (8 codons)
GC%      : 41.7%
```

**Visualization** (`-V`) -- four sections:

*Alignment* -- DNA, mRNA, and protein lined up codon-by-codon:
```
  DNA:    ATG AAA GGG CCC TTT TGC GAT TAA
  mRNA:   AUG AAA GGG CCC UUU UGC GAU UAA
  Protein: M   K   G   P   F   C   D   *
```

*Codon Map* -- each triplet with its amino acid name:
```
1     ATG     AUG     M     Methionine
2     AAA     AAA     K     Lysine
...
8     TAA     UAA     *     STOP
```

*Nucleotide Composition* -- frequency of each base:
```
  A [############----------------------------] 29.2% (7)
  T [############----------------------------] 29.2% (7)
  G [##########------------------------------] 25.0% (6)
  C [#######---------------------------------] 16.7% (4)
```

*GC Content* -- ratio of G+C vs A+T (higher GC = more thermally stable DNA):
```
  GC [#################-----------------------] 41.7%
  AT [#######################-----------------] 58.3%
```

## Test data

Sample files in `test_data/`:

| File | What it tests |
|------|---------------|
| `single_sequence.fasta` | One gene, basic usage |
| `multi_sequence.fasta` | Three genes in one file |
| `high_gc.fasta` | GC-rich sequence (~78%) |
| `low_gc.fasta` | AT-rich sequence (~4% GC) |
| `invalid_sequence.fasta` | Bad input, error handling |

## Project structure

```
dna-protein-viz/
├── include/
│   ├── model/
│   │   ├── sequence.h          DNA sequence data model
│   │   ├── codon_table.h       64-codon genetic code lookup
│   │   ├── translator.h        DNA -> mRNA -> Protein pipeline
│   │   └── fasta_parser.h      FASTA file reader
│   ├── view/
│   │   └── visualizer.h        ASCII visualization engine
│   └── controller/
│       └── app_controller.h    CLI orchestration
├── src/
│   ├── main.cpp                Entry point + arg parsing
│   ├── model/
│   │   ├── sequence.cpp
│   │   ├── codon_table.cpp
│   │   ├── translator.cpp
│   │   └── fasta_parser.cpp
│   ├── view/
│   │   └── visualizer.cpp
│   └── controller/
│       └── app_controller.cpp
├── test_data/                  Sample .fasta files
├── build/                      Compiled output
└── CMakeLists.txt
```

Follows MVC: model handles data & logic, view handles terminal output, controller ties them together.

## Biology refresher

DNA is made up of four nucleotide bases:

- **A** (Adenine) and **T** (Thymine) -- these always pair together (A=T)
- **G** (Guanine) and **C** (Cytosine) -- these always pair together (G≡C)

G-C pairs are held together by three hydrogen bonds, while A-T pairs only have two. This means DNA with more G and C bases is physically stronger and harder to pull apart (higher melting temperature). That's why GC content matters -- it tells you about the structural stability of the DNA.

The translation process:

1. **Transcription** -- the cell copies DNA into mRNA. Every T becomes U (uracil replaces thymine).
2. **Translation** -- ribosomes read the mRNA three bases at a time (each triplet is a codon). Each codon maps to a specific amino acid. The chain starts at ATG (methionine) and ends when it hits a stop codon (TAA, TAG, or TGA).
3. **GC Content** -- the percentage of G+C bases in a sequence. High GC (>60%) means more stable DNA, common in heat-loving organisms. Low GC (<40%) means less stable, typical of AT-rich genomes.
