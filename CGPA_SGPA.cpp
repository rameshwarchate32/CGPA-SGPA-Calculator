#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class SGPA_CAL
{
public:
    int num_of_sub, external_sub, n, num_of_semesters;
    char ext_ch;
    string sub_name[100], p_sub_name[100], e_sub_name[100];
    int marks[100], pmarks[100], e_marks[100];
    float totalCredit = 0.0, TotalGradePoint = 0.0, credit, grade, gp, SGPA, CGPA;
    float P_totalCredit = 0.0, P_TotalGradePoint = 0.0, E_totalCredit = 0.0, E_TotalGradePoint = 0.0, All_credit = 0.0, All_grades = 0.0;

public:
    // Function to input details of subjects
    void input();

    // Function to display subjects and their marks
    void display();

    // Function to assign credit based on marks
    float Credit(float marks);

    // Function to assign grade based on marks
    float Grade(float marks);

    // Function to calculate and set total credit
    void setCredit();

    // Function to calculate and set total grade points
    void setGradePoint();

    // Function to calculate and display SGPA
    float CalCulateSGPA();

    void External_sub();
    // Function to calculate and display CGPA
    void CalCulateCGPA();
    // calculate and display practical
    void calPractical();

    float calPracticalCredit();
    // Function to display final output including details of each subject, total credit, and total grade points
    void display_Final_output();
};

// Function to input details of subjects
void SGPA_CAL::input()
{
    cout << "How many number of subject subjects: ";
    cin >> num_of_sub;
    for (int i = 0; i < num_of_sub; i++)
    {
        cout << "Enter subject name: ";
        cin >> sub_name[i];
        cout << "Enter marks of the  subject " << sub_name[i] << ": ";
        cin >> marks[i];
    }
}

void SGPA_CAL ::External_sub()
{
    cout << "Do you have any external theory subjects? (y/n): ";
    cin >> ext_ch;
    if (ext_ch == 'Y' || ext_ch == 'y')
    {
        cout << "How many external subjects : ";
        cin >> external_sub;
        for (int i = 0; i < external_sub; i++)
        {
            cout << "Enter subject name: ";
            cin >> e_sub_name[i];
            cout << "Enter marks of the subject " << p_sub_name[i] << ": ";
            cin >> e_marks[i];
            e_marks[i] *= 2; // multiply by 2 because we need to convert the marks into outof 100
        }
        cout << "Marks : " << endl;
        cout << " Subjects Names and Marks Of : " << num_of_sub << " Subjects " << endl;
        for (int i = 0; i < num_of_sub; i++)
        {
            cout << sub_name[i] << ": " << marks[i] << "\t";
        }
        cout << endl;
        for (int i = 0; i < external_sub; i++)
        {
            E_totalCredit += 2; //  adding 2 credits for each subject
        }
        for (int i = 0; i < external_sub; i++)
        {
            E_TotalGradePoint += 2 * Grade(e_marks[i]); // recursivly add 2 credits for each and grade points stored in E_TotalGradePoint
        }
    }
    else
    {
        return; // if conditions false then directly return without any operations
    }
}
// Function to display subjects and their marks
void SGPA_CAL::display()
{
    cout << " Subjects Names and Marks Of : " << num_of_sub << " Subjects " << endl;
    for (int i = 0; i < num_of_sub; i++)
    {
        cout << sub_name[i] << ": " << marks[i] << "\t";
    }
    cout << endl;
}

// Function to assign credit based on marks
float SGPA_CAL::Credit(float marks)
{
    if (marks <= 100 && marks >= 36)
    {
        return 4.0; // returns 4 credit points if pass else return 0 credit points
    }
    else
    {
        return 0.0; // No credit for marks below 40
    }
}

// Function to assign grade based on marks
float SGPA_CAL::Grade(float marks)
{
    if (marks <= 100 && marks >= 90)
    {
        return 10.0;
    }
    else if (marks <= 90 && marks >= 80)
    {
        return 9.0;
    }
    else if (marks <= 80 && marks >= 70)
    {
        return 8.0;
    }
    else if (marks <= 70 && marks >= 60)
    {
        return 7.0;
    }
    else if (marks <= 60 && marks >= 50)
    {
        return 6.0;
    }
    else if (marks <= 50 && marks >= 40)
    {
        return 5.0;
    }
    else
    {
        return 0.0; // No grade for marks below 40
    }
}

// Function to calculate and set total credit
void SGPA_CAL::setCredit()
{
    for (int i = 0; i < num_of_sub; i++)
    {
        totalCredit += Credit(marks[i]); // sum of total thoery credit points
    }
}

void SGPA_CAL::calPractical()
{

    cout << "Enter the marks of practical out of 50  : " << endl;
    cout << "number of  practical subject : " << endl;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter subject name: ";
        cin >> p_sub_name[i];
        cout << "Enter marks of the subject " << p_sub_name[i] << ": ";
        cin >> pmarks[i];
        pmarks[i] *= 2;
    }
    for (int i = 0; i < n; i++)
    {
        P_totalCredit += calPracticalCredit();
    }
    for (int i = 0; i < n; i++)
    {
        P_TotalGradePoint += calPracticalCredit() * Grade(pmarks[i]);
    }
}
// Function to calculate and set total grade points
void SGPA_CAL::setGradePoint()
{
    for (int i = 0; i < num_of_sub; i++)
    {
        float credit = Credit(marks[i]);
        float grade = Grade(marks[i]);
        if (credit == 0 || grade == 0)
        {
            TotalGradePoint = 0.0;
            cout << "Total Grade point of theory : " << TotalGradePoint << endl;
            return;
        }
        TotalGradePoint += credit * grade; // Calculate total grade point
    }
}

