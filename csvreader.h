#ifndef __CSVREADER_H__
#define __CSVREADER_H__

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace csvreader
{
    class csvreader;

    class csvline : public std::vector<std::string>
    {
        friend class csvreader;
    private:
        csvreader* parent;
    public:
        std::string operator [] (std::string field) const;
        void operator = (std::vector<std::string>& vec);
    };

    class csvreader
    {
        friend class csvline;
    private:
        std::vector<std::string> columnList;
        std::map<std::string,int> columnMap;
    public:
        /* All lines of the file. A line can be addressed using 0-based index, and then 
           the field name. */
        std::vector<csvline> lines;
        // Read csv file into current instance of `csvreader`
        void readFile (const char* filename, char fieldDelimiter = ',');
        inline csvline operator [] (int index) const { return lines.at(index); }
        //inline std::vector<std::string>& columns() { return columnList; }
        // Provide access to column header names
        inline std::string columns (int num) { return columnList.at(num); }
        // Number of lines of the parsed csv file
        inline int size() { return lines.size(); }
        inline int columnNum() { return columnList.size(); }
    };
};

#endif
