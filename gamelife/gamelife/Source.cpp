#include "pch.h"
#include <iostream>
# include " fstream"
# include " random"

using namespace std;

int Life(bool** Cells, int Cx, int Cy, int x, int y) {
	int Num = 0;

	if (Cx == 0) {
		if (Cy == 0) {
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 2; j++)
					if (Cells[Cx + i][Cy + j]) Num++;
		}
		else if (Cy == y - 1) {
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 2; j++)
					if (Cells[Cx + i][Cy - 1 + j]) Num++;
		}
		else {
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 3; j++)
					if (Cells[Cx + i][Cy - 1 + j]) Num++;
		}
	}
	else if (Cx == x - 1) {
		if (Cy == 0) {
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 2; j++)
					if (Cells[Cx - 1 + i][Cy + j]) Num++;
		}
		else if (Cy == y - 1) {
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 2; j++)
					if (Cells[Cx - 1 + i][Cy - 1 + j]) Num++;
		}
		else {
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 3; j++)
					if (Cells[Cx - 1 + i][Cy - 1 + j]) Num++;
		}
	}
	else {
		if (Cy == 0) {
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 2; j++)
					if (Cells[Cx - 1 + i][Cy + j]) Num++;
		}
		else if (Cy == y - 1) {
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 2; j++)
					if (Cells[Cx - 1 + i][Cy - 1 + j]) Num++;
		}
		else {
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					if (Cells[Cx - 1 + i][Cy - 1 + j]) Num++;
		}
	}

	if (Cells[Cx][Cy]) return Num - 1; else return Num;
}

void Drawing(int x, int y, bool** Cells) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) if (Cells[i][j]) cout << "O" << (char)179; else cout << " " << (char)179;
		cout << endl;
		for (int j = 0; j < y * 2; j++) if (j % 2 == 0) cout << (char)196; else  cout << (char)197;
		cout << endl;
	}
}

void LivingCells(int x, int y, bool**& Cells1) {
	bool** Cells2 = new bool* [x];
	for (int i = 0; i < x; i++) Cells2[i] = new bool[y];

	for (int i = 0; i < x; i++)
		for (int j = 0; j < y; j++)
			Cells2[i][j] = false;

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			if (Life(Cells1, i, j, x, y) < 2) Cells2[i][j] = false;
			else if (Life(Cells1, i, j, x, y) > 3) Cells2[i][j] = false;
			else if (Life(Cells1, i, j, x, y) == 3 && Cells1[i][j] == false) Cells2[i][j] = true;
			else Cells2[i][j] = Cells1[i][j];
		}
	}

	for (int i = 0; i < x; i++) delete[]Cells1[i];
	delete[]Cells1;

	Cells1 = Cells2;

}

int main() {

	default_random_engine engine(random_device{}());

	int Cx, Cy, x, y, NumberCells, Step;

	do {
		cout << " Enter field size(x,y): ";
		cin >> x >> y;
	} while (x < 3 || y < 3);

	bool** Cells = new bool* [x];
	for (int i = 0; i < x; i++) Cells[i] = new bool[y];


	for (int i = 0; i < x; i++)
		for (int j = 0; j < y; j++)
			Cells[i][j] = false;


	do {
		cout << " Enter number living cells(x,y): ";
		cin >> NumberCells;
	} while (NumberCells < 1);

	do {
		cout << " Enter step number: ";
		cin >> Step;
	} while (Step < 1);
	cout << endl;

	uniform_int_distribution<int> Ñoordinates1(0, x - 1);
	uniform_int_distribution<int> Ñoordinates2(0, y - 1);

	for (int i = 0; i < NumberCells;) {
		Cx = Ñoordinates1(engine);
		Cy = Ñoordinates2(engine);
		if (!Cells[Cx][Cy]) {
			Cells[Cx][Cy] = true;
			i++;
		}
	}

	for (int i = 1; i <= Step; i++) {
		Drawing(x, y, Cells);
		LivingCells(x, y, Cells);
		cout << "Step: " << i << endl << endl;
	}

	for (int i = 0; i < x; i++) delete[]Cells[i];
	delete[]Cells;

	system("pause");
	return 0;
}