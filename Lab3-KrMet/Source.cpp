#include <iostream>
#include "windows.h"
#include <vector>
#include "string"
#include <cmath>

using namespace std;

class Table {
private:
	vector<vector<int>> table;
	vector<int> width_form;
	void Format(int m) {
		width_form.clear();
		int width, buf_width;
		width = 1;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++) {
				buf_width = to_string(table[j][i]).size();
				if (width < buf_width) width = buf_width;
			}
			width_form.push_back(width);
		}
	}
public:
	void Input_str(vector<int> str)
	{
		table.push_back(str);
	}
	void Output_Table(int m, bool f) { // f = true -> +; f = false -> *;
		if (table.size() != table[0].size()) {
			return ;
		}
		char ch;
		if (f) ch = '+';
		else ch = '*';
		Format(m);
		int width_table = 2;
		width_table += to_string(m - 1).size();
		for (int i = 0; i < width_form.size(); i++) {
			width_table += width_form[i];
			width_table++;
		}
		string border(width_table, '=');
		cout.width(to_string(m - 1).size());
		cout << ch << "||";
		for (int i = 0; i < m; i++) {
			cout.width(width_form[i]);
			cout << i << "|";
		}
		cout << endl << border << endl;
		for (int i = 0; i < m; i++) {
			cout.width(to_string(m - 1).size());
			cout << i << "||";
			for (int j = 0; j < m; j++) {
				cout.width(width_form[j]);
				cout << table[i][j] << "|";
			}
			cout << endl << border << endl;
		}
		cout << endl;
		table.clear();
	}
};

class Simple_Numbers {
public:
	vector<int> Decomposition(int n) {
		vector<int> Numbers_vector;
		int n1 = n;
		for (int i = 2; i <= sqrt(n1); i++) {
			while (n % i == 0) {
				Numbers_vector.push_back(i);
				n /= i;
			}
		}
		if (n != 1) Numbers_vector.push_back(n);
		return Numbers_vector;
	}
};
class Functions {
private: 
	vector<int> R_numbers;
	vector<int> Q_numbers;
	vector<int> u_v = { 0,0 };
	int GCD = 1;
public:
	int NodEuclidean(int a, int b) {
		if (a == 0 || b == 0) {
			return 0;
		}
		int D, d, r, q;
		D = a;
		d = b;
		while (true) {
			r = D % d;
			q = (D - r) / d;
			if (r < 0) { //проверка отрицательных a, b
				if (d > 0) {
					q--;
					r += d;
				}
				if (d < 0) {
					q++;
					r -= d;
				}
			}
			Q_numbers.push_back(q);
			if (r == 0) break;
			R_numbers.push_back(r);
			D = d;
			d = r;
		}
		GCD = d;
		return GCD;
	}

	void Recursion_Bezu(int ux, int vx, int uy, int vy, int q_index) {
		//Основано на формуле: r(n) = a(u(n-2) - u(n-1)q(n)) + b(v(n-2) - v(n-1)q(n)) (для n>1)
		int buf_ux = ux, buf_vx = vx;
		ux = uy;
		vx = vy;
		uy = buf_ux - ux * Q_numbers[q_index];
		vy = buf_vx - vx * Q_numbers[q_index];
		q_index++;
		if (q_index + 1 == Q_numbers.size()) {
			u_v = { uy, vy };
		}
		else Recursion_Bezu(ux, vx, uy, vy, q_index); //рекурсия
	}
	vector<int> IdentityBezu(int a, int b) {
		int a1 = 1, b1, u = 1, v = 1;
		if (GCD != b) {
			if (GCD == a) v = 0;
			else {
				v *= -(Q_numbers[Q_numbers.size() - 2]);
				if (GCD != a * u + b * v) {
					v = -(Q_numbers[0]);
					Recursion_Bezu(0, 1, 1, v, 1);
					u = u_v[0];
					v = u_v[1];
				}
			}
		}
		return { u, v };
	}
};


class Euler {
public:
	int Method1(int p) {
		return p - 1;
	}
	int Method2(int p, int k) {
		p = pow(p, k) - pow(p, k - 1);
		return p;
	}
	int Method3(vector<int> simple_n) {
		int f = 1, k;
		for (int i = 0; i < simple_n.size(); i++) {
			k = 1;
			if (i < simple_n.size() - 1) {
				while (true && i + 1 < simple_n.size()) {
					if (simple_n[i] == simple_n[i + 1]) {
						simple_n.erase(simple_n.begin() + i + 1);
						k++;
					}
					else break;
				}
			}
			if (k == 1) f *= Method1(simple_n[i]);
			else f *= Method2(simple_n[i], k);
		}
		return f;
	}
	int Method4(vector<int> simple_n, int n) {
		double f = n, buf;
		int f1;
		for (int i = 0; i < simple_n.size(); i++) {
			buf = simple_n[i];
			f *= (1 - (1 / buf));
			if (i < simple_n.size() - 1) {
				while (true && i + 1 < simple_n.size()) {
					if (simple_n[i] == simple_n[i + 1]) simple_n.erase(simple_n.begin() + i + 1);
					else break;
				}
			}
		}
		f1 = f;
		return f1;
	}
};

