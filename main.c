#include <stdio.h>
#define MAX_ENTRY 100

int indx = 0;
char course_name[60] = "CSE122CSE123CSE124MAT111MAT121ENG113ENG123PHY113PHY114GED121";
int course_credit[10] = {3, 1, 1, 3, 3, 3, 3, 2, 1, 3};
struct student_information
{
    int year, dptmt, roll, waiver;
    char name[50];
    float ssc, hsc, cgpa, mark[10];

} students[MAX_ENTRY];

void calculateGPA(int indx)
{
    double total = 0;
    printf("Enter 10 course result\n");
    printf("No. Course_Code Mark\n");
    for (int i = 0; i < 10; i++)
    {
    jump:
        printf("%d. ", i + 1);
        for (int j = i * 6; j < (i * 6) + 6; j++)
        {
            printf("%c", course_name[j]);
        }
        printf(" :");
        scanf("%f", &students[indx].mark[i]);
        float gpa, mark;
        mark = students[indx].mark[i];
        if (mark > 100)
        {
            printf("Error! Enter Correct Mark (0-100)\n");
            goto jump;
        }
        if (mark >= 80)
            gpa = 4.0;
        else if (mark >= 75)
            gpa = 3.75;
        else if (mark >= 70)
            gpa = 3.5;
        else if (mark >= 65)
            gpa = 3.25;
        else if (mark >= 60)
            gpa = 3.0;
        else if (mark >= 55)
            gpa = 2.75;
        else if (mark >= 50)
            gpa = 2.5;
        else if (mark >= 45)
            gpa = 2.25;
        else if (mark >= 40)
            gpa = 2.0;
        else
            gpa = 0.0;
        total += (gpa * course_credit[i]);
    }
    students[indx].cgpa = (float)(total / 23);
}

void setAcademicResult(int indx)
{
    char ssc, hsc;
    printf("Enter Academic Result\n");
    printf("SSC: ");
    scanf("%f", &students[indx].ssc);
    if (students[indx].ssc == 5.00)
    {
        printf("Golden A+(y/n):");
        setbuf(stdin, NULL);
        scanf("%c", &ssc);
    }
    printf("HSC: ");
    scanf("%f", &students[indx].hsc);
    if (students[indx].hsc == 5.00)
    {
        printf("Golden A+(y/n):");
        setbuf(stdin, NULL);
        scanf("%c", &hsc);
    }
    if (ssc == 'y' && hsc == 'y')
    {
        students[indx].waiver = 75;
    }
    else if (ssc == 'n' && hsc == 'y')
    {
        students[indx].waiver = 50;
    }
    else if (ssc == 'n' && hsc == 'n')
    {
        students[indx].waiver = 35;
    }
    else if (students[indx].hsc == 5.00)
    {
        students[indx].waiver = 25;
    }
    else if (students[indx].hsc < 5.00 && students[indx].hsc >= 4.9)
    {
        students[indx].waiver = 20;
    }
    else if (students[indx].hsc < 4.9 && students[indx].hsc >= 4.75)
    {
        students[indx].waiver = 20;
    }
    else
    {
        students[indx].waiver = 20;
    }
}

void calculateWaiver(int indx)
{
    float waiver = students[indx].waiver, cgpa = students[indx].cgpa;
    if (waiver == 75)
    {
        if (cgpa < 3.5)
        {
            students[indx].waiver = 0;
        }
    }
    else if (waiver == 50)
    {
        if (cgpa < 3.5)
        {
            students[indx].waiver = 0;
        }
    }
    else if (waiver == 35)
    {
        if (cgpa < 3.25)
        {
            students[indx].waiver = 0;
        }
    }
    else if (waiver <= 25 && waiver >= 10)
    {
        if (cgpa < 3.0)
        {
            students[indx].waiver = 0;
        }
    }
}

void addStudent()
{
    char str;

    printf("\n");
    printf("Enter Name: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", students[indx].name);
    printf("Enter ID(***-**-****): ");
    scanf("%d-%d-%d", &students[indx].year, &students[indx].dptmt, &students[indx].roll);
    setAcademicResult(indx);
    calculateGPA(indx);
    calculateWaiver(indx);
    indx++;
    printf("Do you want to add more? (y/n) :");
    setbuf(stdin, NULL);
    scanf("%c", &str);
    if (str == 'y')
        addStudent();
}

