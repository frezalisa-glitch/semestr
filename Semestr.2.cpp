#include <iostream>
#include <string>
using namespace std;

//интерфейс
/*интерфейсный класс содержит только виртуальные методы определения которых будут переопределены далее в классах потомках
полей в интерфейсном классе нет
const=0 отвечает за то, что функция не меняет поля класса, а =0 означает, что сейчас метод не имеет реализации и ее должны предоставить классы наследники*/
class InterfacePen {
public:
    virtual void Show() const = 0;           // функция для вывода информации (Чистая виртуальная функция: обязательна для реализации в наследниках. Выводит инфо.)
    virtual double CalcInkUsage() const = 0; // функция для расчета расхода чернил (Чистая виртуальная функция: расчет расхода чернил.)
    virtual ~InterfacePen() = 0;             // деструктор (Чистый виртуальный деструктор. Нужен, чтобы правильно удалять объекты через указатель.)
};

InterfacePen::~InterfacePen() {} // реализация деструктора (даже чистый виртуальный деструктор должен иметь тело).

// шаблонный базовый класс

template <typename T>                      // объявление шаблона, где T — это тип данных (например, int или double) для емкости чернил.
class PenTemplate : public InterfacePen {  // наследование от интерфейса. (когда класс наследуется обязательна пометка доступа)
protected:                                 // поля доступны в этом классе и во всех классах-наследниках.
    static int num;    // статическая переменная: общая для всех объектов этого типа ручек (счетчик). (глобальная переменная)
    string brand;      // марка ручки.
    string color;      // цвет чернил.
    int pagesWritten;  // сколько страниц уже написано.
    T inkCapacity;     // емкость (тип T позволяет использовать и 100, и 100.5).

public:
    PenTemplate();                                                     // конструктор по умолчанию.
    PenTemplate(string brand, string color, int pages, T inkCapacity); // конструктор с параметрами. (перегрузка)
    PenTemplate(const PenTemplate<T>& other);                          // конструктор копирования.
    virtual ~PenTemplate();                                            // виртуальный деструктор.

    virtual void Show() const;           // метод вывода данных.
    virtual double CalcInkUsage() const; // метод расчета расхода.

    static void ShowNum();               // статический метод для вывода общего количества созданных ручек.

    // перегрузка оператора вывода <<. Позволяет писать "cout << pen".
    friend ostream& operator<<(ostream& os, const PenTemplate<T>& pen) {
        pen.Show();
        return os;
    }
};

// инициализация статического счетчика (изначально ручек 0).
template <typename T>  // позволяет определять тип данных
int PenTemplate<T>::num = 0;

// конструктор по умолчанию: задает начальные значения и увеличивает счетчик.
template <typename T>
PenTemplate<T>::PenTemplate() {
    brand = "Unknown";
    color = "Blue";
    pagesWritten = 0;
    inkCapacity = 100;
    num++;
}

// конструктор с параметрами: использует список инициализации (после двоеточия).
template <typename T>
PenTemplate<T>::PenTemplate(string brand, string color, int pages, T inkCapacity)
    : brand(brand), color(color), pagesWritten(pages), inkCapacity(inkCapacity) {
    num++; //счетчик объекта
}

// конструктор копирования: создает дубликат существующего объекта.
template <typename T>
PenTemplate<T>::PenTemplate(const PenTemplate<T>& other)
    : brand(other.brand), color(other.color),
    pagesWritten(other.pagesWritten), inkCapacity(other.inkCapacity) {
    num++;
}

// деструктор: когда объект удаляется, счетчик ручек уменьшается.
template <typename T>
PenTemplate<T>::~PenTemplate() {
    num--;
}

// вывод базовой информации на экран.
template <typename T>
void PenTemplate<T>::Show() const {
    cout << "Pen Info:" << endl;
    cout << "Brand: " << brand << endl;
    cout << "Color: " << color << endl;
    cout << "Pages written: " << pagesWritten << endl;
    cout << "Ink capacity: " << inkCapacity << endl;
}

// базовый расчет чернил: просто страницы умножаем на 1.5.
template <typename T>
double PenTemplate<T>::CalcInkUsage() const {
    return pagesWritten * 1.5;
}

// вывод значения статического счетчика.
template <typename T>
void PenTemplate<T>::ShowNum() {
    cout << "Total pens created: " << num << endl;
}

// производные классы ball и gel наследуюстя от pentem......
// ш.ручка

template <typename T>
class BallPenTemplate : public PenTemplate<T> { // наследуется от базового шаблона.
private:
    double tipSize;     // уникальное поле: размер шарика (в мм).
    static int numBall; // уникальный счетчик именно для шариковых ручек.

public:
    BallPenTemplate();
    BallPenTemplate(string brand, string color, int pages, T inkCapacity, double tipSize);
    BallPenTemplate(const BallPenTemplate<T>& other);
//override для классов потомков
    void Show() const override;             // переопределение метода вывода.
    double CalcInkUsage() const override;   // переопределение расчета.

    static void ShowNum();
};

template <typename T>
int BallPenTemplate<T>::numBall = 0;

// конструкторы вызывают конструктор базового класса PenTemplate через список инициализации.
template <typename T>
BallPenTemplate<T>::BallPenTemplate()
    : PenTemplate<T>(), tipSize(0.7) {
    numBall++;
}

