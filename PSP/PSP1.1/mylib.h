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
	/* �N���XCalculation */
	/* �����F�����̒l���炳�܂��܂Ȍv�Z�������s�� */
	/* �g�p���@�F�R���X�g���N�^�����ɒl���i�[���ꂽ�ϐ����w�肵�C���X�^���X��������A���\�b�h���Ăяo���B */
	/* �@�@�@�@�@���`��A�̃p�����[�^�A���ϒl�A���֌W���Ȃǂ̌v�Z���ł���B */
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
			vector<double> productXY; // valueX��valueY�̐ς̏W��
			for (unsigned int i = 0; i < valueX.size(); i++)
			{
				productXY.push_back(valueX[i] * valueY[i]);
			}
			double sum_productXY = accumulate(productXY.begin(), productXY.end(), 0.0);

			double n_averageXY = valueX.size() * findAverage(valueX) * findAverage(valueY); // n * valueX�̕��ϒl * valueY�̕��ϒl

			vector<double> valueX2; // valueX��2��
			for (unsigned int i = 0; i < valueX.size(); i++)
			{
				valueX2.push_back(valueX[i] * valueX[i]);
			}
			double sum_valueX2 = accumulate(valueX2.begin(), valueX2.end(), 0.0); // valueX��2��̘a

			double n_averageX2 = valueX.size() * findAverage(valueX) * findAverage(valueX); // n * valueX�̕��ϒl * valueX�̕��ϒl

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
			vector<double> productXY; // valueX��valueY�̐ς̏W��
			for (unsigned int i = 0; i < valueX.size(); i++)
			{
				productXY.push_back(valueX[i] * valueY[i]);
			}
			double n_sum_productXY = valueX.size() * accumulate(productXY.begin(), productXY.end(), 0.0);

			double product_sumXY = accumulate(valueX.begin(), valueX.end(), 0.0) * accumulate(valueY.begin(), valueY.end(), 0.0); //valueX�̘a * valueY�̘a

			vector<double> valueX2; // valueX��2��
			for (unsigned int i = 0; i < valueX.size(); i++)
			{
				valueX2.push_back(valueX[i] * valueX[i]);
			}
			double n_sum_valueX2 = valueX.size() * accumulate(valueX2.begin(), valueX2.end(), 0.0); // n * valueX��2��̘a

			double sum2_valueX = accumulate(valueX.begin(), valueX.end(), 0.0) * accumulate(valueX.begin(), valueX.end(), 0.0); //valueX�̘a��2��

			vector<double> valueY2; // valueY��2��
			for (unsigned int i = 0; i < valueY.size(); i++)
			{
				valueY2.push_back(valueY[i] * valueY[i]);
			}
			double n_sum_valueY2 = valueY.size() * accumulate(valueY2.begin(), valueY2.end(), 0.0); // n * valueY��2��̘a

			double sum2_valueY = accumulate(valueY.begin(), valueY.end(), 0.0) * accumulate(valueY.begin(), valueY.end(), 0.0); //valueY�̘a��2��

			return (n_sum_productXY - product_sumXY) / sqrt((n_sum_valueX2 - sum2_valueX) * (n_sum_valueY2 - sum2_valueY));
		}
	}; // class end

	/**************************************************************/
	/* �N���XShow */
	/* �����F��ʂւ̏o�͂��s�� */
	/* �g�p���@�F�R���X�g���N�^�����ɕ\�����镶����A�\������l���w�肵�C���X�^���X��������A���\�b�h���Ăяo���B */
	/* �@�@�@�@�@�ӏ������`���̏o�͂̂ق��A�G���[���o���̃G���[���b�Z�[�W�̕\�����ł���B */
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
				error_message[1] = "�P�̃t�@�C�����w�肵�Ă�������";
				error_message[2] = "�P�̃t�@�C�����w�肵�Ă�������";
				error_message[3] = "�t�@�C���̃t�H�[�}�b�g���قȂ�܂�";
				error_message[4] = "�t�@�C����������܂���";
				error_message[5] = "�t�@�C���ɖ����Ȓl������܂�";

				cout << "�G���[�ԍ��F" << error_flag << endl;
				cout << error_message[error_flag] << endl;
			}
			return;
		}
	}; // class end
}
