#include "Task.h"
#include <string>
#include <filesystem>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <vector> //added by elfin
#include <fstream> //added by elfin

struct outputlist
{
	std::string activity; // 1. edt_actv (INSERT)
	std::string varname; // 2. var_name
	std::string readorwrite; // 3. op (READ or WRITE)
	int node_id; // 4. I left it blank (!!!!)
	int sequenceOrder; // 5. order of Sequence
};

void saveCodeToFile(const std::string& code, const std::string& fileName, const std::string& fileName2)
{
	std::ofstream ostream(fileName); //code
	std::ofstream ostream2(fileName2); //parsed 

    ostream << code;

    std::stringstream test(code);
    std::string segment;
    std::vector<std::string> seglist;
    int node_count = 0;
    int line_num = 0;
    while (std::getline(test, segment))
    {
        std::string s = segment;
        s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
        std::string var_left;
        std::string var_right;
        std::string sign;
        size_t pos = 0;
        int isanif = 0;

        if (s == "{" || s == "}") {
            node_count++;
            if (s == "}")
                line_num++;
            if (s == "{")
                line_num = 0;
            continue;
        }

        if (s.find("if") != std::string::npos) {
            sign = "==";
            while ((pos = s.find(sign)) != std::string::npos) {
                var_left = s.substr(3, pos - 3); //change to -3 later
                //std::cout << "var_left = " << var_left << std::endl;
                s.erase(0, pos + sign.length());
                s.erase(s.length() - 1);
                var_right = s;
                isanif = 1;
                node_count++;
            }
        }
        else if (s.find("while") != std::string::npos) {
            sign = "==";
            while ((pos = s.find(sign)) != std::string::npos) {
                var_left = s.substr(6, pos - 6); //change to -5 later
                //std::cout << "var_left = " << var_left << std::endl;
                s.erase(0, pos + sign.length());
                s.erase(s.length() - 1);
                var_right = s;
                isanif = 1;
            }
        }
        else {
            sign = "=";
            while ((pos = s.find(sign)) != std::string::npos) {
                var_left = s.substr(0, pos);
                //std::cout << "var_left = " << var_left << std::endl;
                s.erase(0, pos + sign.length());
                s.erase(s.length() - 1);
                var_right = s;
            }
        }

        int yaithave = 0;
        if (var_right.find("+") != -1) {
            sign = "+";
            yaithave = 1;
        }
        if (var_right.find("-") != -1) {
            sign = "-";
            yaithave = 1;
        }
        if (var_right.find("*") != -1) {
            sign = "*";
            yaithave = 1;
        }
        if (var_right.find("/") != -1) {
            sign = "/";
            yaithave = 1;
        }
        std::string var_right1;
        std::string var_right2;
        if (yaithave == 1) {
            pos = 0;
            while ((pos = var_right.find(sign)) != std::string::npos) {
                var_right1 = var_right.substr(0, pos);
                //std::cout << "var_right1 = " << var_right1 << std::endl;
                var_right.erase(0, pos + sign.length());
                var_right2 = var_right;
            }
            //std::cout << "var_right2 = " << var_right2 << std::endl;
        }
        else {
            //std::cout << "var_right = " << var_right << std::endl;
        }

        std::vector<outputlist> outputlist_vect;

        if (yaithave == 0 && isanif == 0)
        {
            int sequenceCount = 0;
            // one READ and one WRITE
            // READ first
            bool notdigit = false;
            for (int i = 0; i < var_right.size(); i++)
            {
                if (var_right[i] != '0' && var_right[i] != '1' && var_right[i] != '2' && var_right[i] != '3' && var_right[i] != '4' && var_right[i] != '5' && var_right[i] != '6' && var_right[i] != '7' && var_right[i] != '8' && var_right[i] != '9')
                {
                    notdigit = true;
                    break;
                }
            }
            if (notdigit)
            {
                outputlist outputlist1;
                outputlist1.activity = "INSERT";
                outputlist1.varname = var_right;
                outputlist1.readorwrite = "READ";
                outputlist1.node_id = node_count; // don't forget node_id
                outputlist1.sequenceOrder = line_num;
                line_num++;
                outputlist_vect.push_back(outputlist1);
            }

            // then KILL
            outputlist outputlist2;
            outputlist2.activity = "INSERT";
            outputlist2.varname = var_left;
            outputlist2.readorwrite = "KILL";
            outputlist2.node_id = node_count; // don't forget node_id
            outputlist2.sequenceOrder = line_num;
            line_num++;
            outputlist_vect.push_back(outputlist2);

            outputlist outputlist3;
            outputlist3.activity = "INSERT";
            outputlist3.varname = var_left;
            outputlist3.readorwrite = "WRITE";
            outputlist3.node_id = node_count; // don't forget node_id
            outputlist3.sequenceOrder = line_num;
            line_num++;
            outputlist_vect.push_back(outputlist3);
        }
        else if (yaithave == 1 && isanif == 0)
        {
            int sequenceCount = 0;
            // two READs and one WRITE
            // first READ: var_right1
            bool notdigit1 = false;
            for (int i = 0; i < var_right1.size(); i++)
            {
                if (var_right1[i] != '0' && var_right1[i] != '1' && var_right1[i] != '2' && var_right1[i] != '3' && var_right1[i] != '4' && var_right1[i] != '5' && var_right1[i] != '6' && var_right1[i] != '7' && var_right1[i] != '8' && var_right1[i] != '9')
                {
                    notdigit1 = true;
                    break;
                }
            }
            if (notdigit1)
            {
                outputlist outputlist1;
                outputlist1.activity = "INSERT";
                outputlist1.varname = var_right1;
                outputlist1.readorwrite = "READ";
                outputlist1.node_id = node_count; // don't forget node_id
                outputlist1.sequenceOrder = line_num;
                line_num++;
                outputlist_vect.push_back(outputlist1);
            }

            // second READ: var_right2
            bool notdigit2 = false;
            for (int k = 0; k < var_right2.size(); k++)
            {
                if (var_right2[k] != '0' && var_right2[k] != '1' && var_right2[k] != '2' && var_right2[k] != '3' && var_right2[k] != '4' && var_right2[k] != '5' && var_right2[k] != '6' && var_right2[k] != '7' && var_right2[k] != '8' && var_right2[k] != '9')
                {
                    notdigit2 = true;
                    break;
                }
            }
            if (notdigit2)
            {
                outputlist outputlist2;
                outputlist2.activity = "INSERT";
                outputlist2.varname = var_right2;
                outputlist2.readorwrite = "READ";
                outputlist2.node_id = node_count; // don't forget node_id
                outputlist2.sequenceOrder = line_num;
                line_num++;
                outputlist_vect.push_back(outputlist2);
            }

            // then WRITE
            outputlist outputlist3;
            outputlist3.activity = "INSERT";
            outputlist3.varname = var_left;
            outputlist3.readorwrite = "KILL";
            outputlist3.node_id = node_count; // don't forget node_id
            outputlist3.sequenceOrder = line_num;
            line_num++;
            outputlist_vect.push_back(outputlist3);

            outputlist outputlist4;
            outputlist4.activity = "INSERT";
            outputlist4.varname = var_left;
            outputlist4.readorwrite = "WRITE";
            outputlist4.node_id = node_count; // don't forget node_id
            outputlist4.sequenceOrder = line_num;
            line_num++;
            outputlist_vect.push_back(outputlist4);
        }
        else if (isanif == 1 && yaithave == 0) {
            line_num = 0;
            bool notdigit = false;
            for (int i = 0; i < var_right.size(); i++)
            {
                if (var_right[i] != '0' && var_right[i] != '1' && var_right[i] != '2' && var_right[i] != '3' && var_right[i] != '4' && var_right[i] != '5' && var_right[i] != '6' && var_right[i] != '7' && var_right[i] != '8' && var_right[i] != '9')
                {
                    notdigit = true;
                    break;
                }
            }
            if (notdigit)
            {
                outputlist outputlist1;
                outputlist1.activity = "INSERT";
                outputlist1.varname = var_right;
                outputlist1.readorwrite = "READ";
                outputlist1.node_id = node_count; // don't forget node_id
                outputlist1.sequenceOrder = line_num;
                line_num++;
                outputlist_vect.push_back(outputlist1);
            }

            // then WRITE
            outputlist outputlist2;
            outputlist2.activity = "INSERT";
            outputlist2.varname = var_left;
            outputlist2.readorwrite = "READ";
            outputlist2.node_id = node_count; // don't forget node_id
            outputlist2.sequenceOrder = line_num;
            line_num++;
            outputlist_vect.push_back(outputlist2);
        }

        for (int j = 0; j < outputlist_vect.size(); j++)
        {
            if (j != 0) ostream2 << "\n";
            ostream2 << "(" << outputlist_vect[j].activity << ", "
                << outputlist_vect[j].varname << ", "
                << outputlist_vect[j].readorwrite << ", "
                << outputlist_vect[j].node_id << ", " // don't forget to modify node_id
                << outputlist_vect[j].sequenceOrder << ")";
        }
        ostream2 << '\n' << '\n';
    }
}

std::string loadCodeFromFile(const std::string& fileName)
{
	std::ifstream istream(fileName);
	std::string description;
	istream >> description;

	return description;
}