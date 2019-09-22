#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
using namespace std;

#define MAX_NUM 1000
#define MAX_LEN 10

int getSinLoc(char);//获取字母对应数字
int getDv(int*, int, int);//获取差值间的字母数
int getIndex(int*);//获取单词索引

int main()
{
	//打开input.txt与output.txt文件
	ifstream srcFile("X:\\0931Xu\\Study\\input.txt");
	assert(srcFile.is_open());   //若失败,则输出错误消息,并终止程序运行 
	ofstream destFile("X:\\0931Xu\\Study\\output.txt");
	assert(destFile.is_open());	 //若失败,则输出错误消息,并终止程序运行 

	string word;//存储要查询的字符串
	int wordNum[MAX_LEN] = { 0 };//可以改变来适应不同长度word
	int times=MAX_NUM;//存储查询次数及行数
	int mlength = MAX_LEN;//单词长度
	int location = 0;//对应数最高位
	int tmp = 0;//暂存index

	for (int t = 0; t < MAX_NUM&&t <= times; t++) {
		getline(srcFile, word);
		if (t == 0) {//获取行数
			times = atoi(word.c_str());
			cout <<"We have "<< word <<" words to be transited."<< endl;
			continue;
		}
		int length = word.length();
		int start = mlength - length;
		for (int t1 = 0, location = mlength - length; t1 < length; t1++,location++) {//获得word对应的数字序列
			wordNum[location] = getSinLoc(word[t1]);
		}

		//输出检查
		cout << word << '\t';
		do {//输出数组内对应数字
			cout << wordNum[start] << '\t';
		} while (start++ +1 < mlength);
		tmp = getIndex(wordNum);
		cout<<"\nIndex is "<<tmp<<".\n\n";
		destFile << tmp << endl;
	}
	
	//关闭input.txt与output.txt文件
	srcFile.close();
	destFile.close();

	system ("pause");
	return 0;
}

//获取字母对应数字
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

//得到word索引
int getIndex(int* nums)
{
	int index =	 0;

	while (nums[MAX_LEN - 1] != 1) {
		index += getDv(nums, MAX_LEN - 2, MAX_LEN - 1);
	}
	if (index == 0) return 1;
	else 	return index;
};

//各位归位
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

//计末位的次数
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

//TODO:getDv后的数据恢复
//			:MAX_LEN的微调