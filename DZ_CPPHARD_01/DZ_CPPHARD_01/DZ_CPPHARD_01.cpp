#include <iostream>
#include <algorithm>
#include <optional>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

// Задание 1: Структура Person
struct Person {
    string surname;
    string name;
    optional <string> patronymic;
};

bool operator<(const Person& p1, const Person& p2)
{
    return tie(p1.surname, p1.name, p1.patronymic.has_value() ? p1.patronymic.value() : "") < tie(p2.surname, p2.name, p2.patronymic.has_value() ? p2.patronymic.value() : "");
}

bool operator==(const Person& p1, const Person& p2)
{
    return tie(p1.surname, p1.name, p1.patronymic.has_value() ? p1.patronymic.value() : "") == tie(p2.surname, p2.name, p2.patronymic.has_value() ? p2.patronymic.value() : "");
}

ostream& operator<<(ostream& os, const Person& p)
{
    os << setw(11) << p.surname << " " << setw(11) << p.name << " ";
    if (p.patronymic)
        os << setw(16) << *p.patronymic;
    else
        os << "                ";

    return os;
}
//

// Задание 2: Структура PhoneNumber
struct PhoneNumber {
    int country_code = 0;
    int city_code = 0;
    string number;
    optional<int> additional_number;
};

bool operator<(const PhoneNumber& pn1, const PhoneNumber& pn2)
{
    return tie(pn1.country_code, pn1.city_code, pn1.number, pn1.additional_number) < tie(pn2.country_code, pn2.city_code, pn2.number, pn2.additional_number);
}

ostream& operator<<(ostream& os, const PhoneNumber& pn)
{
    os << setw(4) << "+" << pn.country_code << "(" << pn.city_code << ")" << pn.number << " ";
    if (pn.additional_number)
        os << *pn.additional_number;
    cout << endl;

    return os;
}
//

// Задание 3: Класс PhoneBook
class PhoneBook {
private:
    vector<pair<Person, PhoneNumber>> pb;
public:
    PhoneBook(ifstream& f)
    {
        string str_buff, temp_surn, temp_n, temp_num;  //
        int temp_ccode, temp_cicode;                   // буфер-переменные в которые считываются
        optional<string> temp_patron;                  // данные из файла
        optional<int> temp_addnum;                     // str_buff главный буфер, который является хранилищем всего, что считали с файла, перед тем, как переместить данные в нужную буфер-переменную
     
        const size_t MAX_ELEMENT_PER_LINE = 7;         // максимальное число элементов в строке

        size_t data_id = 0;  // индекс для различных данных из файла (Фамилия, Имя и т.д.)
        size_t pair_id = 0;  // индекс для вектора пар pb     
        while (!f.eof())
        {
            for (size_t i = 0; i < MAX_ELEMENT_PER_LINE; i++)
            {
                getline(f, str_buff, ';'); // читаем файл (и пишем в str_buff) до ';' (сепаратор того, что мы встретили конец одного элемента, например Фамилии, и начало другого, например Имени)
                if (str_buff.find(';'))
                {
                    if (!str_buff.find('!')) // если встречаем '!' (сепаратор того, что у человека нет Отчества и/или добавочного номера), то устанавливаем nullopt...
                    {
                        if (data_id == 2 || data_id == 6) // если data_id == 2, то речь идет об отсутсвии Отчества, если 6, то об отсутствии добавочного номера
                        {
                            if (data_id < 3)
                                temp_patron = nullopt;
                            else
                                temp_addnum = nullopt;
                            data_id++; // ...и инкрементируем индекс, чтобы switch корректно функционировал далее
                        }
                    }
                    else
                    {
                        // исходя из значения data_id присваиваем некой буфер-переменной значение из str_buff. stoi() нужна в тех случаях, когда из str_buff (string) нам надо записать цифры, то есть в int
                        // также не забываем инкрементировать data_id, чтобы следующий case оказался верным

                        switch (data_id)
                        {
                        case 0: temp_surn = str_buff; data_id++; break;
                        case 1: temp_n = str_buff; data_id++; break;
                        case 2: temp_patron = str_buff; data_id++; break;
                        case 3: temp_ccode = stoi(str_buff); data_id++; break;
                        case 4: temp_cicode = stoi(str_buff); data_id++; break;
                        case 5: temp_num = str_buff; data_id++; break;
                        case 6: temp_addnum = stoi(str_buff); break;
                        }
                    }
                }
            }
            
            pb.resize(pair_id + 1); // когда все временные буфера с данными из файла готовы, то изменим размер вектора (текущий размер + 1)
            pb.push_back(make_pair(pb[pair_id].first = { temp_surn, temp_n, temp_patron }, pb[pair_id].second = { temp_ccode, temp_cicode, temp_num, temp_addnum })); // push всех данных в pair_id-элемент вектора
            pair_id++; // инкремент для следующего элемента вектора
            data_id = 0; // сбросим индекс для данных из файла, поскольку будем читать новую строку
            f.get(); // пропустим символ новой строки ('\n')
        }
        pb.pop_back(); // после того, как мы полностью заполнили вектор, удалим самый последний элемент. Исходя из подхода с pb.resize(pair_id + 1) будет создан один лишний элемент в векторе со строкой, которой на самом деле нет
    }