void sortStudents()
{
    printf("Sorting...\n");
    for (int i = 0; i < indx; i++)
    {
        struct student_information temp;
        for (int j = 0; j < indx; j++)
        {
            if (students[i].cgpa > students[j].cgpa)
            {
                temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    printf("Sorted!\n\n");
}

void showStudent()
{
    int year, dptmt, roll;
    printf("\nEnter ID(***-**-****): ");
    scanf("%d-%d-%d", &year, &dptmt, &roll);

    for (int i = 0; i < indx; i++)
    {
        if (year == students[i].year && dptmt == students[i].dptmt && roll == students[i].roll)
        {
            printf("\nName: %s\n", students[i].name);
            printf("ID: %d-%d-%d\n", students[i].year, students[i].dptmt, students[i].roll);
            printf("CGPA: %0.2f\n", students[i].cgpa);
            printf("Waiver: %d%%\n\n", students[i].waiver);
            for (int i = 0; i < 10; i++)
            {
                for (int j = i * 6; j < (i * 6) + 6; j++)
                {
                    printf("%c", course_name[j]);
                }
                printf(" :");
                printf("%.2f\n", students[i].mark[i]);
            }
        }
    }
}

void showStudents()
{

    for (int i = 0; i < indx; i++)
    {
        printf("Name: %s\n", students[i].name);
        printf("ID: %d-%d-%d\n", students[i].year, students[i].dptmt, students[i].roll);
        printf("CGPA: %0.2f\n\n", students[i].cgpa);
    }
}

void updateName(int year, int dptmt, int roll)
{
    for (int i = 0; i < indx; i++)
    {
        if (year == students[i].year && dptmt == students[i].dptmt && roll == students[i].roll)
        {
            printf("Enter Name: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]s", students[i].name);
            printf("Update!\n");
        }
    }
}

void updateID(int year, int dptmt, int roll)
{
    for (int i = 0; i < indx; i++)
    {
        if (year == students[i].year && dptmt == students[i].dptmt && roll == students[i].roll)
        {
            printf("Enter ID(***-**-****): ");
            scanf("%d-%d-%d", &students[i].year, &students[i].dptmt, &students[i].roll);
        }
    }
}

void updateResult(int year, int dptmt, int roll)
{
    for (int i = 0; i < indx; i++)
    {
        if (year == students[i].year && dptmt == students[i].dptmt && roll == students[i].roll)
        {
            setAcademicResult(i);
        }
    }
}

void display_update()
{
    printf("\nEnter 1 for Update Name\n");
    printf("Enter 2 for Upadte ID\n");
    printf("Enter 3 for Upadte Result\n");
    printf("Enter 0 for exit\n");
}

void updateStudent()
{
    int ch;
    int year, dptmt, roll;
    while (1)
    {
        display_update();
        printf("Enter your choice: ");
        setbuf(stdin, NULL);
        scanf("%d", &ch);
        if (ch == 1)
        {
            printf("\nEnter ID(***-**-****): ");
            scanf("%d-%d-%d", &year, &dptmt, &roll);
            setbuf(stdin, NULL);
            updateName(year, dptmt, roll);
        }
        else if (ch == 2)
        {
            printf("\nEnter ID(***-**-****): ");
            scanf("%d-%d-%d", &year, &dptmt, &roll);
            updateID(year, dptmt, roll);
        }
        else if (ch == 3)
        {
            printf("\nEnter ID(***-**-****): ");
            scanf("%d-%d-%d", &year, &dptmt, &roll);
            updateResult(year, dptmt, roll);
        }
        else if (ch == 0)
        {
            break;
        }
    }
}

void display()
{
    printf("\n\tWaiver Calculate System\n");
    printf("Enter 1 for Add Student\n");
    printf("Enter 2 for Sort Students\n");
    printf("Enter 3 for Display Students\n");
    printf("Enter 4 for Display Indivisual Detail\n");
    printf("Enter 5 for Update Indivisual Detail\n");
    printf("Enter 0 for Quit the program\n");
}

int main()
{
    int ch;
    while (1)
    {
        display();
        printf("Enter your choice: ");
        scanf("%d", &ch);
        if (ch == 1)
        {
            addStudent();
        }
        else if (ch == 2)
        {
            sortStudents();
        }
        else if (ch == 3)
        {
            showStudents();
        }
        else if (ch == 4)
        {
            showStudent();
        }
        else if (ch == 5)
        {
            updateStudent();
        }
        else if (ch == 0)
        {
            break;
        }
    }
}