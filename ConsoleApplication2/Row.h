#ifndef Row_H
#define Row_H
#include<vector>
#include"Column.h"
#include<sstream>
using namespace std;
class Row {
	vector<Column>field;
	int ID;
public:
	//Constructor
	Row() {
		this->ID = 0;
	}
	//Constructor

	Row(int Id) {
		this->ID = Id;
	}
	//Thêm trường dữ liệu vào đối tượng
	void AddAttribute(Column value) {
		field.push_back(value);
	}
	//Lấy số lượng trường dữ liệu trong đối tượng
	int getSize() {
		return field.size();
	}
	//Lấy trường dữ liệu đối tượng
	vector<Column>getField() {
		return field;
	}
	//Xóa dữ liệu đối tượng
	void Clear() {
		field.clear();
	}
	//Lấy ID
	int getID() {
		return this->ID;
	}
	//Gán ID
	void setID(int id) {
		ID = id;
	}
	//Lấy trường dữ liệu tại vị trí
	Column getFieldName(int i) {
		return field.at(i);
	}
	//Chuyển đổi dữ liệu để lưu trữ
	string toString() {
		stringstream result;
		for (Column field : this->field) {
			result << field.value << "|";
		}
		return result.str();
	}
	void AddValue(const vector<string>& data) {
		if (data.size() != this->field.size())
			return;
		int len = data.size();
		for (int i = 0; i < len; i++) {
			this->field[i].value = data[i];
		}
	}
};
//output
std::ostream& operator<<(std::ostream& out,  Row& row) {
	for (int i = 0; i < (int)row.getField().size();i++) {
		out << row.getField().at(i);
	}
	return out;
}

#endif // !Row_H
