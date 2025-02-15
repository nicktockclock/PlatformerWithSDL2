#ifndef UTILS_H
#define UTILS_H

class Utils {
    public:
        /* unsigned int split
        * Split a string <txt> everywhere a certain character <ch> is found
        * Store the substrings made in a new vector <strs>
        * Return the size of the vector
        */
        static unsigned int split(const std::string &txt, std::vector<std::string> &strs, char ch){
            int pos = txt.find(ch);
            int initialPos = 0;
            strs.clear();
            //While txt.find(ch) is able to be found in the string
            while (pos != std::string::npos){
                strs.push_back(txt.substr(initialPos, pos - initialPos + 1));
                initialPos = pos + 1;

                pos = txt.find(ch, initialPos);
            }
            //Add the last one
            strs.push_back(txt.substr(initialPos, std::min<int>(pos, txt.size() - (initialPos + 1))));
            return strs.size();
            //25,26,28
        }

};

#endif