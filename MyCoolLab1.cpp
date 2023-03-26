
#include <iostream>
#include "ParticipantsOfTheCompetition.hpp"
#include "BinaryTree.hpp"
#include <vector>
#include <sstream>
#include <string>
#include <fstream>

void printBinaryTree(binaryTree* root);

ParticipantsOfTheCompetition DFS(binaryTree* root, ParticipantsOfTheCompetition searchData);

ParticipantsOfTheCompetition::ParticipantsOfTheCompetition(const std::string& lastName, const std::string& firstName, const std::string& category, const std::string& country, const Date& birthYear, const unsigned short& idParticipant)
    :last_name(lastName), first_name(firstName), _category(category), _country(country), birth_year(birthYear), id_Participant(idParticipant)
{
}

ParticipantsOfTheCompetition::ParticipantsOfTheCompetition(const ParticipantsOfTheCompetition& participant) : last_name(participant.last_name), first_name(participant.first_name), _category(participant._category), _country(participant._country), birth_year(participant.birth_year), id_Participant(participant.id_Participant)
{
}

Date::Date(const unsigned short& _day, const unsigned short& _month, const unsigned short& _year)
    :day(_day), month(_month), year(_year)
{
}

Date::Date(const Date& birthYear) : day(birthYear.day), month(birthYear.month), year(birthYear.year)
{
}

const ParticipantsOfTheCompetition& ParticipantsOfTheCompetition::operator=(const ParticipantsOfTheCompetition& Participant)
{
    first_name = Participant.first_name;
    last_name = Participant.last_name;
    _category = Participant._category;
    _country = Participant._country;
    birth_year = Participant.birth_year;
    id_Participant = Participant.id_Participant;

    return *this;
}

bool ParticipantsOfTheCompetition::operator==(const ParticipantsOfTheCompetition& Participant)
{
    return first_name == Participant.first_name && last_name == Participant.last_name && _category == Participant._category && _country == Participant._country && birth_year == Participant.birth_year && id_Participant == Participant.id_Participant;
}

bool Date::operator==(const Date& birthYear)
{
    return day == birthYear.day && month == birthYear.month && year == birthYear.year;
}

const Date& Date::operator=(const Date& birthYear)
{
    day = birthYear.day;
    month = birthYear.month;
    year = birthYear.year;

    return *this;
}

std::string Date::toString() const
{
    return std::string();
}

unsigned short Date::Day() const
{
    return day;
}

unsigned short Date::Month() const
{
    return month;
}

unsigned short Date::Year() const
{
    return year;
}

std::string ParticipantsOfTheCompetition::FirstName() const
{
    return first_name;
}

std::string ParticipantsOfTheCompetition::LastName() const
{
    return last_name;
}

std::string ParticipantsOfTheCompetition::Country() const
{
    return _country;
}

std::string ParticipantsOfTheCompetition::Category() const
{
    return _category;
}

Date ParticipantsOfTheCompetition::BirthYear() const
{
    return birth_year;
}

unsigned short ParticipantsOfTheCompetition::IDParticipant() const
{
    return id_Participant;
}

std::istream& operator>>(std::istream& in, Date& birthYear)
{
    unsigned short day;
    unsigned short month;
    unsigned short year;
    char delimeter;

    in >> month >> delimeter >> day >> delimeter >> year;

    birthYear = Date(day, month, year);

    return in;
}

std::istream& operator>>(std::istream& in, ParticipantsOfTheCompetition& Participant)
{
    std::string lastName;
    getline(in, lastName, ',');
    std::string firstName;
    getline(in, firstName, ',');
    std::string country;
    getline(in, country, ',');
    std::string category;
    getline(in, category, ',');
    Date birthYear;
    in >> birthYear;
    in.ignore();
    unsigned short idParticipants;
    in >> idParticipants;

    Participant = ParticipantsOfTheCompetition(lastName, firstName, category, country, birthYear, idParticipants);
    std::string end;
    getline(in, end);

    return in;
}

std::ostream& operator<<(std::ostream& out, const Date& birthYear)
{
    out << birthYear.Month() << "/" << birthYear.Day() << "/" << birthYear.Year();

    return out;
}

std::ostream& operator<<(std::ostream& out, const ParticipantsOfTheCompetition& Participant)
{
    out << Participant.LastName() << "\t" << Participant.FirstName() << "\t" << Participant.Country() << "\t" << Participant.Category() << "\t" << Participant.BirthYear() << "\t" << Participant.IDParticipant() << std::endl;

    return out;
}

//Вывод списка участников соревнования
void PrintListOfParticipants(const std::vector<ParticipantsOfTheCompetition>& ListOfParticipants)
{
    std::cout << "Output list: " << "\n\n";
    for (int i = 0; i < ListOfParticipants.size(); i++)
    {
        std::cout << ListOfParticipants[i];
    }
}

