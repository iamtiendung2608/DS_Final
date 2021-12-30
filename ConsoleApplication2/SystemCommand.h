#ifndef SYSTEM_COMMAND_H
#define SYSTEM_COMMAND_H
#include<string>
#include <iostream>
#include"MainDatabase.h"
#include"Row.h"
using namespace std;
enum class  MetaCommandResult {
	SUCCESS,
	UNRECOGNIZED_COMMAND
};
enum class PrepareResult { PREPARE_SUCCESS, PREPARE_UNRECOGNIZED_STATEMENT };
enum class StatementType { CREATE_TABLE, INSERT,  SELECT, UPDATE, NEW, SAVE,DELETE,TEST	 };
struct Statement {
	StatementType type;
};

MetaCommandResult doMetaCommand(const string& inputBuffer) {
	if (inputBuffer.compare(".exit") == 0) {
		//Save before exit
		SaveToFile();
		cout << "Exit SQL" << endl;
		exit(EXIT_SUCCESS);
	}
	else if (inputBuffer.compare(".table") == 0) {
		cout << "Input Database File Name: ";
		string fileName;
		cin >> fileName;
		cin.ignore();
		New();
		if (!Table.LoadFieldName(fileName))
			cout << "Table not exist" << endl;
		else {
			cout << "Reject Table: " <<Table.getName()<< " has " << Table.getField().getField().size() << " data fields " << endl;
		}
		return MetaCommandResult::SUCCESS;
	}
	else if (inputBuffer.compare(".help") == 0) {
		Help();
		return MetaCommandResult::SUCCESS;
	}
	else {
		return MetaCommandResult::UNRECOGNIZED_COMMAND;
	}
}
PrepareResult prepareStatement(const string& inputBuffer, Statement* statement) {
	if (inputBuffer.empty())
		return PrepareResult::PREPARE_UNRECOGNIZED_STATEMENT;
	int pos = inputBuffer.find_first_of(' ');
	string command = inputBuffer.substr(0, pos);
	lowercaseString(command);
	if (command.compare(0, 6, "create") == 0) {
		statement->type = StatementType::CREATE_TABLE;
		return PrepareResult::PREPARE_SUCCESS;
	}
	if (command.compare(0, 6, "insert") == 0) {
		statement->type = StatementType::INSERT;
		return PrepareResult::PREPARE_SUCCESS;
	}
	if (command.compare(0, 6, "select") == 0) {
		statement->type = StatementType::SELECT;
		return PrepareResult::PREPARE_SUCCESS;
	}
	if (command.compare(0, 6, "update") == 0) {
		statement->type = StatementType::UPDATE;
		return PrepareResult::PREPARE_SUCCESS;
	}
	if (command.compare(0, 3, "new") == 0) {
		statement->type = StatementType::NEW;
		return PrepareResult::PREPARE_SUCCESS;
	}
	if (command.compare(0, 4, "save") == 0) {
		statement->type = StatementType::SAVE;
		return PrepareResult::PREPARE_SUCCESS;
	}
	if (command.compare(0, 6, "delete") == 0) {
		statement->type = StatementType::DELETE;
		return PrepareResult::PREPARE_SUCCESS;
	}
	if (command.compare(0, 4, "test") == 0) {
		statement->type = StatementType::TEST;
		return PrepareResult::PREPARE_SUCCESS;
	}
	return PrepareResult::PREPARE_UNRECOGNIZED_STATEMENT;
}
//Function
void executeStatement(Statement* statement) {
	switch (statement->type) {
	case (StatementType::INSERT):
		Insert();
		break;
	case (StatementType::SELECT):
		Select();
		break;
	case (StatementType::UPDATE):
		Update();
		break;
	case (StatementType::CREATE_TABLE):
		Create();
		break;
	case (StatementType::NEW):
		New();
		break;
	case (StatementType::SAVE):
		SaveToFile();
		break;
	case (StatementType::DELETE):
		Delete();
		break;
	case (StatementType::TEST):
		Test();
		break;
	}
}
void printPromt(const string& mess = "SQL") {
	cout << mess << "=# ";
}
//Run Program
void startSQL() {
	string inputBuffer;
	while (true) {
		if (Table.getName().empty()) {
			printPromt();
		}
		else {
			printPromt(Table.getName());
		}
		getline(cin, inputBuffer);
		Trim(inputBuffer);
		/// <summary>
		/// .exit => exit
		/// .table <table name> => show table name or call data
		/// </summary>
		if (inputBuffer[0] == '.') {
			switch (doMetaCommand(inputBuffer)) {
			case (MetaCommandResult::SUCCESS):
				continue;
			case (MetaCommandResult::UNRECOGNIZED_COMMAND):
				cout << "Unrecognized command: \"" << inputBuffer << "\"" << endl;
				continue;
			}
		}
		/// <summary>
		/// convert input => statement
		/// </summary>
		Statement statement;
		switch (prepareStatement(inputBuffer, &statement)) {
		case (PrepareResult::PREPARE_SUCCESS):
			break;
		case (PrepareResult::PREPARE_UNRECOGNIZED_STATEMENT):
			cout << "Unrecognized keyword at start of \"" << inputBuffer << "\"" << endl;
			continue;
		}
		executeStatement(&statement);
		cout << '\n';
	}
}

#endif // !SYSTEM_COMMAND_H