#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
using namespace std;

#define MAX_NUM 1000
#define MAX_LEN 10

int getSinLoc(char);//��ȡ��ĸ��Ӧ����
int getDv(int*, int, int);//��ȡ��ֵ�����ĸ��
int getIndex(int*);//��ȡ��������

int main()
{
	//��input.txt��output.txt�ļ�
	ifstream srcFile("X:\\0931Xu\\Study\\input.txt");
	assert(srcFile.is_open());   //��ʧ��,�����������Ϣ,����ֹ�������� 
	ofstream destFile("X:\\0931Xu\\Study\\output.txt");
	assert(destFile.is_open());	 //��ʧ��,�����������Ϣ,����ֹ�������� 

	string word;//�洢Ҫ��ѯ���ַ���
	int wordNum[MAX_LEN] = { 0 };//���Ըı�����Ӧ��ͬ����word
	int times=MAX_NUM;//�洢��ѯ����������
	int mlength = MAX_LEN;//���ʳ���
	int location = 0;//��Ӧ�����λ
	int tmp = 0;//�ݴ�index

	for (int t = 0; t < MAX_NUM&&t <= times; t++) {
		getline(srcFile, word);
		if (t == 0) {//��ȡ����
			times = atoi(word.c_str());
			cout <<"We have "<< word <<" words to be transited."<< endl;
			continue;
		}
		int length = word.length();
		int start = mlength - length;
		for (int t1 = 0, location = mlength - length; t1 < length; t1++,location++) {//���word��Ӧ����������
			wordNum[location] = getSinLoc(word[t1]);
		}

		//������
		cout << word << '\t';
		do {//��������ڶ�Ӧ����
			cout << wordNum[start] << '\t';
		} while (start++ +1 < mlength);
		tmp = getIndex(wordNum);
		cout<<"\nIndex is "<<tmp<<".\n\n";
		destFile << tmp << endl;
	}
	
	//�ر�input.txt��output.txt�ļ�
	srcFile.close();
	destFile.close();

	system ("pause");
	return 0;
}

//��ȡ��ĸ��Ӧ����
int getSinLoc(char letter)
{
	int number = letter;
	if (64 < number&&number < 91) {
		return number - 64;
	}
	else if (96 < letter&&letter < 123) {
		return number - 96;
	}
	else return 0;
};

//�õ�word����
int getIndex(int* nums)
{
	int index =	 0;

	while (nums[MAX_LEN - 1] != 1) {
		index += getDv(nums, MAX_LEN - 2, MAX_LEN - 1);
	}
	if (index == 0) return 1;
	else 	return index;
};

//��λ��λ
void guiwei(int* nums, int left, int right)
{
	if (nums[left] == 0) {
		return;
	}
	else if (left == 0 || nums[left - 1] == 0 || nums[left - 1] < nums[left] - 1) {
		nums[left]--;
		for (; right < MAX_LEN; right++) {
			nums[right] = 27 - MAX_LEN + right;
		}
	}
	else if(nums[left-1]==nums[left]-1) {
		guiwei(nums, left-1, left);
	}
};

//��ĩλ�Ĵ���
int getDv(int* nums, int left, int right)
{
	int dv = nums[right] - nums[left];
	if (nums[left] == 0 && nums[right] == 0) {
		return 0;
	}
	else if (nums[right] <= nums[left]) {
		return -20000;
	}
	else if ( right != 0) {
		nums[right] = nums[left] + 1;
		guiwei(nums, left, right);
		return dv;
	}
	else return -10000;
};

//TODO:getDv������ݻָ�
//			:MAX_LEN��΢��