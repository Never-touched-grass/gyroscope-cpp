#include <iostream>
#include <vector>
#include <string>
#include <any>
#include <sstream>
#include <algorithm>
using namespace std;
#include "h.hpp"
int main() {
	// GyroScope Official C++ Version
	// This is a simple script interpreter
	// Go to [To be added.]
	vector<vector<string>> fcodes;
	vector<string> fnames;
	string cmd;
	vector<string> lines;
	vector<string> varNames;
	vector<any> varVals;
	int count = 1;
	while (cmd != "gs--run" || cmd != "gs--clear") {
		cout << count << ".";
		getline(cin, cmd);
		if (cmd == "gs--run") {
			break;
		}
		else if (cmd == "gs--clear") {
			lines.clear();
			varNames.clear();
			varVals.clear();
			fcodes.clear();
			fnames.clear();
			count = 0;
			cout << "File cleared.\n";
		}
		lines.emplace_back(cmd);
		count++;
	}
	for (int i = 0; i < lines.size(); i++) {
		if (lines[i].starts_with("println> ")) {
			string str = lines[i].substr(9);
			if (str.starts_with('"') && str.ends_with('"')) {
				string inner = str.substr(1, str.size() - 2);
				cout << inner << "\n";
			}
			else {
				for (size_t j = 0; j < varNames.size(); j++) {
					if (varNames[j] == str) {
						if (varVals[j].type() == typeid(int)) {
							cout << any_cast<int>(varVals[j]) << "\n";
						}
						else if (varVals[j].type() == typeid(string)) {
							cout << any_cast<string>(varVals[j]) << "\n";
						}
						else {
							cerr << "Unknown variable type for: " << str << "\n";
						}
					}
				}
			}
		}
		else if (lines[i].starts_with("print> ")) {
			string str = lines[i].substr(7);
			if (str.starts_with('"') && str.ends_with('"')) {
				string inner = str.substr(1, str.size() - 2);
				cout << inner;
			}
			else {
				for (size_t j = 0; j < varNames.size(); j++) {
					if (varNames[j] == str) {
						if (varVals[j].type() == typeid(int)) {
							cout << any_cast<int>(varVals[j]);
						}
						else if (varVals[j].type() == typeid(string)) {
							cout << any_cast<string>(varVals[j]);
						}
						else {
							cerr << "Unknown variable type for: " << str << "\n";
						}
					}
				}
			}
		}
		else if (lines[i].starts_with("var ")) {
			istringstream iss(lines[i].substr(4));
			vector<string> prs;
			string name;
			string eq;
			string raw;
			iss >> name >> eq;
			getline(iss, raw);
			any value;
			if (!raw.empty() && raw[0] == ' ') {
				value = raw.substr(1, raw.size() - 1);
			}
			else {
				try {
					value = stoi(raw);
				}
				catch (...) {
					cerr << "Invalid value: " << raw << "\n";
					continue;
				}
			}
			varNames.push_back(name);
			varVals.push_back(value);
		}
		else if (lines[i].starts_with("if> ")) {
			string cond = lines[i].substr(4);
			istringstream iss(cond);
			string val, op, arg;
			iss >> val >> op >> arg;
			bool conditionMet = false;
			if ((val.starts_with('"') && val.ends_with('"')) && (arg.starts_with('"') && arg.ends_with('"'))) {
				if (op == "==") {
					conditionMet = (val == arg);
				}
				else if (op == "!=") {
					conditionMet = (val != arg);
				}
				else {
					cerr << "Can only compare string literals with '!=' and '=='\n";
				}
			}
			else if (TryParseInt(val) && TryParseInt(arg)) {
				if (op == "==") {
					conditionMet = (stoi(val) == stoi(arg));
				}
				else if (op == "!=") {
					conditionMet = (stoi(val) != stoi(arg));
				}
				else if (op == "<") {
					conditionMet = (stoi(val) < stoi(arg));
				}
				else if (op == ">") {
					conditionMet = (stoi(val) > stoi(arg));
				}
				else if (op == "<=") {
					conditionMet = (stoi(val) <= stoi(arg));
				}
				else if (op == ">=") {
					conditionMet = (stoi(val) >= stoi(arg));
				}
				else {
					cerr << "Unknown operator: " << op << "\n";
				}
			}
			else {
				for (int x = 0; x < varNames.size(); x++) {
					if (varNames[x] == val) {
						if (varVals[x].type() == typeid(int) && TryParseInt(arg)) {
							if (op == "==") {
								conditionMet = any_cast<int>(varVals[x]) == stoi(arg);
							}
							else if (op == "!=") {
								conditionMet = any_cast<int>(varVals[x]) != stoi(arg);
							}
							else if (op == "<") {
								conditionMet = any_cast<int>(varVals[x]) < stoi(arg);
							}
							else if (op == ">") {
								conditionMet = any_cast<int>(varVals[x]) > stoi(arg);
							}
							else if (op == "<=") {
								conditionMet = any_cast<int>(varVals[x]) <= stoi(arg);
							}
							else if (op == ">=") {
								conditionMet = any_cast<int>(varVals[x]) >= stoi(arg);
							}
							else {
								cerr << "Unknown operator: " << op << "\n";
							}
						}
					}
				}
				if (!conditionMet) {
					while (lines[i] != "}") {
						i++;
					}
				}
			}
			}
		else if (lines[i].starts_with("func> ")) {
      // Future me will deal with this problem
			/*string def = lines[i].substr(6);
			if (def.ends_with("{")) {
				string funcName = def.substr(def.find("{"));
				while (lines[i] != "}") {
					fcodes[-1].push_back(lines[i]);
					i++;
				}
			}
			else {
				cerr << "Functions must have an opening '{'.\n";
			}
			*/
		}
    // and this one
		/*
		else if (lines[i].ends_with("()")) {
			string fname = lines[i].substr(lines[i].find("()"));
			for (int k = 0; k < fnames.size(); k++) {
				if (fnames[k] == "fname") {
					for (int h = 0; h < fcodes[-1].size(); h++) {

					}
				}
			}
			*/
	}
}
