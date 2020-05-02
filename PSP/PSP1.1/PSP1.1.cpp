/* ********************** */
/* �t�@�C���ԍ��F4 */
/* ���t�F2020�N 5�� 2��*/
/* �v���O�������e�F�T�̑��΋K�́iVS,S,M,L,VL�j�����߂�B */
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
/* �N���XCalculationRelativeScale */
/* �����F���΋K�͂̎Z�o */
/* �g�p���@�F���΋K�͂����߂����z����w�肵�A�C���X�^���X���쐬�����チ�\�b�h���Ăяo���B */
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
		vector<double> value_ln; // value�̎��R�ΐ��l
		for (unsigned int i = 0; i < value.size(); i++)
		{
			value_ln.push_back(log(value[i]));
		}

		mylib::Calculation *calculation_pointer = new mylib::Calculation(value_ln);
		double average = calculation_pointer->findAverage();
		double std = calculation_pointer->findSTD();

		delete calculation_pointer;

		double range_ln = 0.0; // �ΐ��͈�
		double range_size = 0.0; // ���ۂ͈̔� 
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
/* ���C���֐� */
/* �錾�Fint main(int argc, char *argv[]) */
/* �������e�F���΋K�͂��Z�o�E�\�����邽�߁A�K�v�ȃN���X��֐����Ăяo���B�G���[�`�F�b�N���s�� */
/* �����F�f�[�^�Z�b�g���L�ڂ��ꂽ�t�@�C���̖��O�A�f�[�^�Z�b�g���̕ϐ��̐� */
/* �߂�l�F�펞�O��Ԃ� */
/*********************************************/
int main (int argc, char *argv[]) // function begin
{
	mylib::Show *show_pointer;
	if (argc != 3) // �w�肳�ꂽ�t�@�C����2�łȂ��ꍇ
	{
		vector<string> tmpstr{ "0" };
		vector<double> tmpvalue{ 0 };
		show_pointer = new mylib::Show(tmpstr, tmpvalue, 1);
		show_pointer->displayAsError();
		delete show_pointer;
		exit(0);
	}

	string format_name = mylib::getFormat(argv[1]);

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