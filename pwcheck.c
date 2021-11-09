/**
 * @name Projekt 1 - Práce s textem
 * @author János László Vasík
 *  <xvasik05@fit.vutbr.cz>
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define maxSize 100

struct stats
{
    char asciiArr[128];
    int allLength;
    int whileCount;
    int shortPw;
};

/*
This function tries to find a character in the given string, and replace it with another character.
This will ensure that all paswords will be compatible with the same processes.

@param password - the pointer wich points to the current password
@param target - the character which the function tries to fidn and replace
@param newChar - the character which will be put on the position of the target character
*/
void replace(char *password, char target, char newChar)
{
    // The for cycle goes from the first character to the last.
    for(int i = 0; i < 101; i++)
    {
        // If the current character in the string named "password" is the "target" one, we replace it with the "newChar" cahracter.
        if(password[i] == target)
        {
            password[i] = newChar;
            break;
        }
        // Or if it finds the "newChar" character first, it stops.
        else if(password[i] == newChar)
        {
            break;
        }
    }
}

/*
This function counts the characters of a given string until it finds the '/0' character and then returns the number of the characters.

@param password - the pointer wich points to the current password
@return count - the number of characters before the '/0' character
*/
int length(char *password)
{
    int count = 0;
    
    while(password[count] != '\0')
    {
        count++;
    }
    return count;
}

/*
This function converts the first argument "LEVEL" of the main() function to an integer and returns it, so it can be used by the security check.

@param level - pointer which points to the first argument of the main() function named "LEVEL"
@return Level - converted format of the first argument
*/
int convertLevel(char *level)
{
    int Level;
    char *ptr;
    Level = strtol(level, &ptr, 10);
    // If the first argument contains other characters than numbers, it returns a -1. 
    if(ptr[0] != '\0')
    {
        return -1;
    }
    // If the first argument is too big, or too small, it returns a -2.
    else if(Level < 1 || Level > 4)
    {
        return -2;
    }
    else
    {
        return Level;
    }
}

/*
This function converts the second argument "Param" of the main() function to a long and returns it, so it can be used by the security check.

@param param - pointer which points to the second argument of the main() function named "Param"
@return Param - converted format of the second argument
*/
int convertParam(char *param)
{
    long Param;
    char *ptr;
    Param = strtol(param, &ptr, 10);
    //If the second argument contains other characters than numbers, it returns a -1.
    if(ptr[0] != '\0')
    {
        return -1;
    }
    //If the second argument is too big or too small, it returns a -2.
    else if(Param < 1 || Param > LONG_MAX)
    {
        return -2;
    }
    else
    {
        return Param;
    }
}

