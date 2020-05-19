#include <iostream>
#include <vector>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <regex>

using namespace std;

string getextension(string);
string extractquestion(string *);

int main(int argc, char** argv) {

	cout << "target folder: " << argv[1] << endl;
	cout << "assignment title: " << argv[2] << endl;
	cout << "author: " << argv[3] << endl;
	cout << "author detail #1: " << argv[4] << endl;
	cout << "author detail #2: " << argv[5] << endl;
	cout << "organization: " << argv[6] << endl;

	vector<string> fileorder;
	ifstream fin;
	ofstream fout;
	string line, tmp("");
	string targetfolder = argv[1];

	fin.open(targetfolder + "order.txt");

	if (fin.fail()) {
		cerr << "\033[31m" << "Unable to open " << targetfolder << "order.txt" << "\033[0m" << endl;
		exit(11);
	}

	while(getline(fin, line)) {
		fileorder.push_back(line);
	}

	fin.close();
	cout << "read order processed from " << targetfolder << "order.txt" << endl;

	fout.open(targetfolder + "generated.tex");
	cout << "writing to " << targetfolder << "generated.tex" << endl;

	fout << "\\documentclass[12pt]{exam}" << endl;
	fout << "\\usepackage{geometry}" << endl;
	fout << "\\geometry{a4paper, margin=1in}" << endl;
	fout << "\\usepackage[utf8]{inputenc}" << endl << endl;
	fout << "\\usepackage{minted}" << endl;

	fout << "\\pagestyle{headandfoot}" << endl;
	fout << "\\runningheader{" << argv[3] << "}{" << argv[2] << "}{Page \\thepage}" << endl;
	fout << "\\firstpagefooter{}{}{}" << endl;
	fout << "\\runningfooter{}{}{}" << endl;
	fout << "\\runningheadrule" << endl;
	
	fout << "\\title{" << argv[2] << "}" << endl;
	fout << "\\author{" << argv[3] << "\\\\" << endl 
		<< argv[4] << "\\\\" << endl 
		<< argv[5] << "\\\\" << endl
		<< "\\textsc{" << argv[6] << "}}" << endl;
	fout << "\\date{\\today}" << endl;

	fout << "\\begin{document}" << endl;
	fout << "\\maketitle" << endl;
	fout << "\\pagenumbering{arabic}" << endl;
	fout << "\\begin{questions}" << endl;

	for (auto filename = fileorder.begin(); filename != fileorder.end(); filename++) {
		ifstream qin;
		qin.open(targetfolder + *filename);

		if (qin.fail()) {
			cerr << "\033[31m" << "unable to open filename:" << targetfolder 
				<< *filename << "\033[31m" <<endl;
			exit(10);
		}

		while (getline(qin,line)) {
			tmp.append(line).append("\n");
		}

		fout << "\\question" << endl << extractquestion(&tmp) << endl;
		fout << "\\begin{minted}[frame=lines, linenos]{" << getextension(*filename) << "}" << endl;
		fout << tmp << endl;

		qin.close();
		cout << "adding code snippet from " << targetfolder + *filename << endl;

		fout << "\\end{minted}" << endl;
		fout << "\\newpage" << endl;

		tmp = "";
	}

	fout << "\\end{questions}" << endl;
	fout << "\\thanks" << endl;
	fout << "\\end{document}";

	fout.close();

	cout << "TeX file created!" << endl;

	return 0;
}

string getextension(string filename) {
	vector<string> tokens;
	boost::split(tokens, filename, boost::is_any_of("."));
	return tokens.back();
}

string extractquestion(string *content) {
	smatch match;

	// thank you stack overflow
	regex re("^/\\*[^*]*\\*+(?:[^/*][^*]*\\*+)*/");

	if(regex_search(*content,match,re)) {
		string str = match.str(0);

		content->erase(0, str.size());
		
		size_t start = str.find("/*");
		if (start != string::npos) {
			str.replace(start, 2, "");
		}
		
		start = str.find("*/");
		if (start != string::npos) {
			str.replace(start, 2, "");
		}

		return str;
	}
	else
		return "Question couldn't be parsed. Edit the tex file manually.";
}