    // сортировка по телефону
    void SortByPhone()
    {
        sort(pb.begin(), pb.end(), [](const pair<Person, PhoneNumber>& l_pair, const pair<Person, PhoneNumber>& r_pair) { return l_pair.second < r_pair.second; });
    }

    // сортировка по ФИО
    void SortByName()
    {
        sort(pb.begin(), pb.end(), [](const pair<Person, PhoneNumber>& l_pair, const pair<Person, PhoneNumber>& r_pair) { return l_pair.first < r_pair.first; });
    }

    tuple<string, PhoneNumber> GetPhoneNumber(const string& surname)
    {
        tuple<string, PhoneNumber> find_pn, find_more_pn, not_find_pn;
        int count = 0;
        for_each(pb.begin(), pb.end(), [surname, &count, &find_pn, &find_more_pn, &not_find_pn](const pair<Person, PhoneNumber>& item) {
            if (item.first.surname == surname) // если фамилия в контейнере и фамилия переденная в функцию совпадают...
            {
                count++; // ...то увеличить счетчик совпадений: если он станет больше единицы, то можно утверждать, что в векторе есть люди с одинаковой фамилией
                count > 1 ? find_more_pn = make_tuple("found more than 1", item.second) : find_pn = make_tuple("", item.second); // если count == 1, то мы нашли человека и выведем его телефон, если > 1,
            }                                                                                                                    // то укажем, что подобных людей больше одного
            else
            {
                not_find_pn = make_tuple("not found", item.second); // если совпадений по фамилии нет, то ничего не найдено
            }
            });

        if (count > 0 && count < 2)
            return find_pn;
        else if (count > 1)
            return find_more_pn;
        else
            return not_find_pn;
    }

    void ChangePhoneNumber(const Person& p, const PhoneNumber& pn)
    {
        find_if(pb.begin(), pb.end(), [p, pn](pair<Person, PhoneNumber>& item) {
            if (item.first == p) // если ФИО совпадают
                item.second = pn; // записываем новый телефон этого человека в контейнер
            else
                return false; // иначе ничего не делаем
            });
    }

    friend ostream& operator<<(ostream& os, const PhoneBook& pb);
};

ostream& operator<<(ostream& os, const PhoneBook& pb)
{   
    for (const auto& [person, number] : pb.pb)
    {
        os << person << number;
    }

    return os;
}

int main()
{
    ifstream file("PhoneBook.txt");
    PhoneBook book(file);
    cout << "                   ==== UNSORTED LIST ==== " << endl;
    cout << book;
    cout << endl;
    
    cout << "                   ==== SORT BY PHONE ==== " << endl;
    book.SortByPhone();
    cout << book;
    cout << endl;
    
    cout << "                   ==== SORT BY NAME ==== " << endl;
    book.SortByName();
    cout << book;
    cout << endl;

    cout << "                   ==== GET PHONE NUMBER ==== " << endl;
    auto print_phone_number = [&book](const string& surname) {
                            cout << surname << "\t";
                            auto answer = book.GetPhoneNumber(surname);
                            if (get<0>(answer).empty())
                                cout << get<1>(answer);
                            else
                                cout << get<0>(answer) << endl;
    };

    print_phone_number("Ivanov");
    print_phone_number("Petrov");
    print_phone_number("Solovev");
    cout << endl;

    cout << "                   ==== CHANGE PHONE NUMBER ==== " << endl;
    book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" }, PhoneNumber{ 7, 123, "15344458", nullopt });
    book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" }, PhoneNumber{ 16, 465, "9155448", 13 });
    cout << book;
}