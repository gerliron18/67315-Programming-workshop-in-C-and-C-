/**
 * @file manageStudents.c
 * @author  Liron Gershuny <liron.gershuny@mail.huji.ac.il>
 * @version 1.0
 * @date 11 Nov 2019
 *
 * @brief Program that manage students info. Will get inputs from the user of students and then
 *        can calculate the best one or just order them by grades or names.
 *
 * @section LICENSE
 * This program is not a free software; bla bla bla...
 *
 * @section DESCRIPTION
 * The program will save all info at array of student struct so it can be easy to calculate
 * things and managing order.
 * Input  : Students info by the user
 * Process: calculate the best student, arrange students by their grades and arrange by their
 *          names
 * Output : Prints to the screen the best student info, the ordered by grades students or the
 *          ordered by names students according to the user request
 */

// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// -------------------------- const definitions -------------------------
/*
 * @def NAME 0
 * @brief A flag that referenced to phrase of student name
 */
#define NAME 0

/*
 * @def COUNTRY 1
 * @brief A flag that referenced to phrase of student country
 */
#define COUNTRY 1

/*
 * @def CITY 2
 * @brief A flag that referenced to phrase of student city
 */
#define CITY 2

/*
 * @def MAX_ARR_LEN 5001
 * @brief The maximum length of students that the user can input to the program plus one for an array
 */
#define MAX_ARR_LEN 5001

/*
 * @def MAX_LINE_LEN 151
 * @brief The maximum length of line that the user can input to the program plus one for an array
 */
#define MAX_LINE_LEN 151

/*
 * @def MAX_PHRASE_LEN 41
 * @brief The maximum length of string phrase that the user can input as a student info
 *        plus one for an array
 */
#define MAX_PHRASE_LEN 41

/*
 * @def MAX_ID_LEN 11
 * @brief The maximum length of student ID that the user can input as a student info
 *        plus one for an array
 */
#define MAX_ID_LEN 11

/*
 * @def MAX_GRADE_LEN 4
 * @brief The maximum length of student grade that the user can input as a student info
 *        plus one for an array
 */
#define MAX_GRADE_LEN 4

/*
 * @def MAX_AGE_LEN 4
 * @brief The maximum length of student age that the user can input as a student info
 *        plus one for an array
 */
#define MAX_AGE_LEN 4

/*
 * @def MAX_PARM 6
 * @brief The max number of parameters of student info needed to be input by user
 */
#define MAX_PARM 6
/*
 * @def B "best"
 * @brief A flag referenced to if the user choose to produce the best student from his inputs
 */
#define B "best"

/*
 * @def M "merge"
 * @brief A flag referenced to if the user choose to order students by their grades from his inputs
 */
#define M "merge"

/*
 * @def Q "quick"
 * @brief A flag referenced to if the user choose to order students by their names from his inputs
 */
#define Q "quick"

/*
 * @def IMPROPER_USAGE_MSG "Usage: manageStudents <Order type: best | merge | quick>\n"
 * @brief A proper command line to use the program
 */
#define IMPROPER_USAGE_MSG "Usage: manageStudents <Order type: best | merge | quick>\n"

/*
 * @def PARM_NUM_ERROR "ERROR: student info must include <ID><name><grade><age><country><city>
 * @brief An error msg if the user don't enter all needed info of a student
 */
#define PARM_NUM_ERROR "ERROR: student info must include <ID><name><grade><age><country><city>\n"

/*
 * @def AGE_ERR_MSG "ERROR: age can only contain an integer between 18 and 120 inclusive\n"
 * @brief An error msg if the user input the student age invalid
 */
#define AGE_ERR_MSG "ERROR: age can only contain an integer between 18 and 120 inclusive\n"

/*
 * @def GRADE_ERR_MSG "ERROR: grade can only contain an integer between 0 and 100 inclusive\n"
 * @brief An error msg if the user input the student grade invalid
 */
#define GRADE_ERR_MSG "ERROR: grade can only contain an integer between 0 and 100 inclusive\n"

/*
 * @def ID_ERR_MSG "ERROR: ID can only contain number of 10 digits which not start with 0\n"
 * @brief An error msg if the user input the student ID invalid
 */
#define ID_ERR_MSG "ERROR: ID can only contain number of 10 digits which not start with 0\n"

/*
 * @def NAME_ERR_MSG "ERROR: name can only contain alphabetic characters, spaces or '-'\n"
 * @brief An error msg if the user input the student name invalid
 */
