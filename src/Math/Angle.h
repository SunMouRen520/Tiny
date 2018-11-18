#ifndef TINY_MATH_ANGLE_H
#define TINY_MATH_ANGLE_H

template<typename T> class Rad;

template<

template<typename T> class Deg {
public:
	/**/
	explicit Deg() ;

	Deg(const T& v);

	Deg(const Deg& other);


	Deg(const Rad& rad);

};

template<typename T> class Rad {
public:
	explicit Rad();

	Rad(const T& v);

	Rad(const Rad& other);

	Rad(const Deg& deg);
};

#endif