class Tasks {
private:
	Table t1;
	vector<int> str_numbers;
	vector<int> simple_numbers;
public:
	void Addition_table(int m) {
		if (m > 1073741824 || m < 0) { //m < int_max/2 + 1 for +
			cout << "Invalid m." << endl;
			return ;
		}
		if (m > 77) {
			int answer;
			cout << "The module is too big, the table will be unreadable or it may break your computer, do you want to continue?[1/0]" << endl;
			cin >> answer;
			if (answer == 0) return;
		}
		int number;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++) {
				number = i + j;
				number = number % m;
				str_numbers.push_back(number);
			}
			t1.Input_str(str_numbers);
			str_numbers.clear();
		}
		t1.Output_Table(m, true);
	}
	void Composition_table(int m) {
		if (m > 46341 || m < 0) { //m < sqrt(int_max) + 1 for *
			cout << "Invalid m." << endl;
			return;
		}
		if (m > 77) {
			int answer;
			cout << "The module is too big, the table will be unreadable or it may break your computer, do you want to continue?[1/0]" << endl;
			cin >> answer;
			if (answer == 0) return;
		}
		int number;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++) {
				number = i * j;
				number = number % m;
				str_numbers.push_back(number);
			}
			t1.Input_str(str_numbers);
			str_numbers.clear();
		}
		t1.Output_Table(m, false);
	}
	void Euler_Function(int n) {
		if (n <= 0) {
			cout << "Invalid n." << endl;
			return;
		}
		if (n == 1) {
			cout << "fi(" << n << ") = 1" << endl;
			return;
		}
		Simple_Numbers S_N;
		Euler fi;
		simple_numbers = S_N.Decomposition(n);
		int k_degree = 0, meth, exit = 1;
		if (simple_numbers[0] == simple_numbers[simple_numbers.size() - 1]) k_degree = simple_numbers.size();
		if (k_degree != 0) {
			while (exit == 1) {
				cout << "Choose a method[1-4](exit=5):" << endl;
				cin >> meth;
				switch (meth) {
				case 1:
					cout << "fi(" << n << ") = " << fi.Method1(n) << endl;
					break;
				case 2:
					cout << "fi(" << n << ") = " << fi.Method2(n, k_degree) << endl;
					break;
				case 3:
					cout << "fi(" << n << ") = " << fi.Method3(simple_numbers) << endl;
					break;
				case 4:
					cout << "fi(" << n << ") = " << fi.Method4(simple_numbers, n) << endl;
					break;
				case 5:
					exit = 0;
					break;
				default:
					cout << "This method does not exist" << endl;
					break;
				}
			}
		}
		else {
			while (exit == 1) {
				cout << "Choose a available method[3/4](exit=5):" << endl;
				cin >> meth;
				switch (meth) {
				case 3:
					cout << "fi(" << n << ") = " << fi.Method3(simple_numbers) << endl;
					break;
				case 4:
					cout << "fi(" << n << ") = " << fi.Method4(simple_numbers, n) << endl;
					break;
				case 5:
					exit = 0;
					break;
				default:
					cout << "This method does not exist" << endl;
					break;
				}
			}
		}
	}
	void InverseClass(int m, int n) {
		if (m > 46341 || m < 0) { //m < sqrt(int_max) + 1 for *
			cout << "Invalid m." << endl;
			return;
		}
		if (n >= m || n < 0) { 
			cout << "Invalid n." << endl;
			return;
		}
		Functions F;
		if (F.NodEuclidean(m, n) != 1) {
			cout << "Element n hasn't inverse element" << endl;
			return;
		}
		int inv_n = 0, composition;
		for (inv_n; inv_n < m; inv_n++) {
			composition = inv_n * n;
			composition = composition % m;
			if (composition == 1) break;
		}
		cout << "Inverse " << n << " = " << inv_n << endl;
	}
	void InverseBezu(int m, int n) {
		if (m > 46341 || m < 0) { //m < sqrt(int_max) + 1 for *
			cout << "Invalid m." << endl;
			return;
		}
		if (n >= m || n < 0) {
			cout << "Invalid nz." << endl;
			return;
		}
		Functions F;
		int GCD = F.NodEuclidean(m, n);
		if (GCD != 1) {
			cout << "Element n hasn't inverse element" << endl;
			return;
		}
		vector<int> U_V = F.IdentityBezu(m, n);
		int inv_n = U_V[1] % m;
		if (inv_n < 0) inv_n = m + inv_n;
		cout << "Inverse " << n << " = " << inv_n << endl;
	}
};


int main() {
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	int m, n, task, exit = 1;
	Tasks Math;
	while (exit == 1) {
		cout << "1.Addition table" << endl << "2.Composition_table" << endl << "3.Euler_Function" << endl << "4.InverseClass" << endl << "5.InverseBezu" << endl << "6.Exit" << endl << "Choose a way:" << endl;
		cin >> task;
		switch (task)
		{
		case 1:
			cout << "Input module:" << endl << "m = ";
			cin >> m;
			Math.Addition_table(m);
			break;
		case 2:
			cout << "Input module:" << endl << "m = ";
			cin >> m;
			Math.Composition_table(m);
			break;
		case 3:
			cout << "Input module:" << endl << "m = ";
			cin >> m;
			Math.Euler_Function(m);
			break;
		case 4:
			cout << "Input module:" << endl << "m = ";
			cin >> m;
			cout << "Input element:" << endl << "n = ";
			cin >> n;
			Math.InverseClass(m, n);
			break;
		case 5:
			cout << "Input module:" << endl << "m = ";
			cin >> m;
			cout << "Input element:" << endl << "n = ";
			cin >> n;
			Math.InverseBezu(m, n);
			break;
		case 6:
			exit = 0;
			break;
		default:
			cout << "This task does not exist" << endl;
			break;
		}
	}
	system("pause");
	return 0;
}