#define NAME_ERR_MSG "ERROR: name can only contain alphabetic characters, spaces or '-'\n"

/*
 * @def COUNTRY_ERR_MSG "ERROR: country can only contain alphabetic characters or '-'\n"
 * @brief An error msg if the user input the student country invalid
 */
#define COUNTRY_ERR_MSG "ERROR: country can only contain alphabetic characters or '-'\n"

/*
 * @def CITY_ERR_MSG "ERROR: name can only contain alphabetic characters or '-'\n"
 * @brief An error msg if the user input the student city invalid
 */
#define CITY_ERR_MSG "ERROR: name can only contain alphabetic characters or '-'\n"

// ------------------------------ functions -----------------------------

/**
 * Defining a struct of student which save all of it's info
 */
typedef struct Student
{
    char id[MAX_ID_LEN], name[MAX_PHRASE_LEN], country[MAX_PHRASE_LEN], city[MAX_PHRASE_LEN];
    int grade, age;
    float score;
} Student;

/**
 * Check that all given arguments of the program are as it should be
 * @param argc The number of given arguments
 * @param argv An array of all given arguments
 * @return 0 if valid, else 1
 */
int checkArguments(int argc, char *argv[])
{
    const char *order = argv[1];
    if (argc != 2)
    {
        printf(IMPROPER_USAGE_MSG);
        return 1;
    }
    else if (strcmp(order, B) != 0 && strcmp(order, M) != 0 && strcmp(order, Q) != 0)
    {
        printf(IMPROPER_USAGE_MSG);
        return 1;
    }
    return 0;
}

/**
 * Check if given pointer to a string contains only digits
 * @param string The given string to check
 * @return 0 if the string contains characters which are not digits, else 1
 */
int checkIfNum(const char* string)
{
    const int string_len = strlen(string);
    for (int i = 0; i < string_len; ++i)
    {
        if(!isdigit(string[i]))
        {
            return 0;
        }
    }
    return 1;
}

/**
 * Check if the given ID is valid, mean contain 10 digits and not start with 0
 * @param string_id The given ID as a string
 * @param lineNum The line number of the input given by the user
 * @return 1 if ID is valid, else 0
 */
int checkID(const char* id, const int lineNum)
{
    if ((checkIfNum(id)) && strlen(id) == 10 && id[0] != '0')
    {
        return 1;
    }
    printf(ID_ERR_MSG);
    printf("in line %d\n", lineNum);
    return 0;
}

/**
 * Check if the given grade is valid, mean contain digits only and value between 0 and 100
 * @param string_grade The given grade as a string
 * @param lineNum The line number of the input given by the user
 * @return 1 if grade is valid, else 0
 */
int checkGrade(const char* string_grade, const int lineNum)
{
    if (checkIfNum(string_grade))
    {
        int grade = (int) strtod(string_grade, NULL);
        if ((grade < 0) || (grade > 100))
        {
            printf(GRADE_ERR_MSG);
            printf("in line %d\n", lineNum);
            return 0;
        }
        return 1;
    }
    printf(GRADE_ERR_MSG);
    printf("in line %d\n", lineNum);
    return 0;
}

/**
 * Check if the given age is valid, mean contain digits only and value between 18 and 120
 * @param string_age The given age as a string
 * @param lineNum The line number of the input given by the user
 * @return 1 if age is valid, else 0
 */
int checkAge(const char* string_age, const int lineNum)
{
    if (checkIfNum(string_age))
    {
        int age = (int) strtod(string_age, NULL);
        if ((age < 18) || (age > 120))
        {
            printf(AGE_ERR_MSG);
            printf("in line %d\n", lineNum);
            return 0;
        }
        return 1;
    }
    printf(AGE_ERR_MSG);
    printf("in line %d\n", lineNum);
    return 0;
}

/**
 * Check if given phrase is valid, mean it contain only alphabetical characters, spaces and '-'
 * @param phrase Pointer to the given phrase
 * @param lineNum The line number of the input given by the user
 * @param type The type of phrase that the function checks, name, country or city
 * @return 1 if the phrase is valid, else 0
 */
int checkPhrase(const char *phrase, const int lineNum, const int type)
{
    unsigned char c;

    while((c = *phrase) && (isalpha(c) || isspace(c) || c == '-'))
    {
        ++phrase;
    }

    if(*phrase != '\0')
    {
        if (type == NAME)
        {
            printf(NAME_ERR_MSG);
        }
        else if (type == COUNTRY)
        {
            printf(COUNTRY_ERR_MSG);
        }
        else if (type == CITY)
        {
            printf(CITY_ERR_MSG);
        }

        printf("in line %d\n", lineNum);
        return 0;
    }
    return 1;
}

