/* ********************** */
/* ファイル番号：4 */
/* 日付：2020年 5月 2日*/
/* プログラム内容：５つの相対規模（VS,S,M,L,VL）を求める。 */
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

/**************************************************************/
/* クラスCalculationRelativeScale */
/* 役割：相対規模の算出 */
/* 使用方法：相対規模を求めたい配列を指定し、インスタンスを作成した後メソッドを呼び出す。 */
/***************************************************************/
class CalculationRelativeScale // class begin
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

	double findCalculationRelativeScale (enum scales scale) // method
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

		double range_ln = 0.0; // 対数範囲
		double range_size = 0.0; // 実際の範囲 
		switch (scale)
		{
		case VS:
			range_ln = average - 2 * std;
			break;

		case S:
			range_ln = average - std;
			break;
			
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
}; // class end

/*********************************************/
/* メイン関数 */
/* 宣言：int main(int argc, char *argv[]) */
/* 処理内容：相対規模を算出・表示するため、必要なクラスや関数を呼び出す。エラーチェックも行う */
/* 引数：データセットが記載されたファイルの名前、データセット内の変数の数 */
/* 戻り値：常時０を返す */
/*********************************************/
int main (int argc, char *argv[]) // function begin
{
	mylib::Show *show_pointer;
	if (argc != 3) // 指定されたファイルが2つでない場合
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
	mylib::FileReading::csvReading(argv[1], &valueX, &valueY, atoi(argv[2]));
	if (atoi(argv[2]) == 1)
	{
		valueY = vector<double>(valueX.size(), 1);
	}

	CalculationRelativeScale* crs_pointer = new CalculationRelativeScale(valueX, valueY);

	vector<string> string_display = { "VS", "S", "M", "L" , "VL"};
	vector<double> value_display;
	value_display.push_back(crs_pointer->findCalculationRelativeScale(scale = VS));
	value_display.push_back(crs_pointer->findCalculationRelativeScale(scale = S));
	value_display.push_back(crs_pointer->findCalculationRelativeScale(scale = M));
	value_display.push_back(crs_pointer->findCalculationRelativeScale(scale = L));
	value_display.push_back(crs_pointer->findCalculationRelativeScale(scale = VL));

	delete crs_pointer;

	show_pointer = new mylib::Show(string_display, value_display, 0);
	show_pointer->displayAsItemzation();

	delete show_pointer;

	return 0;
} // function end