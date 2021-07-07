#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <fstream>
#include <string>
#include <string_view>
#include "Timer.h"

using namespace std;

// Задание 1
template <class T>
void Swap(T& ptr1, T& ptr2)
{
    swap(ptr1, ptr2);
}
//

// Задание 2
template <class T>
void SortPointer(vector<T*>& ptr)
{
    sort(ptr.begin(), ptr.end(), [](T* p1, T* p2) { return *p1 < *p2; });
}
//

// Задание 3
// использование std::count_if() и string::find()
void FindVowelsVAR1(ifstream& f)
{
    Timer timer("std::count_if() and string::find()");
    string str;
    string_view str_v;
    size_t count = 0;

    auto IsValidChar = [&str_v](const char& ch) {
        switch (str_v.at(str_v.find(ch)))
        {
        case 'A': return true;
        case 'a': return true;
        case 'E': return true;
        case 'e': return true;
        case 'I': return true;
        case 'i': return true;
        case 'O': return true;
        case 'o': return true;
        case 'U': return true;
        case 'u': return true;
        case 'Y': return true;
        case 'y': return true;
        default: return false;
        };
    };

    while (true)
    {
        if (!f.eof())
        {
            getline(f, str);
            str_v = str;
            count += count_if(str_v.begin(), str_v.end(), IsValidChar);
        }
        else
            break;
    }
    cout << count << " vowels in the text." << " Method: ";
    timer.print();
    cout << " execution time";
    cout << endl;
}

// использование только std::count_if()
void FindVowelsVAR2(ifstream& f)
{
    Timer timer("only std::count_if()");
    string str;
    string_view str_v;
    size_t count = 0;

    auto IsValidChar = [&str_v](const char& ch) {
        for (size_t i = 0; i < str_v.length(); i++)
        {
            switch (ch)
            {
            case 'A': return true;
            case 'a': return true;
            case 'E': return true;
            case 'e': return true;
            case 'I': return true;
            case 'i': return true;
            case 'O': return true;
            case 'o': return true;
            case 'U': return true;
            case 'u': return true;
            case 'Y': return true;
            case 'y': return true;
            default: return false;
            };
        }
    };

    while (true)
    {
        if (!f.eof())
        {
            getline(f, str);
            str_v = str;
            count += count_if(str_v.begin(), str_v.end(), IsValidChar);
        }
        else
            break;
    }
    cout << count << " vowels in the text." << " Method: ";
    timer.print();
    cout << " execution time";
    cout << endl;
}

// использование только string::find()
void FindVowelsVAR3(ifstream& f)
{
    Timer timer("only string::find()");
    string str;
    string_view str_v;
    size_t count = 0;

    while (true)
    {
        if (!f.eof())
        {
            getline(f, str);
            str_v = str;
            for (size_t i = 0; i < str_v.length(); i++)
            {
                switch (str_v.at(str_v.find(str_v[i])))
                {
                case 'A': count++; break;
                case 'a': count++; break;
                case 'E': count++; break;
                case 'e': count++; break;
                case 'I': count++; break;
                case 'i': count++; break;
                case 'O': count++; break;
                case 'o': count++; break;
                case 'U': count++; break;
                case 'u': count++; break;
                case 'Y': count++; break;
                case 'y': count++; break;
                };
            }
        }
        else
            break;
    }
    cout << count << " vowels in the text." << " Method: ";
    timer.print();
    cout << " execution time";
    cout << endl;
}

