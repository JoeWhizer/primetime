#include <iostream>
#include <vector>
#include <fstream>

constexpr char calcBrute    = 'b';
constexpr char calcSieve    = 's';
constexpr char progRange    = 'r';
constexpr char progCount    = 'c';
constexpr char outputFile   = 'f';
constexpr char outputScreen = 's';

std::string filename = "primes.txt";
int Sieves[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

char GetCalculationMethod();
char GetProgressMethod();
char GetOutputMethod();
void GetRange(int &min, int &max);
void GetPositions(int &start, int &count);
void FillVector(int min, int max, std::vector<int> &numbers);
void SieveNumbers(std::vector<int> numbers, std::vector<int> &primes);
void FindPrimesRange(int min, int max, std::vector<int> &primes);
void FindPrimesCount(int start, int amount, std::vector<int> &primes);
void SavePrimesToFile(std::vector<int> &primes);
void PrintPrimes(std::vector<int> &primes);
std::string FormatLineCounter(int lineCount, int maxValue);

int main() 
{
    bool check = false;
    char calculation, progress, output;
    int min = 1, max = 100, start = 1, count = 1;
    std::vector<int> numbers;
    std::vector<int> primes;

    std::cout << "Welcome to PrimeTime!\n";
    progress = GetProgressMethod();
    if (progress == progRange) {
        GetRange(min, max);
        calculation = GetCalculationMethod();
    } else if (progress == progCount) {
        GetPositions(start, count);
        calculation = calcBrute;
    }

    std::cout << "Calculate prime numbers, please wait...\n";
    if (calculation == calcBrute) {
        if (progress == progRange)
            FindPrimesRange(min, max, primes);
        else if (progress == progCount)
            FindPrimesCount(start, count, primes);
    } else if (calculation == calcSieve) {
        FillVector(min, max, numbers);
        SieveNumbers(numbers, primes);
    }
    std::cout << "done\n";
    std::cout << "Found " << primes.size() << " prime numbers\n";

    output = GetOutputMethod();
    if (output == outputFile) {
        SavePrimesToFile(primes);
        std::cout << "Saved all prime numbers to '" << filename << "'\n";
    } else if (output == outputScreen) {
        PrintPrimes(primes);
    }

    std::cout << std::endl;
    exit(EXIT_SUCCESS);
}

char GetCalculationMethod()
{
    bool check = false;
    char method;
    while (!check) {
        std::cout << "Choose a calculation method (Brute force '" << calcBrute << "' - Sieve '" << calcSieve << "'): ";
        std::cin >> method;
        (method == calcBrute || method == calcSieve) ? check = true : check = false;
        if (!std::cin) exit(EXIT_FAILURE);
    }
    return method;
}

char GetProgressMethod()
{
    bool check = false;
    char method;
    while (!check) {
        std::cout << "Choose a progress method (Range '" << progRange << "' - Count '" << progCount << "'): ";
        std::cin >> method;
        (method == progRange || method == progCount) ? check = true : check = false;
        if (!std::cin) exit(EXIT_FAILURE);
    }
    return method;
}

char GetOutputMethod()
{
    bool check = false;
    char method;
    while (!check) {
        std::cout << "Choose output method (File '" << outputFile << "' - Screen '" << outputScreen << "'): ";
        std::cin >> method;
        (method == outputFile || method == outputScreen) ? check = true : check = false;
        if (!std::cin) exit(EXIT_FAILURE);
    }
    return method;
}

void GetRange(int &min, int &max)
{
    bool check = false;
    while(!check) {
        std::cout << "Please enter a min value: ";
        std::cin >> min;
        std::cout << "Please enter a max value: ";
        std::cin >> max;
        (min < max && min > 0) ? check = true : check = false;
        if (!std::cin) exit(EXIT_FAILURE);
    }
}

void GetPositions(int &start, int &count)
{
    bool check = false;
    while(!check) {
        std::cout << "Please enter a number to start from: ";
        std::cin >> start;
        std::cout << "How many prime numbers should be calculated: ";
        std::cin >> count;
        (start > 0 && count > 0) ? check = true : check = false;
        if (!std::cin) exit(EXIT_FAILURE);
    }
}

void FillVector(int min, int max, std::vector<int> &numbers)
{
    for (int i = min; i <= max; i++)
        numbers.push_back(i);
}

void SieveNumbers(std::vector<int> numbers, std::vector<int> &primes)
{
    std::vector<int> temp;
    int counter = 0;
    
    primes = numbers;
    for (int sieve : Sieves) {
        temp.clear();
        for (int number : primes) {
            if (number == sieve || number % sieve != 0)
                temp.push_back(number);
        }
        primes = temp;
    }
}

void FindPrimesRange(int min, int max, std::vector<int> &primes)
{
    for (int i = min; i < max; i++) {        
        bool notPrime = false;
        for (int j = 2; j <= i; j++) {
            if (i != 1 && i != j) {
                if (i % j == 0) {
                    notPrime = true;
                    break;
                }
            }
        }
        if (i != 1 && !notPrime) { 
            primes.push_back(i);
        }
    }
}

void FindPrimesCount(int start, int amount, std::vector<int> &primes)
{
    int counter = 0;
    for (int i = start; i <= INT32_MAX; i++) {        
        bool notPrime = false;
        for (int j = 2; j <= i; j++) {
            if (i != 1 && i != j) {
                if (i % j == 0) {
                    notPrime = true;
                    break;
                }
            }
        }
        if (i != 1 && !notPrime) { 
            primes.push_back(i);
            ++counter;
        }
        if (counter == amount) {
            return;
        }
    }
}

void SavePrimesToFile(std::vector<int> &primes)
{

    std::ofstream file(filename, std::ofstream::out);
    for (int i = 0; i < primes.size(); i++) {
        file << FormatLineCounter(i +1, primes.size()) << primes[i] << "\n";
    }
    file.close();
}

void PrintPrimes(std::vector<int> &primes)
{
    for (int prime : primes) {
        std::cout << prime << "\n";
    }
}

std::string FormatLineCounter(int lineCount, int maxValue)
{
    std::string str_lineCount = std::to_string(lineCount);
    std::string str_maxValue = std::to_string(maxValue);
    
    int spaces = str_maxValue.size() - str_lineCount.size();
    std::string resultValue = "";
    for (int i = 0; i < spaces; i++) {
        resultValue += "0";
    }
    resultValue += str_lineCount;
    resultValue += ": ";
    return resultValue;
}