/**
 * A function that manage the connection between the program and its variables and the user inputs.
 * Will print to the screen instructions and take care of the inputs by arranging all valid inputs
 * in an array.
 * @param studentArr A pointer to the student struct array
 * @param arrNum A pointer to the number of valid students that were input to the students array
 * @return The ordered students array
 */
Student *manageInput(Student *studentArr, int *arrNum)
{
    int lineNum = 0;

    char input[MAX_LINE_LEN];

    char id[MAX_ID_LEN], name[MAX_PHRASE_LEN], string_grade[MAX_GRADE_LEN], string_age[MAX_AGE_LEN],
    country[MAX_PHRASE_LEN], city[MAX_PHRASE_LEN];

    printf("Enter student info. To exit press q, then enter\n");
    fgets(input, MAX_LINE_LEN, stdin);
    while((strcmp(input, "q\r\n") != 0) && (strcmp(input, "q\n") != 0))
    {
        int parmNum = sscanf(input, "%s\t%[^\t\n]\t%s\t%s\t%s\t%s\t", id, name, string_grade,
                string_age, country, city);
        if (parmNum != MAX_PARM)
        {
            printf(PARM_NUM_ERROR);
            printf("in line %d\n", lineNum);
        }
        else
        {
            if (checkID(id, lineNum) && checkPhrase(name, lineNum, NAME) &&
                checkGrade(string_grade, lineNum) && checkAge(string_age, lineNum) &&
                checkPhrase(country, lineNum, COUNTRY) && checkPhrase(city, lineNum, CITY))
            {
                int grade = (int) strtod(string_grade, NULL);
                int age = (int) strtod(string_age, NULL);
                float score = (float) grade / (float) age;
                Student s;
                strcpy(s.id, id);
                strcpy(s.name, name);
                s.grade = grade;
                s.age = age;
                strcpy(s.country, country);
                strcpy(s.city, city);
                s.score = score;
                studentArr[*arrNum] = s;
                (*arrNum)++;
            }
        }
        lineNum++;
        printf("Enter student info. To exit press q, then enter\n");
        fgets(input, MAX_LINE_LEN, stdin);
    }
    return studentArr;
}

/**
 * This function manage the program flew if the user asked to find the best grade/age scale student
 * from all of its inputs. Will ask the user to input students info and will calculate the best
 * one of them and then print its info to the screen.
 */
void best()
{
    Student studentArr[MAX_ARR_LEN];
    int arrNum = 0;
    manageInput(studentArr, &arrNum);

    if(arrNum != 0)
    {
        int i;
        int bestStu = 0;
        for(i = 1 ; i < arrNum ; i++)
        {
            if(studentArr[i].score > studentArr[bestStu].score)
            {
                bestStu = i;
            }
        }
        printf("best student info is: %s\t%s\t%d\t%d\t%s\t%s\t\n", studentArr[bestStu].id,
               studentArr[bestStu].name, studentArr[bestStu].grade, studentArr[bestStu].age,
               studentArr[bestStu].country, studentArr[bestStu].city);
    }
}

/**
 * A basic merge sorting function that will compare between two students grades and change their
 * position in the students array if needed.
 * @param studentArr An array of students
 * @param low The low index at the array that should be checked
 * @param mid The middle index at the array that separate the checks
 * @param high The high index at the array that should be checked
 */
void mergeSort(Student studentArr[], int low, int mid, int high)
{
    int i = 0, m = 0, k = 0, l = 0;
    Student temp[MAX_ARR_LEN];

    l = low;
    i = low;
    m = mid + 1;

    while ((l <= mid) && (m <= high))
    {
        if (studentArr[l].grade >= studentArr[m].grade)
        {
            temp[i] = studentArr[l];
            l++;
        }
        else
        {
            temp[i] = studentArr[m];
            m++;
        }
        i++;
    }

    if (l > mid)
    {
        for (k = m; k <= high; k++)
        {
            temp[i] = studentArr[k];
            i++;
        }
    }
    else
    {
        for (k = l; k <= mid; k++)
        {
            temp[i] = studentArr[k];
            i++;
        }
    }

    for (k = low; k <= high; k++)
    {
        studentArr[k] = temp[k];
    }
}