/*
This function compares two strings.

@param str1/str2 - the two strings it is going to compare.
@return - if the strings are identical, it returns a 0, if not, then a 1. 
*/
int compare(char *str1, char *str2)
{
    // The cycle iterates until it reaches the end of one of the strings, or until there's a difference between them.
    while(( *str1 != '\0' && *str2 != '\0' ) && *str1 == *str2 )
    {
        str1++;
        str2++;
    }
    // Atfer it got to the last element of the strings, it checks if they're identical.
    if (*str1 == *str2)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/*
This function checks if the third argument exists, if yes, it checks if it is correctly written.

@param arg3 - the pointer which points to the 3rd argument of the main() function.
@return - if it extists, it returns a 0, if it doesn't, then a 1. If it exists but is incorrect, it returns a -1
*/
char checkArg3(char *arg3)
{
    char *stats = "--stats";
    if(arg3)
    {
        if(compare(arg3, stats) == 0)
        {
            return 0;    
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return 1;
    }
}

/*
This function checks if the current password is shorter than the previous shortest one, if yes, it returns its length.

@param Length - length of current password.
@param Stats - a variable from the data structure.
@return Length/Stats.shortPw - the function returns the smaller one of the two variables. 
*/
int minLength(int Length, struct stats Stats)
{
    if(Length < Stats.shortPw)
    {
        return Length;
    }
    else
    {
        return Stats.shortPw;    
    }
}

/*
This function finishes and prints out the statistics that can be initialized with the "--stats" argument.

@param Stats - a variable from the data structure.
*/
void statPrint(struct stats Stats)
{
    int characterCount = 0;
    // With a cycle it sums up the '1's in the ASCII array, and save it to the characterCount variable. 
    for (int i = 0; i < 128; ++i)
    {
		characterCount += Stats.asciiArr[i];
	}
    // Here the the average length is calculated and converted to a float.
    float avgLength = (float) Stats.allLength / Stats.whileCount;
    printf("Statistika:\nRuznych znaku: %d\nMinimalni delka: %d\nPrumerna delka: %.1f\n", characterCount, Stats.shortPw, avgLength);
}

/*
In this function of the program the function evaluates the level of security of the given password,
according to the parameters of the main() function named "LEVEL" and "PARAM".
The function returns the ammount of levels passed by the password. 
To ensure that the given password also meets the requirements of the levels lower than the given level,
"// fall through" comments were added at the end of each case.

@param password - the current password.
@param Param - the value of the second argument given by the user.
@param Level - the value of the first argument given by the user.
@param Length - the length of the current password.

@return passwordGood - number of levels, that the password passed.
*/
int security(char *password, long Param, int Level, int Length)
{
    int passwordGood = 0;
    int passwordBad = 0;
    int tempParam = 0;
    int groupCount;
    char buffer[maxSize];
    char buffer2[maxSize];
    switch (Level)
    {
    // If Level = 4, then the function checks if the given password doesn't contain at least 2 substrings with the minimum length
    // given by "Param". If it doesn't, the password passes (1 is added to the passwordGood variable).
    case 4:
        // This cycle goes through the password character-by-character, until there's not enough characters left for the second substring.
        for (int i = 0; i + Param <= Length; i++)
        {
            int temp = i;
            int charNmbr = 0;
            // Here the function copies the first substring with "Param" length.
            for (int k = i; temp + Param > k; k++)
            {
                buffer[charNmbr] = password[k];
                charNmbr++;
            }
            // To ensure that the substrings have the same format, it inserts a '\0' character at the end.
            buffer[charNmbr] = '\0';
            // Now the second cycle will begin from the first cycle's position+1. This cycle also goes until no substring fits into the character chain.
            for (int u = temp + 1; u + Param <= Length; u++)
            {
                int temp2 = u;
                int charNmbr2 = 0;
                // This cycle copies the second substring.
                for (int j = u; temp2 + Param > j; j++)
                {
                    buffer2[charNmbr2] = password[j];
                    charNmbr2++;
                }
                // Here we also insert the '\0' at the end.
                buffer2[charNmbr2] = '\0';
                // With the compare() function we check if the two substrings are the same, if yes, we add one to the "passwordBad" variable.
                if (compare(buffer, buffer2) == 0)
                {
                    passwordBad++;
                    break;
                }
                else
                {
                    continue;
                }
            }
        }
        // If the function didn't find any substrings that're the same, the password passes, and one is being added to the "passwordGood" variable.
        if (passwordBad == 0)
        {
            passwordGood++;
        }

    // fall through
    // If Level = 3, then the function checks if the given password has the same characters
    // in a sequence somewhere in the password. If the password doesn't have a sequence of 
    // the same character longer than or same length as "Param", the password passes.
    case 3:
        passwordBad = 0;
        // This cycle will iterate through the given password until it reaches it's end.
        for (int i = 0; i < Length; i++)
        {
            int temp = i;
            int charCount = 0;
            // It saves the current first character of the password into the "fchar" variable.
            char fchar = password[i];
            // This iteration will iterate until it goes through as many characters as is given by the value of "Param".
            for (int i = temp; i < i + Param; i++)
            {
                // If the current first character of the password matches the next one, 1 is being added to the "charCount" variable.
                if(fchar == password[i])
                {
                    charCount++;
                    continue;
                }
                else
                // If they dont match, it breaks the cycle and continues with the next character of the password in the outer iteration.
                {
                    break;
                }
            }
            // If there's as many characters in a sequence as the "Param" has value, 1 is being added to the "passwordBad" variable.
            if (charCount == Param)
            {
                passwordBad++;
                break;
            }
            else
            {
                continue;
            }
        }
        // If there were no such cases, the function adds 1 to the "passwordGood" variable.
        if (passwordBad == 0)
        {
            passwordGood++;
        }
        
    // fall through
    // If Level = 2, then the function checks how many groups's requirements the given password meets.
    // If this number equals, or exceeds "Param", the password passes.
    case 2:
        groupCount = 0;
        // If the value of "Param" is bigger than 4, then the function is going to search for all 4 groups of characters.
        if(Param >= 4)
        {
            tempParam = 4;
        }
        // Otherwise its going to check for as many groups as given by "Param".
        else
        {
            tempParam = Param;
        }
        // This command will iterate through the password, and search for the letters of the lower-case alphabet.
        for(int i = 0; i < Length; i++)
        {
            // If it finds a character that is in the lower-case alphabet, it adds 1 to the "groupCount" variable.
            if(password[i] >= 'a' && password[i] <= 'z')
            {
                groupCount++;
                break;
            }
            else
            {
                continue;
            }
        }
        // This command will iterate through the password, and search for the letters of the upper-case alphabet.
        for(int c = 0; c < Length; c++)
        {
            // If it finds a character that is in the upper-case alphabet, it adds 1 to the "groupCount" variable.
            if(password[c] >= 'A' && password[c] <= 'Z')
            {
                groupCount++;
                break;
            }
            else
            {
                continue;
            }
        }
        // This command will iterate through the password, and search for numbers.
        for(int u = 0; u < Length; u++)
        {
            // If it finds a character that is a number, it adds 1 to the "groupCount" variable.
            if(password[u] >= '0' && password[u] <= '9')
            {
                groupCount++;
                break;
            }
            else
            {
                continue;
            }
        }
        // This command will iterate through the password, and search for any special characters in the ASCII range 32-126.
        for(int i = 0; i < Length; i++)
        {
            // If it finds a character that is in this group, it adds 1 to the "groupCount" variable.
            if((password[i] >= 32 && password[i] <= 47) || (password[i] >= 58 && password[i] <= 64) || (password[i] >= 91 && password[i] <= 96) || (password[i] >= 123 && password[i] <= 126))
            {
                groupCount++;
                break;
            }
            else
            {
                continue;
            }
        }
        // If the password passes the requirements of at least as much groups as the value of "Param", 1 is being added to the "passwordGood" variable.
        if (groupCount >= tempParam)
        {
            passwordGood++;
        }

    // fall through
    // If Level = 1, then the function checks if the given password contains both small and big letters. If it does, the password passes.
    case 1:
        // This cycle will iterate through the password.
        for(int i = 0; i < Length; i++)
        {
            // If it first finds an upper-case letter, then it starts another cycle from the previous+1, and searches for a lower-case letter. 
            if (password[i] >= 'A' && password[i] <= 'Z')
            {
                int temp = i+1;
                for (int i = temp; i < Length; i++)
                {
                    if (password[i] >= 'a' && password[i] <= 'z')
                    {
                        // If it finds both upper and lower case characters, it adds 1 to the "passwordGood" variable.
                        passwordGood++;
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
                break;
            }
            // If it first finds a lower-case letter, then it starts another cycle from the previous+1, and searches for an upper-case letter. 
            else if (password[i] >= 'a' && password[i] <= 'z')
            {
                int temp = i+1;
                for (int i = temp; i < Length; i++)
                {
                    if (password[i] >= 'A' && password[i] <= 'Z')
                    {
                        // If it finds both lower and upper case characters, it adds 1 to the "passwordGood" variable.
                        passwordGood++;
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
                break;
            }
            else
            {
                continue;
            }
        }
        break;
    default:
        break;
    }
    // In the end it returns the value of "passwordGood", so we can check how many groups did it pass.
    return passwordGood;
}

/*
In this simple function the program checks if the given password meets the requirements of all the needed levels, if yes, it prints it out.
@param password - the current password.
@param Level - the value of the first argument given by the user. 
@param passwordGood - the number of levels passed by the password.
*/
void printCheck(char *password, int Level, int passwordGood)
{
    // If the number of levels passed by the password equals the value of "Level", the password is printed out to the user.
    if (passwordGood == Level)
    {
        printf("%s\n", password);
    }
}

/*
In the main function the separate, aforementioned functions are all being used to get a password from the user, then check if it's a valid
password, in which case it prints the password out, then it repeates, until it gets an EOF. (ctrl+d in the terminal)

@param argv[1] - The first argument will give the number of levels that the given password needs to pass. 
@param argv[2] - The second argument will give the parameter ("Param"), which will determine some key aspects of the security() funkcion.
@param argv[3] - The third argument is used to initialize the statPrint() function.
*/
int main(int argc, char* argv[])
{
    struct stats Stats = {.asciiArr = {0}, .allLength = 0, .whileCount = 0, .shortPw = 100};

    char password[102];

    int Level;
    int Stat;
    int passwordGood;
    int Length;

    long Param;
    // Here it checks if there were not less than 3 and no more than 4 arguments passed when initializing the program.
    if(argc < 3 || argc > 4)
    {
        fprintf(stderr,"Please use at least 2, or maximum 3 arguments! The third being --stats.\n");
        return -2;
    }
    // Here we convert the first and second argument from a string to a value, and save them to the "Level" and "Param" variables.
    Level = convertLevel(argv[1]);
    Param = convertParam(argv[2]);
    // The return value of the checkArg() function is saved to the "Stat" variable.
    Stat = checkArg3(argv[3]);
    // Here it checks if the third argument is in the correct form.
    if(Stat == -1)
    {
        fprintf(stderr,"Please use the correct format of the third argument, which is: '--stats'.\n");
        return -1;
    }
    // Here it checks if the first and second argument is in the correct form.
    if(Level == -1 || Param == -1)
    {
        fprintf(stderr,"Please don't use characters other than positive numbers in the first two arguments!\n");
        return -1;
    }
    // Here it checks if the first argument is in the correct range.
    if(Level == -2)
    {
        fprintf(stderr,"For the first argument please only use a number in the range (1,4).\n");
        return -2;
    }
    // Here it checks if the second argument is in the correct range.
    if(Param == -2)
    {
        fprintf(stderr,"For the second argument please only use numbers in the range (1,LONG_MAX).\n");
        return -2;
    }
    // Here is the cycle that will ensure that the user can input an endless number of passwords, until the function detects an EOF. 
    while(fgets(password, 102, stdin) != NULL)
    {
        // To ensure compatbility, here it exchanges the '\n' character to a '\0'.
        replace(password,'\n','\0');
        // Here it checks if the password is longer than the max length (100).
        if(password[99] && password[100] != '\0')
        {
            fprintf(stderr,"There are too many characters in the password you've given. The max length of passwords is a 100 characters.\n");
            return -2;
        }
        // Now the function measures the length of the password, and saves it to the variable "Length".
        Length = length(password);
        // Here we make the stats, if the '--stats' parameter has been used. 
	    if(Stat == 0)
        {
            // This cycle takes the integer value of a given character, and into the position in the "asciiArr", given by this value, it inserts a 1.
            for (int i = 0; i < Length; ++i)
            {
            int currentValue = password[i];
	        Stats.asciiArr[currentValue] = 1;
	        }
            // Checking if the shortest password is the current one, if yes, it's saved to the "shortPw" variable.
            Stats.shortPw = minLength(Length, Stats);
            // Here it adds the current length to the previous ones.
            Stats.allLength += Length;
            // The number of entered passwords are being counted, so it can make the average statistics later.
            Stats.whileCount++;
        }
        // The return value of the security() function is saved to the "passwordGood" variable.
        passwordGood = security(password, Param, Level, Length);
        // This function prints out the password, if it has passed.
        printCheck(password, Level, passwordGood);
    }
    // If the '--stats' parameter has been used, the stats are being printed out after the user inputs an EOF. 
    if(Stat == 0)
    {
        statPrint(Stats);
    }
    return 0;
}