/*
  Full Name: Jasper Wu
  Student ID: 2339715
  Chapman email: jaswu@chapman.edu
  Course number and section: 350-01
  Assignment Number: 1
*/

#include "assign1.h"

/*
 Functions for class Assign1
*/
// constructor to set input file name and output file name
Assign1::Assign1(string inFileName, string outFileName){
  this->inputFileName = inFileName;
  this->outputFileName = outFileName;
};
// destructor
Assign1::~Assign1(){
}
// open input file for read using ifstream
bool Assign1::openFileForRead(){
  inputFileStream.open(inputFileName);
  if (!inputFileStream) {
    cout << inputFileName << " cannot be opened " << endl;
    return true;
  }
  return false;
}
// open output file for write using ofstream
// option to append to the file
bool Assign1::openFileForWrite(bool append){
  if (append) {
    outputFileStream.open(outputFileName, ios::app);
  }
  else {
    outputFileStream.open(outputFileName);
  }
  if (!outputFileStream) {
    cout << outputFileName << " cannot be opened " << endl;
    return true;
  }
  return false;
}
// close opened files
void Assign1::closeFiles() {
  inputFileStream.close();
  outputFileStream.close();
}
// rewind to the beginning of the input file
void Assign1::rewindInputFile() {
  inputFileStream.clear();
  inputFileStream.seekg(0);
}
// compute sum
int Assign1::computeSum() {
  string line;
  int sum = 0;

  rewindInputFile();
  while (getline(inputFileStream, line)) {
    sum += line.length();
  }
  return sum;
}
// compute mean
double Assign1::computeMean(int sum) {
  string line;
  int totalN = 0;

  rewindInputFile();
  while (getline(inputFileStream, line)) {
    ++totalN;
  }
  double mean = (double)sum / (double)totalN;
  return mean;
}
// compute variance
double Assign1::computeVariance(double mean) {
  string line;
  double total = 0;
  int totalN = 0;

  rewindInputFile();
  while (getline(inputFileStream, line)) {
    total += pow(((double)line.length() - mean), 2);
    ++totalN;
  }
  double variance = total / (double)totalN;
  return variance;
}
// compute standard deviation
double Assign1::computeStandardDeviation(double variance) {
  double standardDeviation = sqrt(variance);
  return standardDeviation;
}
// compute nucleotide probability
double Assign1::computeProbability(char nucleotide, int sum) {
  string line;
  int total = 0;

  rewindInputFile();
  while (getline(inputFileStream, line)) {
    for (int i = 0; i < line.length(); ++i) {
      if (tolower(line[i]) == tolower(nucleotide)) {
        ++total;
      }
    }
  }
  double probability = (double)total / (double)sum;
  return probability;
}
// compute bigram nucleotide probability
double Assign1::computeBigramProbability(char bigram0, char bigram1) {
  string line;
  int total = 0;
  int sum = 0;

  rewindInputFile();
  while (getline(inputFileStream, line)) {
    if (line.length() % 2 == 1) {
      line += line[0];
    }
    for (int i = 0; i < line.length(); i += 2) {
      ++sum;
      if (tolower(line[i]) == tolower(bigram0) &&
          tolower(line[i+1]) == tolower(bigram1)) {
        ++total;
      }
    }
  }
  double bigramProbability = (double)total / (double)sum;
  return bigramProbability;
}
// print file header to output file
void Assign1::printHeader() {
  outputFileStream << "Name: Jasper Wu " << endl <<
                      "Student ID: 2339715 " << endl <<
                      "Chapman email: jaswu@chapman.edu " << endl <<
                      "Course number and section: 350-01 " << endl <<
                      "Assignment: 1 - assign1.cpp " << endl << endl;
}
// print sum to output file
void Assign1::printSum(int sum) {
  outputFileStream << "The Sum of the length of the DNA strings is: "
                   << sum << endl;
}
// print mean to output file
void Assign1::printMean(double mean) {
  outputFileStream << "The Mean of the length of the DNA strings is: "
                   << mean << endl;
}
// print variance to output file
void Assign1::printVariance(double variance) {
  outputFileStream << "The variance of the length of the DNA strings is: "
                   << variance << endl;
}
// print standard deviation to output file
void Assign1::printStandardDeviation(double standardDeviation) {
  outputFileStream << "The Standard Deviation of the length of the DNA strings is: "
                   << standardDeviation << endl;
}
// print nucleotide probability to output file
void Assign1::printProbability(char nucleotide, double probability) {
  outputFileStream << nucleotide << ":\t\t" << probability << endl;
}
// print bigram nucleotide probability to output file
void Assign1::printBigramProbability(char bigram0, char bigram1, double probability) {
  outputFileStream << bigram0 <<  bigram1 << ":\t\t" << probability << endl;
}
// print nucleotide probability header to output file
void Assign1::printProbabilityHeader() {
  outputFileStream << "Here is the relative probability of each nucleotide: " << endl
                   << endl;
}
// print bigram nucleotide probability header to output file
void Assign1::printBigramProbabilityHeader() {
  outputFileStream << endl << "Here is the relative probability of each nucleotide bigram: "
                   << endl;
}
// generate DNA string length using Gaussian distribution
int Assign1::generateDnaStringLength(double mean, double variance) {
  // generate number between 0 and 1
  double a = (double)rand() / (double)RAND_MAX;
  // generate number between 0 and 1
  double b = (double)rand() / (double)RAND_MAX;
  double c = sqrt(-2 * log(a)) * cos(2 * M_PI * b);
  double d = (sqrt(variance) * c) + mean;
  return (int)d;
}
// generate DNA string
string Assign1::generateDnaString(int length, double aProb, double cProb, double tProb, double gProb) {
  string dnaString = "";

  // compute nucleotide count based on the probability and DNA string length
  double aCount = aProb * length;
  double cCount = cProb * length;
  double tCount = tProb * length;
  double gCount = gProb * length;

  // generate random number to select which nucleotide to append to DNA string
  for (int i = 0; i < length; ++i) {
    int randomNum = (int)(((double)rand() / (double)RAND_MAX) * 4);
    int select;

    // find the next nucleotide that has count greater and equal than 1
    // if the selected nucleotide has count less than 1 than find the next
    // nucleotide
    for (int j = 0; j < 4; ++j) {
      select = (randomNum + j) % 4;
      if (select == 0 && aCount >= 1) {
        break;
      }
      else if (select == 1 && cCount >= 1) {
        break;
      }
      else if (select == 2 && tCount >= 1) {
        break;
      }
      else if (select == 3 && gCount >= 1) {
        break;
      }
    }

    // based on the select append nucleotide to DNA string and decrement its count
    if (select == 0) {
      dnaString += 'A';
      aCount--;
    }
    else if (select == 1) {
      dnaString += 'C';
      cCount--;
    }
    else if (select == 2) {
      dnaString += 'T';
      tCount--;
    }
    else {
      dnaString += 'G';
      gCount--;
    }
  }
  return dnaString;
}
void Assign1::printDnaString(string dnaString) {
  outputFileStream << dnaString << endl;
}
void Assign1::printDnaStringHeader() {
  outputFileStream << endl << "Here are generated 1000 DNA strings:" << endl;
}

/*
  Functions for main
*/
// ask user if want to continue or exit program
bool askToContinue() {
  string userInput;
  cout << "Do you want to continue?(Y/N) ";
  cin >> userInput;
  if (userInput == "y" || userInput == "Y") {
    return true;
  }
  else {
    return false;
  }
}
// ask user to input file name
string askForInputFile() {
  string userInput;
  cout <<  "Enter input file name: ";
  cin >> userInput;
  return userInput;
}
