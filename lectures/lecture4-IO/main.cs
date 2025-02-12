class main{
    //The Main function takes a string of arguments as input "args"
    static int Main(string[] args) {
        foreach(string arg in args) System.Console.Out.WriteLine("stdout: " + arg); //Write to the standard output
        foreach(string arg in args) System.Console.Error.WriteLine("stderr: " + arg); //Write to the standard error output
        for(string line = System.Console.In.ReadLine(); 
            line!=null; 
            line = System.Console.In.ReadLine()) {
                System.Console.Out.WriteLine($"line for stdin: {line}"); 
        }
        
        //We want to add parameter comprehension:
        string inputfile =" ",
                outputfile=" ";
        foreach(string arg in args) { //Check that the input and output file get proper names
            string[] words = arg.Split(":"); //We use the typical Makefile syntax, with : used to seperate parameter name and value
            if(words[0] == "-input") inputfile = words[1];
            if(words[0] == "-output") outputfile = words[1];
        }
        System.Console.Error.WriteLine($"inputfile = {inputfile}, outputfile = {outputfile}");

        if(inputfile == " " || outputfile == " ") return 0;

        //var means that the compiler has to figure out what the type is
        var instream = new System.IO.StreamReader(inputfile); //Open streams for input and output
        var outstream = new System.IO.StreamWriter(outputfile,append:true);
        //We might typically check here that the streams are actually open
        
        for(
            string line = instream.ReadLine();
            line != null;
            line = instream.ReadLine()
        ) {
            outstream.WriteLine($"line from instream: {line}");
        }

        instream.Close(); //Some systems might do this when main exits, but we cannot be sure of that
        outstream.Close();

        return 0;
    }
}