template <typename T>
BallPenTemplate<T>::BallPenTemplate(string brand, string color, int pages, T inkCapacity, double tipSize)
    : PenTemplate<T>(brand, color, pages, inkCapacity), tipSize(tipSize) {
    numBall++;
}

template <typename T>
BallPenTemplate<T>::BallPenTemplate(const BallPenTemplate<T>& other)
    : PenTemplate<T>(other), tipSize(other.tipSize) {
    numBall++;
}

// реализация Show: сначала вызываем Show родителя, потом добавляем свое.
template <typename T>
void BallPenTemplate<T>::Show() const {
    PenTemplate<T>::Show();
    cout << "Type: Ball Pen" << endl;
    cout << "Tip size: " << tipSize << " mm" << endl;
}

// свой расчет расхода для шариковой ручки (коэффициент 1.2).
template <typename T>
double BallPenTemplate<T>::CalcInkUsage() const {
    return this->pagesWritten * 1.2;    // this-> нужен, так как поле в шаблонном базовом классе.
}

template <typename T>
void BallPenTemplate<T>::ShowNum() {
    cout << "Ball pens created: " << numBall << endl;
}

//г.ручка

template <typename T>
class GelPenTemplate : public PenTemplate<T> {
private:
    bool waterproof;
    static int numGel;

public:
    GelPenTemplate();
    GelPenTemplate(string brand, string color, int pages, T inkCapacity, bool waterproof);
    GelPenTemplate(const GelPenTemplate<T>& other);

    void Show() const override;
    double CalcInkUsage() const override;

    static void ShowNum();
};

template <typename T>
int GelPenTemplate<T>::numGel = 0;

template <typename T>
GelPenTemplate<T>::GelPenTemplate()
    : PenTemplate<T>(), waterproof(true) {
    numGel++;
}

template <typename T>
GelPenTemplate<T>::GelPenTemplate(string brand, string color, int pages, T inkCapacity, bool waterproof)
    : PenTemplate<T>(brand, color, pages, inkCapacity), waterproof(waterproof) {
    numGel++;
}

template <typename T>
GelPenTemplate<T>::GelPenTemplate(const GelPenTemplate<T>& other)
    : PenTemplate<T>(other), waterproof(other.waterproof) {
    numGel++;
}

template <typename T>
void GelPenTemplate<T>::Show() const {
    PenTemplate<T>::Show();
    cout << "Type: Gel Pen" << endl;
    cout << "Waterproof: " << (waterproof ? "Yes" : "No") << endl;
}

template <typename T>
double GelPenTemplate<T>::CalcInkUsage() const {
    return this->pagesWritten * 2.0;
}

template <typename T>
void GelPenTemplate<T>::ShowNum() {
    cout << "Gel pens created: " << numGel << endl;
}

// функции связывания
// раннее связывание: передача по значению. Тип объекта определен при компиляции.
void EarlyBinding(PenTemplate<double> pen) {
    cout << "Early binding example:" << endl;
    pen.Show(); // всегда вызовет метод PenTemplate, даже если передали BallPen.
}

// позднее связывание: передача по указателю на интерфейс.
void LateBinding(InterfacePen* pen) {
    cout << "Late binding example:" << endl;
    pen->Show(); // благодаря виртуальным функциям вызовет метод того класса, который передали на самом деле.
}

int main() {
    int choice; // переменная для выбора в меню.

    do {
        // текстовое меню
        cout << "\nChoose pen type:" << endl;
        cout << "1. Ball Pen" << endl;
        cout << "2. Gel Pen" << endl;
        cout << "3. Early binding test" << endl;
        cout << "4. Late binding test" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        if (choice < 0 || choice > 5) {
    cout << "Число должно быть от 1 до 5" << endl;
    cin.ignore();

    continue;
}

cin.ignore(10000, '\n');
        
        if (choice == 1) {
            // создаем объект шариковой ручки. T = double.
            BallPenTemplate<double> pen("Bic", "Blue", 50, 100.0, 0.5);
            cout << pen << endl;                                    // работает перегруженный оператор <<
            cout << "Ink usage: " << pen.CalcInkUsage() << endl;    // полиморфный вызов
            BallPenTemplate<double>::ShowNum();                     // счетчик шариковых
            PenTemplate<double>::ShowNum();                         // общий счетчик
        }

        if (choice == 2) {
            // создаем объект гелевой ручки.
            GelPenTemplate<double> pen("Pilot", "Black", 40, 120.0, true);
            cout << pen << endl;
            cout << "Ink usage: " << pen.CalcInkUsage() << endl;
            GelPenTemplate<double>::ShowNum();
            PenTemplate<double>::ShowNum();
        }

        if (choice == 3) {
            BallPenTemplate<double> pen("Test", "Red", 30, 80.0, 0.7);
            //вызывается обычный конструктор, далее созданный объект подается в аргумент функции раннего связывания, тем самым вызывается конструктор копирования
            EarlyBinding(pen); // демонстрация раннего связывания
        }

        if (choice == 4) {
            GelPenTemplate<double> pen("Test", "Green", 20, 90.0, false);
            LateBinding(&pen); // демонстрация позднего связывания (полиморфизма)
        }

    } while (choice != 0); // цикл работает, пока не введем 0.

    return 0;
}
