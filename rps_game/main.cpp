/***************************************************************************
 * rps_game - Rock, Paper, Scissors Game                                   *
 *                                                                         *
 * Copyright (C) 2015  PLLUG.Community   (info@pllug.org.ua)               *
 *                                                                         *
 * This program is free software: you can redistribute it and/or modify    *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation, either version 3 of the License, or       *
 * (at your option) any later version.                                     *
 *                                                                         *
 * This program is distributed in the hope that it will be useful,         *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
 ***************************************************************************/

#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

/*!
 * \brief The Level enum
 */
enum Level
{
    UNSPECIFIED = 0,
    EASY,
    NORMAL,
    HARD
};

const string cArgKeyLevel = "--level";
const string cArgKeyVersion = "--version";

const string cLevelStringEasy = "easy";
const string cLevelStringNormal = "normal";
const string cLevelStringHard = "hard";
const string cVersionNumer = "1.0.0";

/*!
 * \brief showHelp
 */
void showHelp()
{
    cout << "Usage:" << endl;
    cout << "  rps_game [options]" << endl;
    cout << "      --level (EASY|NORMAL|HARD)" << endl;
    cout << "          specify game difficulty (argument is required)" << endl;
    cout << "      --version" << endl;
    cout << "          output programm version" << endl;
}

/*!
 * \brief parseLevel
 * \param levelString
 * \return
 */
Level parseLevel(string levelString)
{
    Level rLevel = UNSPECIFIED;

    transform(levelString.begin(), levelString.end(), levelString.begin(), ::tolower);

    if (cLevelStringEasy == levelString)
    {
        rLevel = EASY;
    }
    else if (cLevelStringNormal == levelString)
    {
        rLevel = NORMAL;
    }
    else if (cLevelStringHard == levelString)
    {
        rLevel = HARD;
    }

    return rLevel;
}

/*!
 * \brief findArgPosition
 * \param argc
 * \param argv
 * \param argName
 * \return
 */
int findArgPosition(int argc, char* argv[], const string &argName)
{
    int rPosition = -1;

    for (int argIndex = 1; argIndex < argc; ++argIndex)
    {
        string nextArg = argv[argIndex];
        transform(nextArg.begin(), nextArg.end(), nextArg.begin(), ::tolower);

        if (argName == nextArg)
        {
            rPosition = argIndex;
        }
    }

    return rPosition;
}

/*!
 * \brief stringArg
 * \param argc
 * \param argv
 * \param argName
 * \return
 */
string stringArg(int argc, char* argv[], string argName)
{
    string result;

    int argIndex = findArgPosition(argc, argv, argName);
    if (-1 != argIndex)
    {

        if ((argIndex + 1) < argc)
        {

            result = argv[argIndex + 1];

        }
    }

    return result;
}
bool findVersion(int argc, char* argv[])
{

    int argIndex = findArgPosition(argc, argv, "--version");
    if (-1 != argIndex)
    {
        cout << "Version number is " << cVersionNumer << endl;
        return true;
    }
    return false;
}

/*!
 * \brief main
 * \param argc
 * \param argv
 * \return
 */
int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        showHelp();
        return 1;
    }

    //Parse version
    bool exitProgramm = findVersion(argc, argv);
    if (exitProgramm)
        return 0;

    // Parse level
    Level level = UNSPECIFIED;
    string levelStr = stringArg(argc, argv, cArgKeyLevel);

    if (!levelStr.empty())
    {
        level = parseLevel(levelStr);
        cout << "You selected "<< levelStr << "!" <<endl;
    }

    if (UNSPECIFIED == level)
    {
        showHelp();
        return 1;
    }
    return 0;
}


