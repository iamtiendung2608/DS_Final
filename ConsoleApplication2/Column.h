#ifndef Column_HEADER
#define  Column_HEADER
#include<string>
#include<iostream>
#include<iomanip>

using namespace std;
class Column {
public:
	string DataType;
	string value;
	//Initialize
	Column(string m_name, string m_value) {
		DataType = m_name;
		value = m_value;
	}
	Column() {}
};
//Input
std::istream& operator>>(std::istream& in, Column& col) {
	cout << "Input Data Type: ";
	getline(in, col.DataType);
	cout << "Input Field Name: ";
	getline(in, col.value);
	return in;
}
//Output
std::ostream& operator<<(std::ostream& out, const Column& col) {
	out << setw(20) << left << col.value;
	return out;
}


#endif // !Column_HEADER