// Вставка элемента в дерево
void insertIntoBinaryTree(binaryTree* root, ParticipantsOfTheCompetition Participant)
{
    if (Participant.LastName() < root->data.LastName())
    {
        if (root->left != nullptr)
        {
            insertIntoBinaryTree(root->left, Participant);
        }
        else
        {
            root->left = new binaryTree;
            root->left->data = Participant;
            root->left->left = nullptr;
            root->left->right = nullptr;
        }
    }
    else
    {
        if (root->right != nullptr)
        {
            insertIntoBinaryTree(root->right, Participant);
        }
        else
        {
            root->right = new binaryTree;
            root->right->data = Participant;
            root->right->left = nullptr;
            root->right->right = nullptr;
        }
    }
}

//Создание бинарного дерева
binaryTree* createBinaryTree(const std::vector<ParticipantsOfTheCompetition>& ListOfParticipants, binaryTree* root)
{

    for (unsigned short i = 1; i < ListOfParticipants.size(); i++)
    {
        insertIntoBinaryTree(root, ListOfParticipants[i]);
    }
    return root;
}

//Поиск в бинарном дереве
void SearchInBinaryTree(const std::vector<ParticipantsOfTheCompetition>& ListOfParticipants, binaryTree* root)
{

    std::cout << "\n\n\n";

    printBinaryTree(root);

    unsigned short idOfParticipant;
    std::cout << "Enter the id of participant which you want to search: ";
    std::cin >> idOfParticipant;

    if (idOfParticipant <= ListOfParticipants.size())
    {
        std::cout << DFS(root, ListOfParticipants[idOfParticipant - 1]);
    }
    else
    {
        std::cout << "You have gone beyond the boundaries of the list";
    }

    delete root;
}

//Вывод бинарного дерева
void printBinaryTree(binaryTree* root)
{
    if (root != nullptr)
    {
        printBinaryTree(root->left);
        std::cout << root->data;
        printBinaryTree(root->right);
    }
}

//Поиск в глубину
ParticipantsOfTheCompetition DFS(binaryTree* root, ParticipantsOfTheCompetition searchData)
{
    ParticipantsOfTheCompetition tmp;

    //Если значение найдено, возвращаем его
    if (root->data.LastName() == searchData.LastName())
    {
        return root->data;
    }
    
    //Если корень имеет дочерний элемент в левой ветке
    if (root->left != nullptr)
    {
        //Спускаемся в левую ветку, и левый дочерний элемент становиться корнем, и продожаем искать нужные данные
        if (DFS(root->left, searchData) == searchData)
        {
            return searchData;
        }
    }
    //Если корень имеет дочерний элемент в правой ветке
    if (root->right != nullptr)
    {
        //Спускаемся в правую ветку, и правый дочерний элемент становиться корнем, и продожаем искать нужные данные
        if (DFS(root->right, searchData) == searchData)
        {
            return searchData;
        }
    }

    return tmp;
}

//Линейный поиск
void linearSearch(const ParticipantsOfTheCompetition& Participant, const std::string& searchData)
{
    std::string copyOfLastName;

    for (unsigned short i = 0; i < searchData.size(); i++)
    {
        copyOfLastName.push_back(Participant.LastName()[i]);
    }

    if (copyOfLastName == searchData)
    {
        std::cout << Participant;
    }
}

//Сортировка вставкой
void InsertionSort(std::vector<ParticipantsOfTheCompetition>& ListOfParticipants)
{

    for (__int16 i = 1; i < ListOfParticipants.size(); i++)
    {
        ParticipantsOfTheCompetition key = ListOfParticipants.at(i);
        __int16 j = i - 1;

        while (j >= 0 && ListOfParticipants[j].FirstName() > key.FirstName())
        {
            ListOfParticipants.at(j+1) = ListOfParticipants.at(j);
            ListOfParticipants.at(j) = key;
            j--;
        }
    }
}

//Бинарный поиск
__int16 binarySearch(const std::vector<ParticipantsOfTheCompetition>& ListOfParticipants, const std::string& searchData)
{
    short leftIndex = 0;
    short rightIndex = ListOfParticipants.size() - 1;
    short midIndex;

    while (leftIndex <= rightIndex)
    {
        std::string midValue;
        midIndex = (leftIndex + rightIndex) / 2;

        midValue = ListOfParticipants.at(midIndex).FirstName();
        
        if (midValue < searchData)
        {
            leftIndex = midIndex + 1;
        }
        else if (midValue > searchData)
        {
            rightIndex = midIndex - 1;
        }
        else
        {
            return midIndex;
        }
    }
    return -1;
}

