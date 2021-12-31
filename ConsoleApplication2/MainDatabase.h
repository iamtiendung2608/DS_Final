#ifndef MainDatabase_H
#define MainDatabase_H
#include"HashTable.h"
#include"Row.h"
#include"Column.h"
#include<iomanip>
#include <set>
#include"Timer.h"
#include<random>
#include<string>
using namespace std;
HashTable Table;
// Chức năng create
void Create() {
	cout << "Create Table Name: ";
	string Name;
	getline(cin, Name);
	//Khởi tạo tên cho bảng
	Table.setName(Name);
	cout << "Input number of field: ";
	int n;
	//Nhập số lượng tính chất dữ liệu của đối tượng
	cin >> n;
	cin.ignore();
	Row field;
	for (int i = 0; i < n; i++) {
		Column col;
		cin >> col;
		//Thêm trường dữ liệu đối tượng khi xây dựng đối tượng
		field.AddAttribute(col);
	}
	//Lấy trường dữ liệu đã xây dựng được gán cho đối tượng
	Table.setField(field);
	cout << "Create Table: " + Name << endl;
	Table.SaveFieldName();
}
//Output trong chức năng Select
int PrintOut(vector<Row> All) {
	for (int i = 0; i < (int)All.size(); i++) {
		cout << All.at(i) << endl;
	}
	return All.size();
}
void Insert() {
	// Kiểm tra xem bảng có tên chưa(đã khởi tạo chưa)
	if (Table.getName().empty()) {
		cout << "Haven't install a table move to create new..." << endl;
		Create();
	}
	//Lấy các đặc tính của đối tượng ra
	Row field = Table.getField();
	Row Data;
	//Xây dựng dữ liệu dựa trên các đặc tính của đối tượng
	for (int i = 0; i < Table.getField().getSize(); i++) {
		cout << field.getFieldName(i);
		Column col;
		getline(cin, col.value);
		//Thêm thông tin vừa xây dựng vào đối tượng hiện tại
		Data.AddAttribute(col);
	}
	//Add try catch
	try
	{
		//Bắt buộc thuộc tính của đối tượng khởi tạo phải bao gồm ID
		Data.setID(std::stoi(Data.getField().at(0).value));
	}
	catch (const std::exception&)
	{
		cout << "Please Insert an int value to ID" << endl;
		return;
	}
	//Tiến hành chèn dữ liệu vào bảng
	Table.Insert(Data.getID(), Data);
}
void Select() {
	// Kiểm tra xem bảng có tên chưa(đã khởi tạo chưa)
	if (Table.getName().empty()) {
		cout << "Haven't install a table move to create new..." << endl;
		Create();
	}
	//Lấy các giá trị của trường dữ liệu đối tượng làm dòng đầu tiên
	Row Name = Table.getField();
	cout << Name << endl;
	cout << setfill('-');
	cout << setw(20 * (int)(Name.getSize())) << "-" << endl;
	cout << setfill(' ');
	int count = 0;
	//Loop HashKey để lần lược lấy dữ liệu cho output
	for (int i = 0 ; i < 997; i++) {
		//Load current Data
		vector<Row>getI=Table.Select(i);
		//Load storage Data
		vector<Row>getK=Table.LoadRow(i);
		//Output
		PrintOut(getI);
		PrintOut(getK);
	}
}
//Tạo mới bảng
void New() {
	HashTable HashNew;
	Table = std::move(HashNew);
}
void Help() {
	cout << setw(20) << left << ".help" << "for help" << endl;
	cout << setw(20) << left << ".exit" << "to exist SQL" << endl;
	cout << setw(20) << left << ".table" << "to load file database" << endl;
	cout << setw(20) << left << "CREATE" << "create new table" << endl;
	cout << setw(20) << left << "INSERT" << "insert data to table, create new if haven't exist" << endl;
	cout << setw(20) << left << "SELECT" << "get all data from table, create new if haven't exist" << endl;
	cout << setw(20) << left << "UPDATE" << "update contained data, create new if haven't exist" << endl;
	cout << setw(20) << left << "DELETE" << "delete contained data, create new if haven't exist" << endl;
	cout << setw(20) << left << "NEW" << "create new table" << endl;
}
void SaveToFile() {
	// Kiểm tra xem bảng có tên chưa(đã khởi tạo chưa)
	if (!Table.getName().empty() && Table.numberOfRow() != 0) {
		//Loop HashKey để lấy dữ liệu lưu trữ
		for (int i = 0;i < 997;i++) {
			//Lưu trữ theo hashKey
			Table.SaveData(i);
		}
	}
	else
		cout << "Table empty" << endl;
}
void Update() {
	// Kiểm tra xem bảng có tên chưa(đã khởi tạo chưa)
	if (Table.getName().empty()) {
		cout << "Haven't install a table move to create new..." << endl;
		Create();
	}
	//Lấy các trường dữ liệu để build
	Row field = Table.getField();
	Row Data;
	//Build an object
	for (int i = 0; i < Table.getField().getSize(); i++) {
		cout << field.getFieldName(i);
		Column col;
		getline(cin, col.value);
		//Xây dựng giias trị lần lược từng trường dữ liệu, thêm vào đối tượng
		Data.AddAttribute(col);
		//Check if contained ID or not
		if (i == 0) {
			if (!Table.contains(std::stoi(col.value))) {
				if (!Table.containsFile(std::stoi(col.value))) {
					cout << "Not contains ID" << endl;
					return;
				}
			}
		}
	}
	//Gán ID cho đối tượng
	Data.setID(std::stoi(Data.getField().at(0).value));
	//Tiến hành Update
	Table.Update(Data.getID(), Data);
}
void Delete() {
	// Check xem bang co ton tai hay khong
	if (Table.getName().empty()) {
		cout << "Haven't install a table move to create new..." << endl;
		Create();
	}
	int ID;
	//Nhap Key cần xóa
	cout << "ID:		";
	cin >> ID;
	cin.ignore();
	//Xóa Key
	Table.Delete(ID);
}
//test
void Test() {
	Table.setName("SV");
	random_device dev;
	mt19937 rng(dev());
	uniform_int_distribution<mt19937::result_type>dist6(0, 10000);
	Timer t;
	int d = dist6(rng);
	Row Data;
	Data.AddAttribute(Column("int", to_string(d)));
	Data.AddAttribute(Column("string", "Name"));
	Data.AddAttribute(Column("string", "Gender"));
	Table.setField(Data);
	Table.SaveFieldName();
	for (int i = 0; i < 10000; i++) {
		d = dist6(rng);
		Column k("Dung", "Tien");
		Data.AddAttribute(Column("int", to_string(d)));
		Data.AddAttribute(k);
		Data.AddAttribute(k);
		Table.Insert(d, Data);
	}
	cout << t.elapsed();
}
#endif // !MainDatabase_H
