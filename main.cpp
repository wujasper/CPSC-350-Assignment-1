/*
  Full Name: Jasper Wu
  Student ID: 2339715
  Chapman email: jaswu@chapman.edu
  Course number and section: 350-01
  Assignment Number: 1
*/

#include "assign1.h"

int main(int argc, char** argv){

  // make sure user input the file name
  if (argc != 2) {
    cout << " Must provide input file name " << endl;
    return -1;
  }
  string inputFileName = argv[1];
  string outputFileName = "Jasper_Wu.out";
  bool toContinue = false;
  bool openOutputFileToAppend = false;

  // while loop to process input file unitl user exit the program
  do {
    // extension object from class Assign1
    Assign1 *assign1 = new Assign1(inputFileName, outputFileName);

    // exit if there is error when open files
    bool inputFileOpenError = assign1->openFileForRead();
    bool outputFileOpenError = assign1->openFileForWrite(openOutputFileToAppend);
    if (inputFileOpenError || outputFileOpenError) {
      assign1->closeFiles();
      delete assign1;
      return -1;
    }
    if (!openOutputFileToAppend) {
      assign1->printHeader();
    }
    // compute statistics
    int sum = assign1->computeSum();
    assign1->printSum(sum);
    double mean = assign1->computeMean(sum);
    assign1->printMean(mean);
    double variance = assign1->computeVariance(mean);
    assign1->printVariance(variance);
    double standardDeviation = assign1->computeStandardDeviation(variance);
    assign1->printStandardDeviation(standardDeviation);

    // compute nucleotide probability
    assign1->printProbabilityHeader();
    double aProbability = assign1->computeProbability('A', sum);
    assign1->printProbability('A', aProbability);
    double cProbability = assign1->computeProbability('C', sum);
    assign1->printProbability('C', cProbability);
    double tProbability = assign1->computeProbability('T', sum);
    assign1->printProbability('T', tProbability);
    double gProbability = assign1->computeProbability('G', sum);
    assign1->printProbability('G', gProbability);

    // compute bigram nucleotide probability
    assign1->printBigramProbabilityHeader();
    double aabigramProbability = assign1->computeBigramProbability('A','A');
    assign1->printBigramProbability('A', 'A', aabigramProbability);
    double acbigramProbability = assign1->computeBigramProbability('A','C');
    assign1->printBigramProbability('A', 'C', aabigramProbability);
    double atbigramProbability = assign1->computeBigramProbability('A','T');
    assign1->printBigramProbability('A', 'T', aabigramProbability);
    double agbigramProbability = assign1->computeBigramProbability('A','G');
    assign1->printBigramProbability('A', 'G', aabigramProbability);
    double cabigramProbability = assign1->computeBigramProbability('C','A');
    assign1->printBigramProbability('C', 'A', aabigramProbability);
    double ccbigramProbability = assign1->computeBigramProbability('C','C');
    assign1->printBigramProbability('C', 'C', aabigramProbability);
    double ctbigramProbability = assign1->computeBigramProbability('C','T');
    assign1->printBigramProbability('C', 'T', aabigramProbability);
    double cgbigramProbability = assign1->computeBigramProbability('C','G');
    assign1->printBigramProbability('C', 'G', aabigramProbability);
    double tabigramProbability = assign1->computeBigramProbability('T','A');
    assign1->printBigramProbability('T', 'A', aabigramProbability);
    double tcbigramProbability = assign1->computeBigramProbability('T','C');
    assign1->printBigramProbability('T', 'C', aabigramProbability);
    double ttbigramProbability = assign1->computeBigramProbability('T','T');
    assign1->printBigramProbability('T', 'T', aabigramProbability);
    double tgbigramProbability = assign1->computeBigramProbability('T','G');
    assign1->printBigramProbability('T', 'G', aabigramProbability);
    double gabigramProbability = assign1->computeBigramProbability('G','A');
    assign1->printBigramProbability('G', 'A', aabigramProbability);
    double gcbigramProbability = assign1->computeBigramProbability('G','C');
    assign1->printBigramProbability('G', 'C', aabigramProbability);
    double gtbigramProbability = assign1->computeBigramProbability('G','T');
    assign1->printBigramProbability('G', 'T', aabigramProbability);
    double ggbigramProbability = assign1->computeBigramProbability('G','G');
    assign1->printBigramProbability('G', 'G', aabigramProbability);

    // generate and print 1000 DNA strings
    assign1->printDnaStringHeader();
    for (int i = 0; i < 1000; ++i) {
      int dnaStringLength = assign1->generateDnaStringLength(mean, variance);
      string dnaString = assign1->generateDnaString(dnaStringLength, aProbability, cProbability, tProbability, gProbability);
      assign1->printDnaString(dnaString);
    }

    // close the file and delete the assign1 object
    assign1->closeFiles();
    delete assign1;

    // check user if continue the program
    toContinue = askToContinue();
    if (toContinue) {
      inputFileName = askForInputFile();
      openOutputFileToAppend = true;
    }
  } while (toContinue);

  return 0;
}