/**
 * A recursive function that divide the students array to smaller parts so at the end only two
 * students will be checked at a time.
 * @param studentArr An array of students
 * @param low The low index at the array that should be checked
 * @param high The high index at the array that should be checked
 */
void mergePartition(Student *studentArr, int low, int high)
{
    int mid = 0;

    if (low < high)
    {
        mid = (low + high) / 2;
        mergePartition(studentArr, low, mid);
        mergePartition(studentArr, mid + 1, high);
        mergeSort(studentArr, low, mid, high);
    }
}

/**
 * This function manage the program flew if the user asked to sort students by their grades.
 * Will ask the user to input students info and will use merge sort algorithm to sort the array
 * from the best graded student to the worse graded and then print the info of the students to the
 * screen one by one.
 */
void merge()
{
    Student studentArr[MAX_ARR_LEN];
    int arrNum = 0;
    manageInput(studentArr, &arrNum);

    mergePartition(studentArr, 0, arrNum - 1);

    if(arrNum != 0)
    {
        int i;
        for(i = 0; i < arrNum; i++)
        {
            printf("%s\t%s\t%d\t%d\t%s\t%s\t\n", studentArr[arrNum - i - 1].id,
                   studentArr[arrNum - i - 1].name, studentArr[arrNum - i - 1].grade,
                   studentArr[arrNum - i - 1].age, studentArr[arrNum - i - 1].country,
                   studentArr[arrNum - i - 1].city);
        }
    }
}

/**
 * This function swap between two students infos.
 * @param a A pointer to the first student
 * @param b A pointer to the second student
 */
void swap(Student* a, Student* b)
{
    Student t = *a;
    *a = *b;
    *b = t;
}

/**
 * A function that divide the students array to smaller parts so at the end only two
 * students will be checked at a time in order to find the best pivot for quick sort algorithm.
 * @param studentArr An array of students
 * @param low The low index at the array that should be checked
 * @param high The high index at the array that should be checked
 * @return The best pivot index to do quick sort with
 */
int quickPartition (Student *studentArr, int low, int high)
{
    Student pivot = studentArr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (strcmp(studentArr[j].name, pivot.name) <= 0)
        {
            i++;
            swap(&studentArr[i], &studentArr[j]);
        }
    }
    swap(&studentArr[i + 1], &studentArr[high]);
    return (i + 1);
}

/**
 * A recursive function that divide the students array to smaller parts so at the end only two
 * students will be checked at a time in order to arrange the students array with quick sort
 * algorithm by swap between students.
 * @param studentArr An array of students
 * @param low The low index at the array that should be checked
 * @param high The high index at the array that should be checked
 */
void quickSort(Student *studentArr, int low, int high)
{
    if (low < high)
    {
        int pi = quickPartition(studentArr, low, high);

        quickSort(studentArr, low, pi - 1);
        quickSort(studentArr, pi + 1, high);
    }
}

/**
 * This function manage the program flew if the user asked to sort students by their names.
 * Will ask the user to input students info and will use quick sort algorithm to sort the array
 * in alphabetic order of their names and then print the info of the students to the
 * screen one by one.
 */
void quick()
{
    Student studentArr[MAX_ARR_LEN];
    int arrNum = 0;
    manageInput(studentArr, &arrNum);

    quickSort(studentArr, 0, arrNum - 1);

    if(arrNum != 0)
    {
        int i;
        for(i = 0; i < arrNum; i++)
        {
            printf("%s\t%s\t%d\t%d\t%s\t%s\t\n", studentArr[i].id,
                   studentArr[i].name, studentArr[i].grade, studentArr[i].age,
                   studentArr[i].country, studentArr[i].city);
        }
    }
}

/**
 * This function check the given argument by the user and send to another functions according to
 * what the user want to do with it.
 * @param order The given argument which say what the user would like to do with the program
 */
void manageOrder(const char *order)
{
    if (strcmp(order, B) == 0)
    {
        best();
    }
    else if (strcmp(order, M) == 0)
    {
        merge();
    }
    else if (strcmp(order, Q) == 0)
    {
        quick();
    }
}

/**
 * The main function of the program. First, will send the command line to check if legal and then
 * send to other functions according to the will of the user.
 * @param argc The number of arguments given at the command line by the user
 * @param argv An array of the arguments given by the user
 * @return 1 if the program crashed, else 0
 */
int main(int argc, char *argv[])
{
    if (checkArguments(argc, argv) == 0)
    {
        manageOrder(argv[1]);
    }
    else
    {
        return 1;
    }
    return 0;
}