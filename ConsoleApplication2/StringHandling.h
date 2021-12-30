#pragma once
#ifndef STRING_HANDLING_H
#define STRING_HANDLING_H
#include <string>
#include <regex>
#include <vector>

//Remove space first, end string str
void formatString(std::string& str) {
	std::string temp = "";
	int size = str.length();
	for (int i = 0; i < size; i++) {
		if (str[i] != ' ') {
			if (str[i] == '.' || str[i] == ',' || str[i] == '(' || str[i] == ')') {
				if (temp != "" && temp.back() != ' ')
					temp.push_back(' ');
				temp += str[i];
				if (i != size - 1)
					temp.push_back(' ');
			}
			else
				temp += str[i];
		}
		else {
			if (temp != "" && temp.back() != ' ')
				temp += str[i];
		}
	}
	str = temp;
}

void Trim(std::string& str) {
	int size = str.size();
	while (str.front() == ' ')
		str.erase(str.begin());
	while (str.back() == ' ')
		str.erase(str.begin() + str.size() -1);
}

void Split(std::string str, std::vector<std::string>& vtStr, const char& separator = ' ') {
	formatString(str);
	vtStr.clear();
	int pos;
	std::string word;
	while (!str.empty()) {
		pos = str.find_first_of(separator);

		if (pos != -1) {
			word = str.substr(0, pos);
			formatString(word);
			vtStr.push_back(word);
			str.replace(0, pos + 1, "");
		}
		else {
			vtStr.push_back(str);
			break;
		}
	}
}

void uppercaseString(std::string& str) {
	int len = str.length();
	for (int i = 0; i < len; i++) {
		str[i] = str[i] & '_';
	}
}
void lowercaseString(std::string& str) {
	int len = str.length();
	for (int i = 0; i < len; i++) {
		str[i] = str[i] | ' ';
	}
}

int indexOfStr(const std::vector<std::string>& input, const std::string& str) {
	int i = 0;
	for (std::string s : input) {
		if (str.compare(s) == 0)
			return i;
		i++;
	}
	return -1;
}

bool checkValidCreateCommand(const std::string& input) {
	std::regex inputCommnd("(\\s)*([a-zA-Z](\\w)+)(\\s)+([a-zA-Z](\\w)+)(\\s)*(\\(((\\s)*(\\w)+(\\s)+(int|string)+((\\s)+(PRIMARY))?(\\s)*(,(?!\\)))?)+\\))(\\s)*");
	if (std::regex_match(input, inputCommnd))
		return true;
	return false;
}
#endif // !STRING_HANDLING_H
