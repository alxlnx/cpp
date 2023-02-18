/* public inhert: "is a"
isos. triangle is a triangle
acc. from evwrywhere.
public applied to pub = pub, to
priv = priv.
private inhert: 
accs. only from children.
priv everything.
"is implemented with"
derived class uses derivig class
allow overriding methods of derived class
ex: mix-in classes, some class from game
inherits socket class privately

RAII:
use constructors and destructors.

: a{val} - init. a. That syntax calls 
CONSTRUCTOS FOR FEILDS.
a = val inside cons. - assign a.
So for const int a; latter does NOT work.
*/


#include <iostream>
#include <exception>
#include <chrono>
#include <cmath>

/* CHRONO:

 *          | steady_clock (guaranteed to grow) 

 * clocks --| system_clock (sys time)

 *          | high_res_clock

 *              

 * time_point - steady_clock_timepoint
 * duration   - diff betweem 2 timepoints
 * duration.count() - convert dur to double
 * duration_cast<dur. type>(dur)
 *
 * */

 

class Timer {
public:
    Timer() {
        start = std::chrono::steady_clock::now();
    }

    ~Timer() {
        std::cout << (std::chrono::steady_clock::now() - start).count() << '\n';
    }
private:
    std::chrono::steady_clock::time_point start{};
};

 

class Triangle {
public:
    Triangle(double a, double b, double c) : a{a}, b{b}, c{c}
    {

        std::cout << "Made a tringale\n";   
        if (!validate(a, b, c)) throw std::invalid_argument("Incorrect sides");
    }

    ~Triangle() {
        std::cout << "Killed a triangle\n";
    }
    void Print() {
        std::cout << a << " " << b << " " << c << '\n';
    }   
private:

    bool validate(double a, double b, double c) {

        return !(a + b > c or a + c > b or b + c > a);

    }
    double a, b, c;

};

 

int main() {

try {

    Timer t{};

    long double sum{};

    for (int i{}; i < 1'000'000; ++i) {

        sum += std::sin(i) + std::cos(i);

    }

    std::cout << sum << '\n';

} catch (std::exception& e) { // (...)

    std::cerr << "An exception was thrown: " << e.what() << "\n";

    // try using .at() at invalid idx and catching

}

    return 0;
}
