#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>

#include <stdexcept>
#include <cstdlib>

class TextQuery{
public:
	// typedef to make declarations easier
	typedef std::vector<std::string>::size_type line_no;
	/*
	 * interface:
	 *     read_file builds internal data structures for the given file
	 *     run_query finds the given word and return set of lines on which it appears
	 *     text_line returns a requested line from the input file
	 */
	void read_file(std::ifstream &is);
	std::set<line_no> run_query(const std::string &find) const;
	std::string text_line(line_no lno) const;

private:
	//utility functions used by read_file
	void store_file(std::ifstream &input_file); // store input file
	void build_map(); //associated each word with a set of line numbers
	// remember the whole input file
	std::vector<std::string> lines_of_text;
	//map word to set of the lines on which it occurs
	std::map<std::string, std::set<line_no> > word_map;
};

bool open_file( std::ifstream& input_file, std::string filename);

void print_results(std::set<TextQuery::line_no> locs, std::string word, TextQuery tq);

std::string make_plural(size_t ctr,const std::string &word, const std::string &ending);

int main(int argc, char **argv) {
	//open the file from which user will query words
	std::ifstream infile;
	if( argc < 2 || !open_file(infile, argv[1])) {
		std::cerr << "No input file!" << std::endl;
		return EXIT_FAILURE;
	}
	TextQuery tq;
	tq.read_file(infile); //builds query map
	// iterate while the user:prompt for a word to find and print results
	// loop indefinitely; the loop exit is inside the while
	while( true) {
		std::cout << "enter word to look for, or q to quit: ";
		std::string s;
		std::cin >> s;
		// stop if hit eof on input or a 'q' is entered
		if( !std::cin || s=="q") {
			break;
		}
		std::set<TextQuery::line_no> locs = tq.run_query(s);
		//print count and all occurrences, if any
		print_results(locs, s, tq);
	}
	return 0;
}

bool open_file( std::ifstream& input_file, std::string filename) {
	input_file.open( filename.c_str());
	return true;
}

void print_results( std::set<TextQuery::line_no> locs, std::string sought, TextQuery tq) {
	// if the word was found, then print count and all occurrences
	typedef std::set<TextQuery::line_no> line_nums;
	line_nums::size_type size = locs.size();
	std::cout << "\n" << sought << " occurs " << size << " "
		<< make_plural(size, "time", "s") << std::endl;
	//print each line in which the word appeared
	line_nums::const_iterator it = locs.begin();
	for( ; it != locs.end(); it++) {
		std::cout << "\t(line "
			//don't confound user with text lines starting at 0
			<< (*it) +1 << ") "
			<< tq.text_line(*it) << std::endl;
	}
}

void TextQuery::read_file(std::ifstream &is) {
	store_file(is);
	build_map();
}

std::set<TextQuery::line_no> TextQuery::run_query(const std::string &find) const {
	std::map<std::string, std::set<line_no> >::const_iterator iter;
	iter = word_map.find( find);
	if(iter == word_map.end() ) {
		return std::set<line_no>();
	}
	else {
		return iter->second;
	}
}

std::string TextQuery::text_line(line_no lno) const {
	if(lno < lines_of_text.size()) {
		return lines_of_text[lno];
	}
	throw std::out_of_range("line number out of range");
}

void TextQuery::store_file(std::ifstream &input_file) {
	std::string line;
	while( getline(input_file, line) ) {
		lines_of_text.push_back( line);
	}
}

void TextQuery::build_map() {
	std::vector<std::string>::iterator iter;
	iter = lines_of_text.begin();
	line_no lno=0;
	for(; iter != lines_of_text.end(); iter++, lno++) {
		std::string::size_type start=0, end=0, pos;
		std::string word;
		std::cout << "line:" << *iter << std::endl;
		pos = iter->find_first_of( " \t");
		while(pos < iter->size()) {
			if( pos != std::string::npos) {
				end = pos;
			}
			else {
				end = iter->size();
			}
			if( start != end) {
				std::cout << "substr(" << start << ", " << end-start << ")" << std::endl;
				word = iter->substr( start+1, end-start-1);
				if( word.size() > 0) {
					word_map[word].insert( lno);
				}
			}

			start = end;
			pos = iter->find_first_of( " \t", start+1);
		}
	}
	/*
	std::cout << "---------------- build vector----------" << std::endl;
	std::vector<std::string>::const_iterator lt_iter;
	lt_iter = lines_of_text.begin();
	std::vector<std::string>::size_type i=0;
	for( ; lt_iter != lines_of_text.end(); lt_iter++, i++) {
		std::cout << "lines_of_text[" << i << "]=" << *lt_iter << std::endl;
	}
	*/
	std::cout << "---------------- build map ------------" << std::endl;
	std::map<std::string, std::set<line_no> >::const_iterator wm_iter;
	wm_iter = word_map.begin();
	for( ; wm_iter != word_map.end(); wm_iter++) {
		std::cout << "word_map[" << wm_iter->first << "]=" << wm_iter->second.size() << std::endl;
	}
}

std::string make_plural(size_t ctr,const std::string &word, const std::string &ending)
{
	return (ctr==1) ? word : word+ending;//make_plural(wc, "word ", "s ")当输入中文本中
}
