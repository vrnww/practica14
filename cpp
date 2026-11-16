// задача 1

#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    getline(cin, s); // считываем всю строку целиком, включая пробелы

    // массив играет роль стека: сюда будем складывать открывающие скобки
    char stack[1000];
    int top = 0;      // top — индекс первой свободной ячейки (сколько элементов лежит)
    bool ok = true;   // флаг: пока считаем, что последовательность правильная

    // проходим по каждому символу строки
    for (int i = 0; i < s.length(); i++) {
        // если встретили открывающую скобку — кладём её в стек
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            stack[top] = s[i];
            top++;
        }
        // если встретили закрывающую — проверяем, совпадает ли она с вершиной стека
        else if (s[i] == ')' || s[i] == ']' || s[i] == '}') {
            // стек пуст, а закрывающая скобка есть — значит, ошибка
            if (top == 0) {
                ok = false;
                break;
            }
            char last = stack[top - 1]; // смотрим верхний элемент стека
            // если пара подходящая — убираем открывающую скобку из стека
            if ((s[i] == ')' && last == '(') ||
                (s[i] == ']' && last == '[') ||
                (s[i] == '}' && last == '{')) {
                top--;
            }
            else {
                // пары не совпали — последовательность неправильная
                ok = false;
                break;
            }
        }
        // остальные символы (буквы, пробелы, знаки препинания) просто игнорируем
    }

    // если после прохода в стеке остались скобки — значит, какая-то не закрыта
    if (top != 0) ok = false;

    if (ok) cout << "yes" << endl;
    else cout << "no" << endl;

    return 0;
}
// задача 2

#include <iostream>
#include <string>
using namespace std;

// вспомогательная функция: проверяет, является ли символ буквой
// (латиница + кириллица, включая ё)
bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
           (c >= 'а' && c <= 'я') || (c >= 'А' && c <= 'Я') || c == 'ё' || c == 'Ё';
}

// вспомогательная функция: приводит букву к нижнему регистру
// (чтобы "Кринж" и "кринж" считались одним словом)
char toLower(char c) {
    if (c >= 'A' && c <= 'Z') return c + 32;   // латиница
    if (c >= 'А' && c <= 'Я') return c + 32;   // кириллица
    if (c == 'Ё') return 'ё';                  // ё обрабатываем отдельно
    return c;                                  // остальное не трогаем
}

int main() {
    string text;
    getline(cin, text); // считываем всю строку

    // массив уже найденных уникальных слов и их количество
    string words[1000];
    int count = 0;

    string cur = ""; // здесь накапливаем текущее слово

    // идём по строке; на позиции length() подставляем пробел,
    // чтобы гарантированно "закрыть" последнее слово
    for (int i = 0; i <= text.length(); i++) {
        char c = (i < text.length()) ? text[i] : ' ';

        if (isLetter(c)) {
            // буква — добавляем к слову в нижнем регистре
            cur += toLower(c);
        }
        else {
            // не буква — значит, слово закончилось
            if (cur.length() > 0) {
                // проверяем, встречалось ли уже такое слово
                bool found = false;
                for (int j = 0; j < count; j++) {
                    if (words[j] == cur) {
                        found = true;
                        break;
                    }
                }
                // если новое — запоминаем
                if (!found) {
                    words[count] = cur;
                    count++;
                }
                cur = ""; // обнуляем слово для следующего
            }
        }
    }

    // выводим уникальные слова в порядке появления
    for (int i = 0; i < count; i++) {
        cout << words[i] << endl;
    }

    return 0;
}

// задача 3
#include <iostream>
#include <stack>
using namespace std;

stack<int> data; // обычный стек — сами числа
stack<int> mins; // второй стек — минимумы

void push(int x) {
    data.push(x);
    // во второй стек кладём меньший из двух: новое число или прошлый минимум
    if (mins.empty() || x < mins.top())
        mins.push(x);
    else
        mins.push(mins.top());
}

void pop() {
    data.pop();
    mins.pop(); // убираем синхронно
}

bool empty() {
    return data.empty();
}

int getMin() {
    return mins.top(); // просто верхушка — вот и весь O(1)
}