#include<string>
#include<iostream>
#include<fstream>

//c++ takes these arguments, must have the same signature as C, it has two parameters:
//arg is "argument count"
//char* is a pointer to a list of chars = a string
//char** is a vector of pointers = a vector of strings
    //Can also be written as char* argv[]
int main(int argc, char** argv) {
    std::string infile = " ",
                outfile = " ";

    //The first argument (i = 0) is the name of the command, which is usually not interesting
    for(int i = 0; i<argc; ++i){
        std::string arg = argv[i];
        std::cout << "arg[" << i << "] = " << arg << "\n"; //We dont want to flush the buffer (std::endl does this)
        //Calling ./main 1 2 3 4 just prints the four parameters 1 2 3 4 to the output stream
        
        //-- often means the 'long' version of parameter names(?)
        if(arg == "--input" && i+1<argc) infile = argv[i + 1];
        if(arg == "--output" && i+1<argc) outfile = argv[i + 1];
    }
    std::cerr << "infile=" << infile << "   outfile=" << outfile << "\n";
    if(infile== " " || outfile == " ") return 0;

    //Input file stream
    std::ifstream instream(infile); //Shorthand without "new", variable decleration is moemory allocation(?) - Automatically calls the parametarized constructur
    std::ofstream outstream(outfile, std::ios::app);

    std::string word;
    //>> extract the first token from the stream, any whitespace (space, tab, enter) seperates tokens
    //Once instream has no more tokens, it retuns false (probably)
    while(instream >> word) outstream << word; //Insert word into the outstream

    instream.close();
    outstream.close();
}