// использование вложенных циклов for
void FindVowelsVAR4(ifstream& f)
{
    Timer timer("double FOR");
    string str;
    string_view str_v;
    size_t count = 0;

    while (true)
    {
        if (!f.eof())
        {
            getline(f, str);
            str_v = str;
            size_t i = 0;
            size_t j = str_v.length() - 1;
            for (; i < str_v.length(); i++)
            {
                switch (str_v[i])
                {
                case 'A': count++; break;
                case 'a': count++; break;
                case 'E': count++; break;
                case 'e': count++; break;
                case 'I': count++; break;
                case 'i': count++; break;
                case 'O': count++; break;
                case 'o': count++; break;
                case 'U': count++; break;
                case 'u': count++; break;
                case 'Y': count++; break;
                case 'y': count++; break;
                };
                if (i < j)
                {
                    for (; j != 0;)
                    {
                        switch (str_v[j])
                        {
                        case 'A': count++; j--; break;
                        case 'a': count++; j--; break;
                        case 'E': count++; j--; break;
                        case 'e': count++; j--; break;
                        case 'I': count++; j--; break;
                        case 'i': count++; j--; break;
                        case 'O': count++; j--; break;
                        case 'o': count++; j--; break;
                        case 'U': count++; j--; break;
                        case 'u': count++; j--; break;
                        case 'Y': count++; j--; break;
                        case 'y': count++; j--; break;
                        };
                        break;
                    }
                }
                else
                    break;
            }
        }
        else
            break;
    }
    cout << count << " vowels in the text." << " Method: ";
    timer.print();
    cout << " execution time";
    cout << endl;
}
//

// main()
int main()
{
    //
    int a = 25;
    int b = 50;
    int* a_ptr = &a;
    int* b_ptr = &b;

    string first_name = "Nikita";
    string second_name = "Maksim";
    string* f_ptr = &first_name;
    string* s_ptr = &second_name;
                                                 //
    cout << "Before swap: " << endl;            /// Поменять местами значения на которые указывают указатели
    cout << *a_ptr << " " << *b_ptr << endl;    //
    Swap(a_ptr, b_ptr);
    cout << "After swap: " << endl;
    cout << *a_ptr << " " << *b_ptr << endl;

    cout << "Before swap: " << endl;
    cout << *f_ptr << " " << *s_ptr << endl;
    Swap(f_ptr, s_ptr);
    cout << "After swap: " << endl;
    cout << *f_ptr << " " << *s_ptr << endl;
    cout << endl;
    //

    //
    int num1 = 2;
    int num2 = 7845;
    int num3 = 35;
    int num4 = 999;
    int num5 = 41;
    vector<int*> ptr_to_ints { &num1, &num2, &num3, &num4, &num5 };

    string str1 = "Zodiac";
    string str2 = "Bob";
    string str3 = "David";
    string str4 = "Gregor";
    string str5 = "Jack";
    vector<string*> ptr_to_strings { &str1, &str2, &str3, &str4, &str5 };

    vector<int*>::const_iterator it_int;
    cout << "Before sort: " << endl;
    for (it_int = ptr_to_ints.begin(); it_int < ptr_to_ints.end(); it_int++)
    {
        cout << **it_int << " ";
    }
    cout << endl;
                                                                                           //
    SortPointer(ptr_to_ints);                                                             /// Сортировка вектора указателей по значениям на которые указывают указатели
                                                                                          //
    cout << "After sort: " << endl;
    for (it_int = ptr_to_ints.begin(); it_int < ptr_to_ints.end(); it_int++)
    {
        cout << **it_int << " ";
    }
    cout << endl;

    vector<string*>::const_iterator it_str;
    cout << "Before sort: " << endl;
    for (it_str = ptr_to_strings.begin(); it_str < ptr_to_strings.end(); it_str++)
    {
        cout << **it_str << " ";
    }
    cout << endl;

    SortPointer(ptr_to_strings);

    cout << "After sort: " << endl;
    for (it_str = ptr_to_strings.begin(); it_str < ptr_to_strings.end(); it_str++)
    {
        cout << **it_str << " ";
    }
    cout << endl << endl;
    //

    //
    cout << "Find all vowels in War and Peace" << endl;
    ifstream file("War and Peace.txt");
    FindVowelsVAR1(file);

    file.seekg(0);
    FindVowelsVAR2(file);                        //
                                                /// Подсчет гласных букв разными методами
    file.seekg(0);                              //
    FindVowelsVAR3(file);

    file.seekg(0);
    FindVowelsVAR4(file);
    //
}