// Интерполяционный поиск
__int16 interpolationSearch(const std::vector<ParticipantsOfTheCompetition>& ListOfParticipants, const __int16& searchData)
{
    short leftIndex = 0;
    short rightIndex = ListOfParticipants.size() - 1;
    short midIndex;

    while (ListOfParticipants.at(leftIndex).IDParticipant() < searchData && ListOfParticipants.at(rightIndex).IDParticipant() > searchData)
    {
        if (ListOfParticipants.at(rightIndex).IDParticipant() == ListOfParticipants.at(leftIndex).IDParticipant())
        {
            break;
        }
        midIndex = leftIndex + ((searchData - ListOfParticipants[leftIndex].IDParticipant()) * (rightIndex - leftIndex)) / (ListOfParticipants[rightIndex].IDParticipant() - ListOfParticipants[leftIndex].IDParticipant());

        if (ListOfParticipants.at(midIndex).IDParticipant() < searchData)
        {
            leftIndex = midIndex + 1;
        }
        else if (ListOfParticipants.at(midIndex).IDParticipant() > searchData)
        {
            rightIndex = midIndex - 1;
        }
        else
        {
            return midIndex;
        }
    }

    if (ListOfParticipants.at(leftIndex).IDParticipant() == searchData)
    {
        return leftIndex;
    }
    if (ListOfParticipants.at(rightIndex).IDParticipant() == searchData)
    {
        return rightIndex;
    }

    return -1;
}


//Поиск Фиббоначи
short fibbonachiSearch(const std::vector<ParticipantsOfTheCompetition>& ListOfParticipants,const std::string& searchData)
{
    short fib2 = 0;
    short fib1 = 1;
    short fib = fib1 + fib2;

    while (fib < ListOfParticipants.size())
    {
        fib2 = fib1;
        fib1 = fib;
        fib = fib1 + fib2;
    }

    short offset = -1;
    while (fib > 1)
    {
        short index = fmin(offset + fib2, ListOfParticipants.size() - 1);
        if (ListOfParticipants.at(index).FirstName() < searchData) 
        {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = index;
        }
        else if (ListOfParticipants.at(index).FirstName() > searchData) 
        {
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;
        }
        else 
        {
            return index;
        }
    }

    if (fib1 && ListOfParticipants[offset + 1].FirstName() == searchData)
    {
        return offset + 1;
    }

    return -1;
}

int main()
{
    std::vector<ParticipantsOfTheCompetition> ListOfParticipants;

    std::string path = "D:/MyCoolProject1/MOCK_DATA.csv";

    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cout << "File opening error!";
    }
    else
    {
        while (!file.eof())
        {
            ParticipantsOfTheCompetition tmp;

            file >> tmp;

            if (file.eof())
            {
                break;
            }

            ListOfParticipants.push_back(tmp);
        }
    }

    PrintListOfParticipants(ListOfParticipants);


    
    std::cout << "\n\na) Linear search" << std::endl;
    std::cout << "b) Search in an unsorted tree-structured array" << std::endl;
    std::cout << "c) Binary search" << std::endl;
    std::cout << "d) Interpolation search" << std::endl;
    std::cout << "e) Fibonachi search" << std::endl;
    std::cout << "\n\nChoose your options: ";
    char symbol;
    std::cin >> symbol;
    switch (symbol)
    {
        case 'a':
        {
            std::string lastName;
            std::cout << "\n\nEnter the symbols or last name of participant: ";
            std::cin >> lastName;

            for (unsigned short i = 0; i < ListOfParticipants.size(); i++)
            {
                linearSearch(ListOfParticipants[i], lastName);
            }
            break;
        }
        case 'b':
        {
            binaryTree* tree = new binaryTree;
            tree->data = ListOfParticipants[0];
            tree->left = nullptr;
            tree->right = nullptr;
            createBinaryTree(ListOfParticipants, tree);
            SearchInBinaryTree(ListOfParticipants, tree);
            break;
        }
        case 'c':
        {
            InsertionSort(ListOfParticipants);
            PrintListOfParticipants(ListOfParticipants);
            std::string firstName;
            std::cout << "\n\nEnter the first name of participant: ";
            std::cin >> firstName;
            __int16 index;
            index = binarySearch(ListOfParticipants, firstName);
            index != -1 ? std::cout << ListOfParticipants[index] : std::cout << "No data found!" << std::endl;
            break;
        }
        case 'd':
        {
            __int16 IDParticipant;
            std::cout << "\n\nEnter ID of participant to search: ";
            std::cin >> IDParticipant;
            IDParticipant = interpolationSearch(ListOfParticipants, IDParticipant);
            std::cout << ListOfParticipants[IDParticipant];
            IDParticipant != -1 ? std::cout << ListOfParticipants[IDParticipant] : std::cout << "No data found!" << std::endl;
            break;
        }
        case 'e':
        {
            InsertionSort(ListOfParticipants);
            std::string firstName;
            std::cout << "\n\nEnter the first name of participant: ";
            std::cin >> firstName;
            __int16 index;
            index = fibbonachiSearch(ListOfParticipants, firstName);
            index < 0 ? std::cout << "No data found" : std::cout << ListOfParticipants[index];
            break;
        }
        default:
        {
            std::cout << "No found option" << std::endl;
            break;
        }

    }
   

    system("pause>nul");
    return 0;
}
