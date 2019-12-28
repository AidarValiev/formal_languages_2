#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <stdio.h>
#include <fstream>
using namespace std;

const std::string START_SYMBOL = "S";

struct Rule {
	int start;
	std::string end;
	Rule(int start_, const std::string& end_) : start(start_), end(end_) {}
};

struct Situation {
	int start;
	std::string left;
	std::string right;
	int pos;
	Situation(int start_, const std::string& right_, int pos_) : start(start_), left(""), right(right_), pos(pos_) {}
	Situation(int start_, const std::string& left_, const std::string right_, int pos_) : start(start_), left(left_), right(right_), pos(pos_) {}
	explicit Situation(const Situation& other, bool used) : start(other.start), left(""), right("") {
		left += other.left;
		left += other.right[0];
		for (int i = 1; i < other.right.size(); ++i) {
			right += other.right[i];
		}
		pos = other.pos;

	}
	Situation(const Situation& other) = default;
	Situation(Situation&& other) = default;
	explicit Situation(const Rule& other, int it) : start(other.start), left(""), right(other.end), pos(it) {}
	bool operator<(const Situation& other) const {
		if (start < other.start)
			return true;
		else if (start > other.start)
			return false;
		if (pos < other.pos)
			return true;
		else if (pos > other.pos)
			return false;
		if (left < other.left)
			return true;
		else if (left > other.left)
			return false;
		if (right < other.right)
			return true;
		return false;
	}
};

class Solver {
public:
	Solver() {}
	bool solve(const std::string& ptr) {
		pattern = ptr;
		situations.resize(ptr.size() + 1);
		situations[0].insert(Situation(-1, START_SYMBOL, 0));
		for (int it = 0; it <= pattern.size(); ++it) {
			scan(it);
			bool changed = true;
			while (changed) {
				int n = situations[it].size();
				complete(it);
				predict(it);
				if (n == situations[it].size())
					changed = false;
			}
		}
		for (auto& sit : situations[pattern.size()]) {
			if (sit.start == -1 && sit.left == START_SYMBOL && sit.right.size() == 0 && sit.pos == 0) {
				return true;
			}
		}
		return false;
	}
	void read_rules(std::istream& in) {
		std::string s1, s2;
		int n; in >> n;
		for (int i = 0; i < n; ++i) {
			in >> s1 >> s2;
			if (s2 == "$")
				s2 = "";
			if (s1 != START_SYMBOL + "'") {
				rules.emplace_back((int)(s1[0] - 'A'), s2);
			}
		}
	}
private:
	std::string pattern;
	std::vector<Rule> rules;
	std::vector<std::set<Situation>> situations;
	void scan(int it) {
		if (it != 0) {
			for (auto& sit : situations[it - 1]) {
				if (sit.right.size() > 0 && sit.right[0] == pattern[it - 1]) {
					situations[it].insert(Situation(sit, true));
				}
			}
		}
	}
	void complete(int it) {
		set<Situation> trash;
		for (auto& sit : situations[it]) {
			if (sit.right.size() == 0) {
				for (auto& other_sit : situations[sit.pos]) {
					if (!other_sit.right.empty() && other_sit.right[0] == (char)(sit.start + 'A')) {
						trash.insert(Situation(other_sit, true));
					}
				}
			}
		}
		for (auto& i : trash) {
			situations[it].insert(i);
		}
	}
	void predict(int it) {
		set<Situation> trash;
		for (auto& sit : situations[it]) {
			if (sit.right.size() != 0) {
				for (int j = 0; j < rules.size(); ++j) {
					if ((char)(rules[j].start + 'A') == sit.right[0]) {
						trash.insert(Situation(rules[j], it));
					}
				}
			}
		}
		for (auto& i : trash) {
			situations[it].insert(i);
		}
	}
};

bool solve(std::istream& in) {
	std::string ptr;
	Solver solver;
	solver.read_rules(in);
	in >> ptr;
	return solver.solve(ptr);
}

int main(int argc, char** argv) {
	if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 't') {
		std::ifstream in("test_in.txt");
		std::ofstream out("test_out.txt");
		int n; in >> n;
		int counter = 0;
		for (int i = 0; i < n; ++i) {
			bool ans = solve(in);
			if (ans) {
				out << "Yes\n";
			}
			else {
				out << "No\n";
			}
			int x;
			in >> x;
			counter += (x == ans);
		}
		out << counter << '/' << n << " tests passed\n";
		in.close();
		out.close();
		std::cout << counter << '/' << n << " tests passed\n";
		//system("pause");
		return 0;
	}
	if (solve(std::cin)) {
		std::cout << "Yes";
	}
	else {
		std::cout << "No";
	}
	//system("pause");
	return 0;
}
