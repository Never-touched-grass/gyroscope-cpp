#include <string>
bool TryParseInt(const string& str) {
	int out;
	try {
		out = stoi(str);
		return true;
	}
	catch (const invalid_argument&) {
		return false;
	}
	catch (const out_of_range&) {
		return false;
	}
}
