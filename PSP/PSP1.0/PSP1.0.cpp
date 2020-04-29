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

void fileReading(string file_name, vector<double> *valueX, vector<double> *valueY);

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
	string file_name = argv[1];
	int format_index = file_name.find_last_of(".");
	string format_name = file_name.substr(format_index, file_name.size() - format_index);

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
	fileReading(file_name, &valueX, &valueY);

	mylib::Calculation *calculation_pointer = new mylib::Calculation(valueX, valueY);

	vector<string> string_display = { "線形回帰のパラメータβ0", "線形回帰のパラメータβ1", "相関係数r", "相関係数の２乗値r２" , "yk"};
	vector<double> value_display = { calculation_pointer->findBeta0(), calculation_pointer->findBeta1(), calculation_pointer->findCorrelation(), calculation_pointer->findCorrelation() * calculation_pointer->findCorrelation(), calculation_pointer->findBeta0() + calculation_pointer->findBeta1() * 386};
	show_pointer = new mylib::Show(string_display, value_display, 0);
	show_pointer->displayAsItemzation();

	delete show_pointer;

	return 0;
} // function end


/*********************************************/
/* 関数fileReading */
/* 宣言：void fileReading(string file_name, vector<double> *valueX, vector<double> *valueY) */
/* 処理内容：ファイルを開き、ファイルに記載されたデータセットを読み込む */
/* 引数：第１引数→ファイル名、第２引数→値を格納する配列のアドレス、第３引数→値を格納する配列のアドレス */
/* 戻り値：なし */
/*********************************************/
void fileReading (string file_name, vector<double> *valueX, vector<double> *valueY) // function begin
{
	ifstream reading_file(file_name, ios::in);
	mylib::Show *show_pointer;
	if (reading_file.fail()) //ファイルが開けなかった場合
	{
		vector<string> tmpstr{ "0" };
		vector<double> tmpvalue{ 0 };
		show_pointer = new mylib::Show(tmpstr, tmpvalue, 4);
		show_pointer->displayAsError();
		delete show_pointer;
		exit(0);
	}
	char dataset_flag = 'X';

	string reading_line_buffer = "";
	while (getline(reading_file, reading_line_buffer)) // ファイルから1行ずつ読み込む
	{
		replace(reading_line_buffer.begin(), reading_line_buffer.end(), ',', ' ');
		istringstream stringstream(reading_line_buffer);
		string value_string = "";
		double value = 0;
		while (stringstream >> value_string)
		{
			if (any_of(value_string.cbegin(), value_string.cend(), isalpha) || none_of(value_string.cbegin(), value_string.cend(), isdigit)) //値が数値でない場合
			{
				vector<string> tmpstr{ "0" };
				vector<double> tmpvalue{ 0 };
				show_pointer = new mylib::Show(tmpstr, tmpvalue, 5);
				show_pointer->displayAsError();
				delete show_pointer;
				exit(0);
			}
			value = stod(value_string);
			if (dataset_flag == 'X')
			{
				valueX->push_back(value);
				dataset_flag = 'Y';
			}
			else
			{
				valueY->push_back(value);
				dataset_flag = 'X';
			}
		}
	}

	return;
} // function end
