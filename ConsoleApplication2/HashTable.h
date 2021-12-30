#ifndef HashTable_H
#define HashTable_H
#include<vector>
#include"Row.h"
#include<sstream>
#include <fstream>
#include "StringHandling.h"
using namespace std;
class HashTable {
	vector<vector<Row>>obj;
	Row FieldName;
	int count = 0;
	string Name;
public:
	//Constructor khởi tạo giá trị của bảng
	HashTable() {
		for (int i = 0; i <997;i++) {
			obj.push_back(vector<Row>());
		}
		Name = "";
		FieldName = NULL;
	}
	//Lấy HashKey
	int HashFunction(int key) {
		return key %997;
	}
	void Insert(int key, Row value) {
		if (contains(HashFunction(key))) {
			cout << "Contained ID" << endl;
			return;
		}
		if ( containsFile(HashFunction(key))) {
			cout << "Contained ID" << endl;
			return;
		}
		obj.at(HashFunction(key)).push_back(value);
		count++;
		if (obj.at(HashFunction(key)).size() > 3) {
			SaveData(HashFunction(key));
			obj.at(HashFunction(key)).clear();
			cout << "Binding data to file" << endl;
			count -= 4;
		}
		cout << "Insert into table: " + this->Name << endl;
	}
	//Lấy số lượng phần tử có trên bảng hiện tại
	int numberOfRow() {
		return count;
	}
	//Đặt tên cho bảng 
	void setName(string name) {
		this->Name = name;
	}
	//Gán giá trị trường dữ liệu cho bảng
	void setField(Row fieldname) {
		this->FieldName = fieldname;
	}
	//lay ten cua bang
	string getName() {
		return this->Name;
	}
	//Lấy trường dữ liệu của bảng
	Row getField() {
		return this->FieldName;
	}
	//Lấy dữ liệu của bảng hiện tại theo ID
	vector<Row>Select(int ID) {
		vector<Row>Result;
		for (int i = 0; i <(int) obj.at(HashFunction(ID)).size(); i++) {
			Result.push_back(obj.at(HashFunction(ID)).at(i));
		}
		return Result;
	}
	HashTable& operator= (const HashTable& fraction);
	//Lưu trữ tên và trường dữ liệu của bảng
	void SaveFieldName() {
		string FileName = this->Name + ".db";
		fstream fo;
		fo.open(FileName, ios::out | ios::binary);
		if (fo.fail()) {
			cout << "Cannot open file" << endl;
			return;
		}
		/// <summary>
		/// Save vector FieldName
		/// </summary>
		vector<Column> vtFieldName = this->FieldName.getField();
		int sizeOfFieldName = vtFieldName.size();
		fo.write((char*)&sizeOfFieldName, sizeof(sizeOfFieldName));
		size_t size;
		string temp;
		for (Column col : vtFieldName) {
			temp = col.DataType;
			size = temp.size();
			fo.write((char*)&size, sizeof(size));
			fo.write((char*)&temp[0], size);
			temp = col.value;
			size = temp.size();
			fo.write((char*)&size, sizeof(size));
			fo.write((char*)&temp[0], size);
		}
		fo.close();
	}
	//Select  97 
	//save
	void SaveData(int ID) {
		if (Select(ID).size() == 0)
			return;
		string FileName = std::to_string(HashFunction(ID)) + "_" + Name + ".db";
		fstream fo;
		fo.open(FileName, ios::app | ios::binary);
		if (fo.fail()) {
			cout << "Cannot open file" << endl;
			return;
		}
		size_t size;
		string temp;
		vector<Row> All = this->Select(ID);
		for (Row row : All) {
			temp = row.toString();
			size = temp.size();
			fo.write((char*)&size, sizeof(size));
			fo.write((char*)&temp[0], size);
		}
		ClearData(ID);
		fo.close();
	}
	//read
	bool LoadFieldName(const string& FileName) {
		string Direct = FileName + ".db";
		fstream fi;
		fi.open(Direct, ios::in | ios::binary);
		if (fi.fail())
			return false;
		int pos = FileName.find_first_of('.');
		this->Name = FileName.substr(0, pos);
		/// <summary>
		/// Read FieldName
		/// </summary>
		/// <param name="FileName"></param>
		int sizeOfFieldName;
		fi.read((char*)&sizeOfFieldName, sizeof(sizeOfFieldName));
		Row field;
		size_t size{};
		string temp{};
		for (int i = 0; i < sizeOfFieldName; i++) {
			Column col;
			//read Name col
			fi.read((char*)&size, sizeof(size));
			temp.resize(size);
			fi.read((char*)&temp[0], size);
			col.DataType = temp;
			//read Value col
			fi.read((char*)&size, sizeof(size));
			temp.resize(size);
			fi.read((char*)&temp[0], size);
			col.value = temp;
			field.AddAttribute(col);
		}
		if (field.getSize() != 0)
			this->FieldName = field;
		fi.close();
		return true;
	}
	//Xóa dữ liệu tại HashKey khi gọi Auto Balance
	void ClearData(int key) {
		obj.at(HashFunction(key)).clear();
	}
	//Look up in current Data
	bool contains(int key) {
		//Duyệt qua ô lưu trữ tại HashKey nhập vào và bắt đầu tìm kiếm
		vector<Row>k = obj.at(HashFunction(key));
		for (int i = 0; i < (int)k.size(); i++) {
			if (k.at(i).getID() == key) {
				return true;
			}
		}
		return false;
	}
	//Look up in storage Data
	bool containsFile(int key) {
		//Lấy dữ liệu từ lưu trữ của hashKey và bắt đầu tìm kiếm
		vector<Row>K = LoadRow(key);
		for (int i = 0; i < (int)K.size(); i++) {
			if (K.at(i).getID() == key) {
				return true;
			}
		}
		return false;
	}
	void Update(int key, Row value) {
		for (int i = 0; i < (int)obj.at(HashFunction(key)).size(); i++) {
			if (obj.at(HashFunction(key)).at(i).getID() == key) {
				obj.at(HashFunction(key)).at(i) = value;
				cout << "Update success" << endl;
				return;
			}
		}
		vector<Row>K = LoadRow(HashFunction(key));
		if (K.size() == 0) {
			cout << "Not contains key" << endl;
			return;
		}
		for (int i = 0; i < (int)K.size(); i++) {
			if (K.at(i).getID() == key) {
				K.at(i) = value;
				obj.at(HashFunction(key)).push_back(K.at(i));
				cout << "Update success" << endl;
			}
			else {
				obj.at(HashFunction(key)).push_back(K.at(i));
			}
		}
		DeleteData(key);
		SaveData(HashFunction(key));
	}
	void Delete(int key) {
		//Check ID tại bảng hiện tại, nếu có update dữ liệu, k lưu trữ
		for (int i = 0; i < (int)obj.at(HashFunction(key)).size(); i++) {
			if (obj.at(HashFunction(key)).at(i).getID() == key) {
				obj.at(HashFunction(key)).erase(obj.at(HashFunction(key)).begin() + i);
				cout << "Delete success" << endl;
				return;
			}
		}
		//Lấy dữ liệu từ kho lưu trữ của HashKey
		vector<Row>K = LoadRow(key);
		if (K.size() == 0) {
			cout << "Not contains key" << endl;
			return;
		}
		//Nếu có ID -> update -> lưu lại
		//Nếu không có -> lấy ra để lưu lại
		for (int i = 0; i < (int)K.size(); i++) {
			if (K.at(i).getID() == key) {
				cout << "Delete success" << endl;
			}
			else {
				obj.at(HashFunction(key)).push_back(K.at(i));
			}
		}
		//Xóa dữ liệu trong file cũ
		DeleteData(key);
		//:Lưu dữ liệu tại HashKey
		SaveData(HashFunction(key));
	}
	//Xóa dữ liệu trong file cũ
	void DeleteData(int key) {
		string FileName = std::to_string(HashFunction(key)) + "_" + Name + ".db";
		fstream fo;
		fo.open(FileName, ios::out | ios::trunc);
		fo.clear();
		fo.close();
	}
	vector<Row> LoadRow(const int& key) {
		vector<Row> arr{};
		if (this->Name.empty())
			return arr;
		string Direct = std::to_string(HashFunction(key)) + "_" + this->Name + ".db";
		fstream fi;
		fi.open(Direct, ios::in | ios::binary);
		if (fi.fail())
			return arr;
		/// <summary>
		/// Read Table Data
		/// </summary>
		/// <param name="FileName"></param>
		vector<string> data{};
		string temp{};
		size_t size{};
		while(!fi.eof()) {
			Row row(this->FieldName);
			if (!fi.read((char*)&size, sizeof(size)))
				return arr;
			temp.resize(size);
			fi.read((char*)&temp[0], size);
			Split(temp, data, '|');
			row.AddValue(data);
			row.setID(std::stoi(row.getField().at(0).value));
			arr.push_back(row);
		}
		fi.close();
		return arr;
}
};
//overide operator =
HashTable& HashTable::operator= (const HashTable& fraction)
{
	// do the copy
	obj = fraction.obj;
	FieldName = fraction.FieldName;
	Name = fraction.Name;
	return *this;
}
#endif // !HashTable_H
