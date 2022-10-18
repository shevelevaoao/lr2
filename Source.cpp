#include <iostream>
#include <chrono>

using namespace std;

int snail_amount;
double avg_time = 0;
void merge(float* arr, int l, int m, int r)
{
	int i = 0, j = 0, k = l;
	int n1 = m - l + 1;
	int n2 = r - m;
	float* L = new float[n1]();
	float* R = new float[n2]();

	for (int i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
	delete[] L;
	delete[] R;
}

void mergeSort(float* arr, int l, int r)
{

	int m = l + (r - l) / 2;
	if (l < r)
	{
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}


struct Snail
{
	float x = 0, y = 0;
	int length = snail_amount - 1;
	float* paths = new float[length]();

	bool confusion = false;
	float temp;
	void conf_detecter()
	{
		auto start = chrono::high_resolution_clock::now();
		mergeSort(paths, 0, length - 1);
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<double, milli> duration = end - start;
		avg_time += duration.count();
		if (paths[0] == paths[1])
			this->confusion = true;
	}
};

float pathlength(float x1, float y1, float x2, float y2)

{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int main()
{
	setlocale(0, "");

	cout << "Сколько всего улиток? ";
	cin >> snail_amount;
	Snail* snails = new Snail[snail_amount];
	cout << "Обозначьте для каждой улитки стартовую позицию в сантиметрах" << endl;
	for (int i = 0; i < snail_amount; i++)
	{
		cout << "улитка " << i << ":\nX: ";
		cin >> snails[i].x;
		cout << "Y: ";
		cin >> snails[i].y;
		cout << endl;
	}
	float shortest_path = 141422;
	float temp = 0;
	int l = 0;
	for (int i = 0; i < snail_amount; i++)
	{
		for (int j = 0; j < snail_amount; j++)
		{
			if (i != j)
			{
				temp = pathlength(snails[i].x, snails[i].y, snails[j].x, snails[j].y);
				snails[i].paths[l] = temp;
				if (temp < shortest_path)
					shortest_path = temp;
				l++;
			}
		}
		snails[i].conf_detecter();
		l = 0;
	}
	int k = 0;
	for (int i = 0; i < snail_amount; i++)
	{
		if (snails[i].confusion)
		{
			cout << "Улитка " << i << " в замешательстве\n";
			k++;
		}
	}
	cout << "Среднее время сортировки = " << avg_time / snail_amount << " millisec." << endl;
	if (k != snail_amount)
		cout << "Кратчайшее время = " << shortest_path / 2 << " sec." << endl << endl;
	system("pause");
	return 0;
}