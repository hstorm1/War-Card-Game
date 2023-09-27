/** *********************************************************************
 * @file
 *
 * @brief checks for file input and output
 ***********************************************************************/

#include "thpef.h"

/** *********************************************************************
 * @author David Hill
 *
 * @par Description:
 * This function opens an input file, checks if it's open,
 * and if not, will return an error message.
 *
 * @param[in] in - the input stream.
 * @param[in] file - the file name to open.
 *
 * @returns a boolean value. True if the file opened correctly and false
 * if it did not.
 *
 * @par Example:
   @verbatim
   ifstream in;
   string s = argv[3];
   openInput(in, s);

   output: true
   @endverbatim

 ***********************************************************************/



bool openInput(ifstream& in, string file)
{
    // open the file
    in.open(file);

    // if it didn't open correctly, output error message
    if (!in.is_open())
    {
        cout << "Unable to open input file: " + file << endl;
        return false;
    }
    return true;
}



/** *********************************************************************
 * @author David Hill
 *
 * @par Description:
 * This function opens an output file, checks if it's open,
 * and if not, will return an error message.
 *
 * @param[in] out - the output stream.
 * @param[in] file - the file name to open.
 *
 * @returns a boolean value. True if the file opened correctly and false
 * if it did not.
 *
 * @par Example:
   @verbatim
   ofstream out;
   string s = argv[3];
   openInput(out, s);

   output: true
   @endverbatim

 ***********************************************************************/



bool openOutput(ofstream& out, string file)
{
    // open the file
    out.open(file);

    // if it didn't open correctly, output error message
    if (!out.is_open())
    {
        cout << "Unable to open output file: " + file << endl;
        return false;
    }
    return true;
}