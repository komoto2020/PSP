#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<numeric>
#include<cmath>
#include<fstream>

using namespace std;

namespace mylib
{
	/**************************************************************/
	/* クラスCalculation */
	/* 役割：汎用的な計算処理を行う */
	/* 使用方法：配列を指定し、インスタンスを作成した後メソッドを呼び出す。 */
	/* 　　　　　指定した配列の平均値、分散、標準偏差の計算ができる。 */
	/***************************************************************/
	class Calculation // class begin
	{
	private:
		vector<double> value;

	public:
		Calculation(vector<double> value)
		{
			this->value = value;
		}

		~Calculation()
		{

		}

		double findAverage() // method
		{
			double sum = accumulate(value.begin(), value.end(), 0.0);
			int num = value.size();
			return sum / num;
		}

		double findCorrelation(vector<double> valueX, vector<double> valueY) // method
		{
			vector<double> productXY; // valueXとvalueYの積の集合
			for (unsigned int i = 0; i < valueX.size(); i++)
			{
				productXY.push_back(valueX[i] * valueY[i]);
			}
			double n_sum_productXY = valueX.size() * accumulate(productXY.begin(), productXY.end(), 0.0);

			double product_sumXY = accumulate(valueX.begin(), valueX.end(), 0.0) * accumulate(valueY.begin(), valueY.end(), 0.0); //valueXの和 * valueYの和

			vector<double> valueX2; // valueXの2乗
			for (unsigned int i = 0; i < valueX.size(); i++)
			{
				valueX2.push_back(valueX[i] * valueX[i]);
			}
			double n_sum_valueX2 = valueX.size() * accumulate(valueX2.begin(), valueX2.end(), 0.0); // n * valueXの2乗の和

			double sum2_valueX = accumulate(valueX.begin(), valueX.end(), 0.0) * accumulate(valueX.begin(), valueX.end(), 0.0); //valueXの和の2乗

			vector<double> valueY2; // valueYの2乗
			for (unsigned int i = 0; i < valueY.size(); i++)
			{
				valueY2.push_back(valueY[i] * valueY[i]);
			}
			double n_sum_valueY2 = valueY.size() * accumulate(valueY2.begin(), valueY2.end(), 0.0); // n * valueYの2乗の和

			double sum2_valueY = accumulate(valueY.begin(), valueY.end(), 0.0) * accumulate(valueY.begin(), valueY.end(), 0.0); //valueYの和の2乗

			return (n_sum_productXY - product_sumXY) / sqrt((n_sum_valueX2 - sum2_valueX) * (n_sum_valueY2 - sum2_valueY));
		}

		double findVariance() // method
		{
			vector<double> deviation2; // 偏差の2乗値の集合
			double average = findAverage();
			for (unsigned int i = 0; i < value.size(); i++)
			{
				double d2 = pow(value[i] - average, 2); // 偏差の2乗値
				deviation2.push_back(d2);
			}
			double sum_diff2 = accumulate(deviation2.begin(), deviation2.end(), 0.0);
			int n = value.size();
			return sum_diff2 / (n - 1);
		}

		double findSTD() // method
		{
			double variance = findVariance();
			return sqrt(variance);
		}
	}; // class end

	/**************************************************************/
	/* クラスShow */
	/* 役割：画面への出力を行う */
	/* 使用方法：コンストラクタ引数に表示する文字列、表示する値を指定しインスタンス化した後、メソッドを呼び出す。 */
	/* 　　　　　箇条書き形式の出力のほか、エラー検出時のエラーメッセージの表示ができる。 */
	/***************************************************************/
	class Show // class begin
	{
	private:
		vector<string> string_display;
		vector<double> value_display;
		int error_flag;

	public:
		Show(vector<string> string_display, vector<double> value_display, int error_flag)
		{
			this->string_display = string_display;
			this->value_display = value_display;
			this->error_flag = error_flag;
		}

		~Show()
		{

		}

		void displayAsItemzation() // method
		{
			if (error_flag == 0) 
			{
				for (unsigned int i = 0; i < string_display.size(); i++)
				{
					cout << string_display[i] << " = " << value_display[i] << endl;
				}
			}
			return;
		}

		void displayAsError() // method
		{
			if (error_flag != 0)
			{
				map<int, string> error_message;
				error_message[1] = "１つのファイルを指定してください";
				error_message[2] = "１つのファイルを指定してください";
				error_message[3] = "ファイルのフォーマットが異なります";
				error_message[4] = "ファイルが見つかりません";
				error_message[5] = "ファイルに無効な値があります";

				cout << "エラー番号：" << error_flag << endl;
				cout << error_message[error_flag] << endl;
			}
			return;
		}
	}; // class end

	/*********************************************/
	/* 関数getFormat */
	/* 宣言：void getFormat(string file_name) */
	/* 処理内容：ファイル名から拡張子を調べる */
	/* 引数：第１引数→ファイル名 */
	/* 戻り値：拡張子名（ドット（.）も含む） */
	/*********************************************/
	string getFormat (string file_name) // function begin
	{
		int format_index = file_name.find_last_of(".");
		string format_name = file_name.substr(format_index, file_name.size() - format_index);
		return format_name;
	} // function end

	/**************************************************************/
	/* クラスFileReading */
	/* 役割：ファイルを開き、値を指定した変数に格納する */
	/* 使用方法： 開くファイル名、格納する変数のアドレスを指定し、拡張子に対応したメソッドを呼び出す。 */
	/***************************************************************/
	class FileReading 
	{
	public:
		static void csvReading(string file_name, vector<double>* valueX, vector<double>* valueY, int param) // method
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

			string reading_line_buffer = "";
			string value_string;
			double value;
			if (param == 1)
			{
				while (getline(reading_file, reading_line_buffer)) // ファイルから1行ずつ読み込む
				{
					value_string = reading_line_buffer;
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
					valueX->push_back(value);
				}
			}

			else if (param == 2)
			{
				while (getline(reading_file, reading_line_buffer)) // ファイルから1行ずつ読み込む
				{
					replace(reading_line_buffer.begin(), reading_line_buffer.end(), ',', ' ');
					istringstream stringstream(reading_line_buffer);
					value_string = "";
					value = 0;

					char dataset_flag = 'X';
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
			}
			return;
		}
	};
}
