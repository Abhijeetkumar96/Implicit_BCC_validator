#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <map>

class bcc_result {
public:
	std::map<int, std::set<int>> bcc_validator;
	std::vector<int> cut_vertex;
	void print_results(const std::map<int, std::set<int>>&);
	void print_results(const std::vector<int>&);
	void print() {
		print_results(bcc_validator);
		print_results(cut_vertex);
	}
};

void read_input(const std::string& filename, std::map<int, std::set<int>>& bcc_validator, std::vector<int>& cut_vertex) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "Unable to open file." << std::endl;
        return;
    }

    int n, e;
    in >> n >> e;
    cut_vertex.resize(n);

    std::string line;
    getline(in, line); // Read the remaining part of the line after integers

    // Read cut vertex status
    getline(in, line);
    if (line != "cut vertex status") {
        std::cerr << "Expected 'cut vertex status', got: " << line << std::endl;
        return;
    }

    int u, cut_status;
    for (int i = 0; i < n; ++i) {
        in >> u >> cut_status;
        cut_vertex[u] = cut_status;
    }

    // Read vertex BCC number
    getline(in, line); // To move to the next line
    getline(in, line);
    if (line != "vertex BCC number") {
        std::cerr << "Expected 'vertex BCC number', got: " << line << std::endl;
        return;
    }

    int bcc_no;
    for (int i = 0; i < n; ++i) {
        in >> u >> bcc_no;
        if (!cut_vertex[u]) {
            bcc_validator[bcc_no].insert(u);
        }
    }

    in.close();
}

void bcc_result::print_results(const std::map<int, std::set<int>>& bcc_validator) {
    for (const auto& pair : bcc_validator) {
        std::cout << pair.first << " : ";
        for (const int vertex : pair.second) {
            std::cout << vertex << " ";
        }
        std::cout << std::endl;
    }
}

void bcc_result::print_results(const std::vector<int>& cut_vertex) {
	int ii = 0;
	for(const auto &i : cut_vertex) {
		std::cout << ii++ <<" : " << i << std::endl;
	}
}

bool areAllSetsAvailable(const std::map<int, std::set<int>>& map1, const std::map<int, std::set<int>>& map2) {
    for (const auto& pair : map1) {
        const std::set<int>& set1 = pair.second;
        bool setFound = false;

        for (const auto& pair2 : map2) {
            const std::set<int>& set2 = pair2.second;

            if (set1 == set2) {
                setFound = true;
                break;
            }
        }

        if (!setFound) {
            return false;
        }
    }
    return true;
}

void validate(const bcc_result& serial_results, const bcc_result& par_results) {
    // Validate cut_vertex
    bool isCutVertexSame = serial_results.cut_vertex == par_results.cut_vertex;
    std::cout << "Cut Vertex Validation: " << (isCutVertexSame ? "Passed" : "Failed") << std::endl;

    // Validate bcc_validator
    bool isBccValidatorSame = areAllSetsAvailable(serial_results.bcc_validator, par_results.bcc_validator);
    std::cout << "BCC Validator Validation: " << (isBccValidatorSame ? "Passed" : "Failed") << std::endl;
}

int main(int argc, char* argv[]) {

	if(argc < 3) {
		std::cerr <<"Usage: " << argv[0] <<" <serial_output> <par_output>" << std::endl;
		return EXIT_FAILURE;
	}
	bcc_result serial_results, par_results;
	std::string serial_filename = argv[1];
	std::string par_filename = argv[2];

	read_input(serial_filename, serial_results.bcc_validator, serial_results.cut_vertex);
	read_input(par_filename, 	par_results.bcc_validator, 	  par_results.cut_vertex);

	validate(serial_results, par_results);

	std::cout << "serial_results:\n"; serial_results.print();
	std::cout << "par_results: \n"; par_results.print();
	
	return 0;
}