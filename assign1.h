/*
  Full Name: Jasper Wu
  Student ID: 2339715
  Chapman email: jaswu@chapman.edu
  Course number and section: 350-01
  Assignment Number: 1
*/

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

class Assign1{

private:
  string inputFileName;
  string outputFileName;
  ifstream inputFileStream;
  ofstream outputFileStream;

  void rewindInputFile();

public:
  Assign1(string inputFileName, string outputFileName);
  ~Assign1();

  bool openFileForRead();
  bool openFileForWrite(bool append);
  void closeFiles();

  int computeSum();
  double computeMean(int sum);
  double computeVariance(double mean);
  double computeStandardDeviation(double variance);
  double computeProbability(char nucleotide, int sum);
  double computeBigramProbability(char bigram0, char bigram1);
  void printHeader();
  void printSum(int sum);
  void printMean(double mean);
  void printVariance(double variance);
  void printStandardDeviation(double standardDeviation);
  void printProbability(char nucleotide, double probability);
  void printProbabilityHeader();
  void printBigramProbability(char bigram0, char bigram1, double probability);
  void printBigramProbabilityHeader();
  int generateDnaStringLength(double mean, double variance);
  string generateDnaString(int length, double aProb, double cProb, double tProb, double gProb);
  void printDnaString(string dnaString);
  void printDnaStringHeader();

};

bool askToContinue();
string askForInputFile();
