#pragma once
//#include"../source/object.h"
#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<sstream>

class CsvSave {
public:
	static std::vector<std::string> Load(std::string _pass);
	/// <summary>
	/// �}�C�i�X�����@unsigned char�^�@���@�|�C���^�[�Ŏ󂯎��
	/// </summary>
	/// <param name="_pass"></param>
	/// <param name="_map"></param>
	static void Load(std::string _pass, std::vector<unsigned char>* _map);
	static void Save(std::string _pass, std::vector<std::string>_str,int _num=10);

private:
	
};