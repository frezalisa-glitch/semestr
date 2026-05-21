#include <iostream>
#include <string>
using namespace std;

//интерфейс

class InterfacePen {
public:
    virtual void Show() const = 0;           //функция для вывода информации  
    virtual double CalcInkUsage() const = 0; // функция для расчета расхода чернил
    virtual ~InterfacePen() = 0;             //деструктор
};

InterfacePen::~InterfacePen() {}

//шаблонный базовый класс

template <typename T>
class PenTemplate : public InterfacePen {
protected:
    static int num;
    string brand;
    string color;
    int pagesWritten;
    T inkCapacity;

public:
    PenTemplate();
    PenTemplate(string brand, string color, int pages, T inkCapacity);
    PenTemplate(const PenTemplate<T>& other);
    virtual ~PenTemplate();

    virtual void Show() const;
    virtual double CalcInkUsage() const;

    static void ShowNum();

    friend ostream& operator<<(ostream& os, const PenTemplate<T>& pen) {
        pen.Show();
        return os;
    }
};

template <typename T>  //позволяет определять тип данных
int PenTemplate<T>::num = 0;

template <typename T>
PenTemplate<T>::PenTemplate() {
    brand = "Unknown";
    color = "Blue";
    pagesWritten = 0;
    inkCapacity = 100;
    num++;
}

template <typename T>
PenTemplate<T>::PenTemplate(string brand, string color, int pages, T inkCapacity)
    : brand(brand), color(color), pagesWritten(pages), inkCapacity(inkCapacity) {
    num++;
}

template <typename T>
PenTemplate<T>::PenTemplate(const PenTemplate<T>& other)
    : brand(other.brand), color(other.color),
    pagesWritten(other.pagesWritten), inkCapacity(other.inkCapacity) {
    num++;
}

template <typename T>
PenTemplate<T>::~PenTemplate() {
    num--;
}

template <typename T>
void PenTemplate<T>::Show() const {
    cout << "Pen Info:" << endl;
    cout << "Brand: " << brand << endl;
    cout << "Color: " << color << endl;
    cout << "Pages written: " << pagesWritten << endl;
    cout << "Ink capacity: " << inkCapacity << endl;
}

template <typename T>
double PenTemplate<T>::CalcInkUsage() const {
    return pagesWritten * 1.5;
}

template <typename T>
void PenTemplate<T>::ShowNum() {
    cout << "Total pens created: " << num << endl;
}

//производные классы ball и gel наследуюстя от pentem......
//ш.ручка

template <typename T>
class BallPenTemplate : public PenTemplate<T> {
private:
    double tipSize;
    static int numBall;

public:
    BallPenTemplate();
    BallPenTemplate(string brand, string color, int pages, T inkCapacity, double tipSize);
    BallPenTemplate(const BallPenTemplate<T>& other);

    void Show() const override;
    double CalcInkUsage() const override;

    static void ShowNum();
};

template <typename T>
int BallPenTemplate<T>::numBall = 0;

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

template <typename T>
void BallPenTemplate<T>::Show() const {
    PenTemplate<T>::Show();
    cout << "Type: Ball Pen" << endl;
    cout << "Tip size: " << tipSize << " mm" << endl;
}

template <typename T>
double BallPenTemplate<T>::CalcInkUsage() const {
    return this->pagesWritten * 1.2;
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

//функции связывания
//раннее связывание
void EarlyBinding(PenTemplate<double> pen) {
    cout << "Early binding example:" << endl;
    pen.Show();
}

//позднее связывание
void LateBinding(InterfacePen* pen) {
    cout << "Late binding example:" << endl;
    pen->Show();
}

int main() {
    int choice;

    do {
        cout << "\nChoose pen type:" << endl;
        cout << "1. Ball Pen" << endl;
        cout << "2. Gel Pen" << endl;
        cout << "3. Early binding test" << endl;
        cout << "4. Late binding test" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {

            BallPenTemplate<double> pen("Bic", "Blue", 50, 100.0, 0.5);
            cout << pen << endl;
            cout << "Ink usage: " << pen.CalcInkUsage() << endl;
            BallPenTemplate<double>::ShowNum();
            PenTemplate<double>::ShowNum();
        }

        if (choice == 2) {

            GelPenTemplate<double> pen("Pilot", "Black", 40, 120.0, true);
            cout << pen << endl;
            cout << "Ink usage: " << pen.CalcInkUsage() << endl;
            GelPenTemplate<double>::ShowNum();
            PenTemplate<double>::ShowNum();
        }

        if (choice == 3) {
            BallPenTemplate<double> pen("Test", "Red", 30, 80.0, 0.7);
            EarlyBinding(pen);
        }

        if (choice == 4) {
            GelPenTemplate<double> pen("Test", "Green", 20, 90.0, false);
            LateBinding(&pen);
        }

    } while (choice != 0);

    return 0;
}