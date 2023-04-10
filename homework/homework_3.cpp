/*
 * Дополните иерархию геометрических фигур, реализованную на семинаре, треугольником, равнобедренным треугольником, 
 * равносторонним треугольником, прямоугольником и квадратом. 
 * Добавьте ещё хотя бы одну формулу в миксин (например, формулу Герона) и используйте её. 
 * 
 */
#include <iostream>
#include <exception>
#include <cmath>

namespace Plane_Geometry {
class MathMixIn {
public:
	const double pi() const {
		return std::acos(-1);
	}
	
	double approximate_ellipse_perimeter(double a, double b) const {
		return 2 * pi() * std::sqrt( (a * a + b * b) / 2 );
	}
	
	double heron_area(double a, double b, double c) const {
		double s = (a + b + c) / 2.0; // semi_perimiter
		return std::sqrt( s * (s-a) * (s-b) * (s-c) );
	}
};

// BASE CLASS 
class Shape {
public:
	virtual double perimeter() const = 0;
	virtual double area() const = 0;
};

// ROUND SHAPES
class Ellipse : public Shape, private MathMixIn {
public:
	Ellipse(double A, double B) : a{A}, b{B} {
		if (A <= 0 or B <= 0) {
			throw std::invalid_argument("Ellipse(): non-positive side(s) given");
		}
	} 
	
	double perimeter() const override  {
		return approximate_ellipse_perimeter(a, b);
	}
	double area() const override {
		return pi() * a * b;
	}
private:
	double a, b;
};

class Circle : public Ellipse {
public:
	Circle(double r) : Ellipse(r,r) {}
};

// TRIANGLES
class Triangle : public Shape, private MathMixIn {
public:
	Triangle(double A, double B, double C) : a{A}, b{B}, c{C} {
		if (A <= 0 or B <= 0 or C <= 0) {
			throw std::invalid_argument("Triangle():  non-positive side(s) given");
		} else if (A + B <= C or A + C <= B or B + C <= A) {
			throw std::invalid_argument("Triangle(): sides given do not satisfy the triangle inequality");
		}
	}
	
	double perimeter() const override {
		return a + b + c;
	}
	double area() const override {
		return heron_area(a, b, c);
	}
	virtual bool is_isosceles() const { return false; }
	virtual bool is_equilateral() const { return false; }
private:
	double a, b, c;
};

class IsoscelesTriangle : public Triangle {
public:
	IsoscelesTriangle(double A, double C) : Triangle(A, A, C) {}
	
	bool is_isosceles() const override { return true; }
	bool is_equilateral() const { return false; }
};

class EquilateralTriangle : public IsoscelesTriangle {
public:
	EquilateralTriangle(double A) : IsoscelesTriangle(A, A) {}
	
	bool is_isosceles() const override { return true; }
	bool is_equilateral() const { return true; }
};

// RECTANGLES
class Rectangle : public Shape {
public:
	Rectangle(double A, double B) : a{A}, b{B}  {
		if (A <= 0 or B <= 0) {
			throw std::invalid_argument("Rectangle():  non-positive side(s) given");
		}
	}
	
	double area() const {
		return a * b;
	}
	double perimeter() const {
		return 2 * (a + b);
	}
	
	virtual bool is_square() const { return false; }
private:
	double a, b;
};

class Square : public Rectangle {
public:
	Square(double A) : Rectangle(A, A) {}
	
	bool is_square() const override { return true; }
};
} // Plane_Geometry namespace

int main() {
	Plane_Geometry::Ellipse e {4, 5};
	std::cout << "The area of the ellipse is " << e.area() << '\n';
	
	Plane_Geometry::Circle c {9};
	std::cout << "The area of the circle is " << c.area() << '\n';
	
	Plane_Geometry::Triangle t {4, 13, 15};
	std::cout << "The area of the trianle is " << t.area() << '\n';
	
	Plane_Geometry::IsoscelesTriangle it {3, 3};
	std::cout << "The area of the i triangle is " << it.area() << '\n';
	
	Plane_Geometry::EquilateralTriangle et {5};
	std::cout << "The area of the e triangle is " << et.area() << '\n';
	
	Plane_Geometry::Rectangle r {10, 5};
	std::cout << "The area of the rectangle is " << r.area() << '\n';
	
	Plane_Geometry::Rectangle sq {5, 5};
	std::cout << "The area of the square is " << sq.area() << '\n';
}
















