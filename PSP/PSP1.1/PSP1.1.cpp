/* ********************** */
/* ファイル番号：３ */
/* 日付：2019年 12月 28日*/
/* プログラム内容：線形回帰のパラメータ、相関係数とその２乗値を求めるプログラム */
/* ********************** */

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>

#include"mylib.h"
using namespace std;

enum scales {
	VS,
	S,
	M,
	L,
	VL,
};

/*********************************************/
/* メイン関数 */
/* 宣言：int main(int argc, char *argv[]) */
/* 処理内容：他の関数の呼び出し、クラスのインスタンス化、エラーチェックを行う */
/* 引数：データセットが記載されたファイルの名前 */
/* 戻り値：常時０を返す */
/*********************************************/
int main (int argc, char *argv[]) // function begin
{
	mylib::Show *show_pointer;
	if (argc != 2) // 指定されたファイルが１つでない場合
	{
		vector<string> tmpstr{ "0" };
		vector<double> tmpvalue{ 0 };
		show_pointer = new mylib::Show(tmpstr, tmpvalue, 1);
		show_pointer->displayAsError();
		delete show_pointer;
		exit(0);
	}

	string format_name = mylib::getFormat(argv[1]);

	if (format_name != ".csv") //ファイルの拡張子が.csvではない場合
	{
		vector<string> tmpstr{ "0" };
		vector<double> tmpvalue{ 0 };
		show_pointer = new mylib::Show(tmpstr, tmpvalue, 3);
		show_pointer->displayAsError();
		delete show_pointer;
		exit(0);
	}

	vector<double> valueX;
	vector<double> valueY;
	scales scale;
	mylib::FileReading::csvReading(argv[1], &valueX, &valueY, int(argv[2]));
	if (int(argv[2]) == 1)
	{
		valueY = vector<double>(valueX.size(), 1);
	}

	CalculationRelativeScale *crs_pointer = new CalculationRelativeScale(valueX, valueY);

	vector<string> string_display = { "VS", "S", "M", "L" , "VL"};
	vector<double> value_display = 
	{ 
		crs_pointer->findCalculationRelativeScale(scale = VS), 
		crs_pointer->findCalculationRelativeScale(scale = S), 
		crs_pointer->findCalculationRelativeScale(scale = M), 
		crs_pointer->findCalculationRelativeScale(scale = L), 
		crs_pointer->findCalculationRelativeScale(scale = VL)
	};
	delete crs_pointer;

	show_pointer = new mylib::Show(string_display, value_display, 0);
	show_pointer->displayAsItemzation();

	delete show_pointer;

	return 0;
} // function end

class CalculationRelativeScale
{
private:
	vector<double> value;

public:
	CalculationRelativeScale(vector<double> valueX, vector<double> valueY)
	{
		for (unsigned int i = 0; i < valueX.size(); i++)
		{
			this->value.push_back(valueX[i] / valueY[i]);
		}
	}

	~CalculationRelativeScale()
	{

	}

	double findCalculationRelativeScale(enum scales scale)
	{
		vector<double> value_ln; // valueの自然対数値
		for (unsigned int i = 0; i < value.size(); i++)
		{
			value_ln.push_back(log(value[i]));
		}
		
		mylib::Calculation *calculation_pointer = new mylib::Calculation(value_ln);
		double average = calculation_pointer->findAverage();
		double std = calculation_pointer->findSTD();

		delete calculation_pointer;

		double range_ln; // 対数範囲
		double range_size; // 実際の範囲 
		switch (scale)
		{
		case VS:
			range_ln = average - 2 * std;
			break;

		case S:
			break;
			range_ln = average - std;
		
		case M:
			range_ln = average;
			break;
		
		case L:
			range_ln = average + std;
			break;
		
		case VL:
			range_ln = average + 2 * std;
			break;
		}

		range_size = exp(range_ln);
		return range_size;
	}
};