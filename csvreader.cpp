#include "csvreader.h"

namespace csvreader
{
    // Read chars from the stream until a new line delimiter is reached.
    std::string readTillLine (std::ifstream& file, char delim)
    {
        char cbuf = ' ';
        std::string line = "";
        while (cbuf != delim && !file.eof())
        {
            line += cbuf;
            file >> cbuf;
            std::cerr << int(cbuf) << ' ';
        }
        std::cerr << std::endl;
        line = line.substr(1);
        return line;
    }

    // Break the line into tokens using the given delimiter
    void tokenize (std::string line, char delim, std::vector<std::string>& tokens)
    {
        tokens.clear();
        // Make sure to save all tokens
        line += delim;
        std::string ctok;
        char cbuf;
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == delim)
            {
                tokens.push_back(ctok);
                ctok = "";
            }
            else
                ctok += line[i];
        }
    }

    // Break the line into tokens using the given delimiter
    void tokenize (std::string line, char delim, csvline& tokens)
    {
        std::vector<std::string> vecbuf;
        tokenize (line, delim, vecbuf);
        tokens.clear();
        for (int i = 0; i < vecbuf.size(); i++)
            tokens.push_back(vecbuf[i]);
    }

    void csvline::operator = (std::vector<std::string>& vec)
    {
        clear();
        for (int i = 0; i < vec.size(); i++)
            push_back(vec[i]);
    }

    void csvreader::readFile (const char* filename, char fieldDelimiter)
    {
        std::ifstream csv (filename, std::ios::binary);
        std::string line;
        csvline cline;

        #ifdef lineDelimiter
        line = readTillLine(csv, lineDelimiter);
        #else
        getline(csv, line);
        #endif
        
        tokenize(line, fieldDelimiter, columnList);
        for (int i = 0; i < columnList.size(); i++)
            columnMap[columnList[i]] = i;

        while (!csv.eof())
        {
            #ifdef lineDelimiter
            line = readTillLine(csv, lineDelimiter);
            #else
            getline(csv, line);
            #endif
            tokenize(line, fieldDelimiter, cline);
            cline.parent = this;
            lines.push_back(cline);
        }

        csv.close();
    }

    std::string csvline::operator [] (std::string field) const
    {
        assert (parent != nullptr);
        int index = parent->columnMap[field];
        std::cerr << "`" << index << "`" << std::endl;
        if (index >= this->size())
            return "";
        return this->data()[index];
    }
};