// Function to calculate and display SGPA
// Function to calculate SGPA
float SGPA_CAL::CalCulateSGPA()
{
    if (totalCredit == 0.0)
    {
        return 0.0; // Avoid division by zero
    }
    if (ext_ch == 'Y' || ext_ch == 'y')
    {
        All_credit = totalCredit + P_totalCredit + E_totalCredit;
        All_grades = TotalGradePoint + P_TotalGradePoint + E_TotalGradePoint;

        SGPA = (TotalGradePoint + P_TotalGradePoint + E_TotalGradePoint) / All_credit;
        return SGPA;
    }
    else
    {
        All_credit = totalCredit + P_totalCredit;
        All_grades = TotalGradePoint + P_TotalGradePoint;

        SGPA = (TotalGradePoint + P_TotalGradePoint) / All_credit;
        return SGPA;
    }
}

float SGPA_CAL::calPracticalCredit()
{
    if (n == 4)
    {
        return 1.5;
    }
    else if (n <= 3 || n == 5)
    {
        return 2.0;
    }
    else if (n <= 2)
    {
        return 3.0;
    }
    else
    {
        return 0.0;
    }
}
// Function to calculate CGPA
void SGPA_CAL::CalCulateCGPA()
{
    cout << "Enter the number of semesters: ";
    cin >> num_of_semesters;

    SGPA_CAL semesterCalculators[num_of_semesters];

    for (int i = 0; i < num_of_semesters; i++)
    {
        cout << "Enter details for Semester " << i + 1 << ":" << endl;
        semesterCalculators[i].input();        // add this line to include theory subjects`
        semesterCalculators[i].External_sub(); // Add this line to include external subjects
        semesterCalculators[i].calPractical(); // Add this line to include practical subjects
    }

    float totalCreditCGPA = 0.0;
    float totalGradePointCGPA = 0.0;

    for (int i = 0; i < num_of_semesters; i++)
    {
        semesterCalculators[i].setCredit();
        semesterCalculators[i].setGradePoint();

        // Check if the student failed in any subject in the semester
        for (int j = 0; j < semesterCalculators[i].num_of_sub; j++)
        {
            if (semesterCalculators[i].marks[j] < 35)
            {
                cout << "Student failed in Semester " << i + 1 << "." << endl;
                cout << "CGPA: 0.0" << endl;
                return;
            }
        }

        totalCreditCGPA += semesterCalculators[i].totalCredit + semesterCalculators[i].P_totalCredit + semesterCalculators[i].E_totalCredit;
        totalGradePointCGPA += semesterCalculators[i].TotalGradePoint + semesterCalculators[i].P_TotalGradePoint + semesterCalculators[i].E_TotalGradePoint;
    }

    if (totalCreditCGPA == 0.0)
    {
        CGPA = 0.0;
    }
    else
    {
        CGPA = totalGradePointCGPA / totalCreditCGPA;
    }
    for (int i = 0; i < num_of_semesters; i++)
    {
        cout << "Details of Semester " << i + 1 << ":" << endl;
        semesterCalculators[i].display_Final_output();
    }
    cout << "CGPA: " << CGPA << endl;
}

void SGPA_CAL::display_Final_output()
{
    cout << "------------------------------------------------------------------------------" << endl;
    cout << "|" << setw(20) << "Subject" << setw(10) << "Marks" << setw(10) << "Credit" << setw(10) << "Grade" << setw(15) << "Total Grade Point" << setw(10) << "|" << endl;

    for (int i = 0; i < num_of_sub; i++)
    {
        cout << "|" << setw(20) << sub_name[i] << setw(10) << marks[i] << setw(10) << Credit(marks[i]) << setw(10) << Grade(marks[i]) << setw(15) << Credit(marks[i]) * Grade(marks[i]) << setw(12) << "|" << endl;
    }

    if (ext_ch == 'Y' || ext_ch == 'y')
    {
        for (int i = 0; i < external_sub; i++)
        {
            cout << "|" << setw(20) << e_sub_name[i] << setw(10) << e_marks[i] << setw(10) << "2" << setw(10) << Grade(e_marks[i]) << setw(15) << 2 * Grade(e_marks[i]) << setw(12) << "|" << endl;
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << "|" << setw(20) << p_sub_name[i] << setw(10) << pmarks[i] / 2 << setw(10) << calPracticalCredit() << setw(10) << Grade(pmarks[i]) << setw(15) << calPracticalCredit() * Grade(pmarks[i]) << setw(12) << "|" << endl;
    }

    cout << "------------------------------------------------------------------------------" << endl;
    cout << "|" << setw(20) << "Total Credit: " << totalCredit + P_totalCredit + E_totalCredit << "\tTotal Grade Points: " << TotalGradePoint + P_TotalGradePoint + E_TotalGradePoint << setw(32) << "|" << endl;
    cout << "|" << setw(20) << "SGPA: " << CalCulateSGPA() << setw(56) << "|" << endl;
    cout << "------------------------------------------------------------------------------" << endl;
}

int main()
{
    int ch;
    SGPA_CAL sgpaCalculator;
    SGPA_CAL CGPACalculator;
    cout << "Enter your choice: \n1. SGPA CALCULATOR \n2. CGPA CALCULATOR \n";
    cin >> ch;

    switch (ch)
    {
    case 1:
        sgpaCalculator.input();
        sgpaCalculator.display();
        sgpaCalculator.External_sub();
        sgpaCalculator.calPractical();
        sgpaCalculator.setCredit();
        sgpaCalculator.setGradePoint();
        sgpaCalculator.CalCulateSGPA();
        sgpaCalculator.display_Final_output();
        break;

    case 2:
        CGPACalculator.CalCulateCGPA();
        break;

    default:
        cout << "Invalid Choice";
        break;
    }

    return 0;
}
