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
	/* �N���XCalculation */
	/* �����F�ėp�I�Ȍv�Z�������s�� */
	/* �g�p���@�F�z����w�肵�A�C���X�^���X���쐬�����チ�\�b�h���Ăяo���B */
	/* �@�@�@�@�@�w�肵���z��̕��ϒl�A���U�A�W���΍��̌v�Z���ł���B */
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

		double findVariance() // method
		{
			vector<double> deviation2; // �΍���2��l�̏W��
			double average = findAverage();
			for (unsigned int i = 0; i < value.size(); i++)
			{
				double d2 = pow(value[i] - average, 2); // �΍���2��l
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

	/*********************************************/
	/* �֐�getFormat */
	/* �錾�Fvoid getFormat(string file_name) */
	/* �������e�F�t�@�C��������g���q�𒲂ׂ� */
	/* �����F��P�������t�@�C���� */
	/* �߂�l�F�g���q���i�h�b�g�i.�j���܂ށj */
	/*********************************************/
	string getFormat (string file_name) // function begin
	{
		int format_index = file_name.find_last_of(".");
		string format_name = file_name.substr(format_index, file_name.size() - format_index);
		return format_name;
	} // function end

	/**************************************************************/
	/* �N���XFileReading */
	/* �����F�t�@�C�����J���A�l���w�肵���ϐ��Ɋi�[���� */
	/* �g�p���@�F �J���t�@�C�����A�i�[����ϐ��̃A�h���X���w�肵�A�g���q�ɑΉ��������\�b�h���Ăяo���B */
	/***************************************************************/
	class FileReading 
	{
	public:
		static void csvReading(string file_name, vector<double>* valueX, vector<double>* valueY, int param) // method
		{
			ifstream reading_file(file_name, ios::in);
			mylib::Show *show_pointer;
			if (reading_file.fail()) //�t�@�C�����J���Ȃ������ꍇ
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
				while (getline(reading_file, reading_line_buffer)) // �t�@�C������1�s���ǂݍ���
				{
					value_string = reading_line_buffer;
					if (any_of(value_string.cbegin(), value_string.cend(), isalpha) || none_of(value_string.cbegin(), value_string.cend(), isdigit)) //�l�����l�łȂ��ꍇ
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
				while (getline(reading_file, reading_line_buffer)) // �t�@�C������1�s���ǂݍ���
				{
					replace(reading_line_buffer.begin(), reading_line_buffer.end(), ',', ' ');
					istringstream stringstream(reading_line_buffer);
					value_string = "";
					value = 0;

					char dataset_flag = 'X';
					while (stringstream >> value_string)
					{
						if (any_of(value_string.cbegin(), value_string.cend(), isalpha) || none_of(value_string.cbegin(), value_string.cend(), isdigit)) //�l�����l�łȂ��ꍇ
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
