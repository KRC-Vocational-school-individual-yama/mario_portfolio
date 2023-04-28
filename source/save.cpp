#include "save.h"


std::vector<std::string> CsvSave::Load(std::string _pass){
//ファイルの読み込み
	std::ifstream file(_pass);
	if (!file.is_open())
		return std::vector<std::string>();

	std::string oneS;
	std::vector<std::string> getS;

	while (std::getline(file, oneS)) {
		std::istringstream inS(oneS);
		std::string twoS;
		
		while (std::getline(inS,twoS,',')) {
			getS.emplace_back(twoS);
		}
	}
	file.close();

	////中身を数字だけに変換
	//std::vector<int> fields;
	//for (auto it = getS.begin(); it != getS.end();it++) {
	//	std::string mozi = "-";
	//	std::string nowmozi = (*it);
	//	if (nowmozi==mozi)continue;
	//	int puyo = atoi(nowmozi.c_str());
	//	fields.emplace_back(puyo);
	//}

	////壁を入れ替え
	//int maxIndex = PuyoFieldConfig::fieldHeight * PuyoFieldConfig::fieldWidth;
	//for (int i = 0; i < PuyoFieldConfig::fieldHeight; i++) {
	//	for (int j = 0; j < PuyoFieldConfig::fieldWidth; j++) {
	//		int index = PuyoField::IndexChange(i, j);
	//
	//		bool widthzero = j == 0;
	//		bool heightzero = i == 0;
	//		bool widthmax = j == PuyoFieldConfig::fieldWidth - 1;
	//		bool heightmax = i == PuyoFieldConfig::fieldHeight - 1;
	//		if (widthzero || heightzero || widthmax || heightmax)
	//			fields[index] = -1;
	//	}
	//}

	return getS;
}

void CsvSave::Load(std::string _pass, std::vector<unsigned char>* _map){
	std::ifstream file(_pass);
	if (!file.is_open())return ;
	std::string oneS;
	while (std::getline(file, oneS)) {
		std::istringstream inS(oneS);
		std::string twoS;
		while (std::getline(inS, twoS, ',')) {

			_map->emplace_back(std::stoi(twoS));
		}
	}
	file.close();
}

void CsvSave::Save(std::string _pass, std::vector<std::string>_str,int _num) {
	//保存
	std::ofstream ofs(_pass);
	for (int i = 0; static_cast<unsigned int>(i) < _str.size(); i++) {
		if (i % _num == 0)
			ofs << std::endl;
		ofs << _str[i].c_str() << ',';
	}
	ofs.close();
}
