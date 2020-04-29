#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<numeric>
#include<cmath>
using namespace std;

namespace mylib
{
	/**************************************************************/
	/* クラスCalculation */
	/* 役割：複数の値からさまざまな計算処理を行う */
	/* 使用方法：コンストラクタ引数に値が格納された変数を指定しインスタンス化した後、メソッドを呼び出す。 */
	/* 　　　　　線形回帰のパラメータ、平均値、相関係数などの計算ができる。 */
	/***************************************************************/
	class Calculation // class begin
	{
	private:
		vector<double> valueX;
		vector<double> valueY;

	public:
		Calculation(vector<double> valueX, vector<double> valueY)
		{
			this->valueX = valueX;
			this->valueY = valueY;
		}

		~Calculation()
		{

		}

		double findBeta0() // method
		{
			double averageX = findAverage(valueX);
			double averageY = findAverage(valueY);
			return averageY - findBeta1() * averageX;
		}

		double findBeta1() // method
		{
			vector<double> productXY; // valueXとvalueYの積の集合
			for (unsigned int i = 0; i < valueX.size(); i++)
			{
				productXY.push_back(valueX[i] * valueY[i]);
			}
			double sum_productXY = accumulate(productXY.begin(), productXY.end(), 0.0);

			double n_averageXY = valueX.size() * findAverage(valueX) * findAverage(valueY); // n * valueXの平均値 * valueYの平均値

			vector<double> valueX2; // valueXの2乗
			for (unsigned int i = 0; i < valueX.size(); i++)
			{
				valueX2.push_back(valueX[i] * valueX[i]);
			}
			double sum_valueX2 = accumulate(valueX2.begin(), valueX2.end(), 0.0); // valueXの2乗の和

			double n_averageX2 = valueX.size() * findAverage(valueX) * findAverage(valueX); // n * valueXの平均値 * valueXの平均値

			return (sum_productXY - n_averageXY) / (sum_valueX2 - n_averageX2);
		}

		double findAverage(vector<double> values) // method
		{
			double sum = accumulate(values.begin(), values.end(), 0.0);
			int num = values.size();
			return sum / num;
		}

		double findCorrelation() // method
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
}
