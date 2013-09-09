#include <iostream>
#include <string>


using namespace std;


#define BOOK_ARG 1


//stackoverflow :)
static string slurp(ifstream& in) {
  stringstream sstr;
  sstr << in.rdbuf();
    return sstr.str();
}

int main (int argc, char *argv[]) {

  std::ifstream marbleFile;

  if (argc < 2) {
    cerr << "Usage: " << argv[0] << "[marblefile]"<<endl;
    return 1;
  }


  bookFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  string bookStr = slurp(marbleFile);
  try {
    bookFile.open(argv[BOOK_ARG]);
  }
  catch (std::ifstream::failure e) {
    std::cerr << "Could not open: " << argv[BOOK_ARG] << endl <<
      "Reason: " << e.what() << endl;
    return 2;
  }

  
  
}
