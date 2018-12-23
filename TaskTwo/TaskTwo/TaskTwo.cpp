﻿// TaskTwo.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>


/*
15.   Найти  точку, из указанного массива точек, расстояние от  которой  до
	 заданной плоскости Ax+By+Cx+D=0 будет наименьшим. Вычисление расстояние от
	 точки до плоскости выделить в отдельную подпрограмму.
*/

struct Point
{
	double x;
	double y;
	double z;
};

double p(double A, double B, double C, double D, Point *point) {
	double res = 0.0f;
	double buff = 0.0f;
	double x0 = point->x;
	double y0 = point->y;
	double z0 = point->z;
	__asm {
		finit;
		fldz;
		fld A;
		fld A;
		fmulp	st(1), st(0);
		fld B;
		fld B;
		fmulp	st(1), st(0);
		fld C;
		fld C;
		fmulp	st(1), st(0);
		faddp	st(1), st(0);
		faddp	st(1), st(0);
		fsqrt;
		fcomi  st(0), st(1);
		jz ZERO;
		fstp	qword ptr[buff];
		mov ebx, point;
		fld D;
		fld C;
		fld qword ptr[ebx + 16];
		fmulp	st(1), st(0);
		fld B;
		fld qword ptr[ebx + 8];
		fmulp	st(1), st(0);
		fld A;
		fld qword ptr[ebx];
		fmulp	st(1), st(0);
		faddp	st(1), st(0);
		faddp	st(1), st(0);
		faddp	st(1), st(0);
		fld buff;
		fdivp   st(1), st(0);
		fstp	qword ptr[res];
	ZERO:
	}
	return res;
}

Point * find(double A, double B, double C, double D, Point **points, int n) {
	Point *res = 0;
	double oldP = 999999;
	__asm {
		finit;
		mov esi, 0;
		jmp START;
	ITER:
		add esi, 4;
	START:
		mov ebx, points;
		mov eax, [ebx + esi];

	FILL:
		sub esp, 36;
		mov [esp], eax;
		add esp, 4;
		fld D;
		fstp qword ptr[esp];
		add esp, 8;
		fld C;
		fstp qword ptr[esp];
		add esp, 8;
		fld B;
		fstp qword ptr[esp];
		add esp, 8;
		fld A;
		fstp qword ptr[esp];
		sub esp, 60;
		call p;
		add esp, 60;
	WHILE:
		mov ecx, n;
		cmp esi, ecx;
		je ITER;
	END:
	}
	Point *res1 = res;
	return res;
}

int main()
{
	Point **points = new Point* [3];
	Point *point = new Point();
	point->x = 1.1f;
	point->y = 2.2f;
	point->z = 3.3f;
	Point *point2 = new Point();
	point2->x = 5.1f;
	point2->y = 7.2f;
	point2->z = 8.3f;
	Point *point3 = new Point();
	point3->x = 1115.1f;
	point3->y = 712.2f;
	point3->z = 8611.3f;
	points[0] = point;
	points[1] = point2;
	points[2] = point3;
	find(1.2, 1.3, 1.4, 1.5, points, 3);
	//p(1, 1, 1, 1, point);
}

