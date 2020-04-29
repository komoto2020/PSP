/* ********************** */
/* �t�@�C���ԍ��F�R */
/* ���t�F2019�N 12�� 28��*/
/* �v���O�������e�F���`��A�̃p�����[�^�A���֌W���Ƃ��̂Q��l�����߂�v���O���� */
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
/* ���C���֐� */
/* �錾�Fint main(int argc, char *argv[]) */
/* �������e�F���̊֐��̌Ăяo���A�N���X�̃C���X�^���X���A�G���[�`�F�b�N���s�� */
/* �����F�f�[�^�Z�b�g���L�ڂ��ꂽ�t�@�C���̖��O */
/* �߂�l�F�펞�O��Ԃ� */
/*********************************************/
int main (int argc, char *argv[]) // function begin
{
	mylib::Show *show_pointer;
	if (argc != 2) // �w�肳�ꂽ�t�@�C�����P�łȂ��ꍇ
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

	if (format_name != ".csv") //�t�@�C���̊g���q��.csv�ł͂Ȃ��ꍇ
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

	vector<string> string_display = { "���`��A�̃p�����[�^��0", "���`��A�̃p�����[�^��1", "���֌W��r", "���֌W���̂Q��lr�Q" , "yk"};
	vector<double> value_display = { calculation_pointer->findBeta0(), calculation_pointer->findBeta1(), calculation_pointer->findCorrelation(), calculation_pointer->findCorrelation() * calculation_pointer->findCorrelation(), calculation_pointer->findBeta0() + calculation_pointer->findBeta1() * 386};
	show_pointer = new mylib::Show(string_display, value_display, 0);
	show_pointer->displayAsItemzation();

	delete show_pointer;

	return 0;
} // function end


/*********************************************/
/* �֐�fileReading */
/* �錾�Fvoid fileReading(string file_name, vector<double> *valueX, vector<double> *valueY) */
/* �������e�F�t�@�C�����J���A�t�@�C���ɋL�ڂ��ꂽ�f�[�^�Z�b�g��ǂݍ��� */
/* �����F��P�������t�@�C�����A��Q�������l���i�[����z��̃A�h���X�A��R�������l���i�[����z��̃A�h���X */
/* �߂�l�F�Ȃ� */
/*********************************************/
void fileReading (string file_name, vector<double> *valueX, vector<double> *valueY) // function begin
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
	char dataset_flag = 'X';

	string reading_line_buffer = "";
	while (getline(reading_file, reading_line_buffer)) // �t�@�C������1�s���ǂݍ���
	{
		replace(reading_line_buffer.begin(), reading_line_buffer.end(), ',', ' ');
		istringstream stringstream(reading_line_buffer);
		string value_string = "";
		double value = 0;
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

	return;
} // function end
