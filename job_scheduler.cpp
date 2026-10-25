#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Job
{
    string id;
    string name;
    int deadline;
    int profit;
    int priority;
    bool scheduled;
};

void sortJobs(Job jobs[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (jobs[j].profit < jobs[j + 1].profit ||
                (jobs[j].profit == jobs[j + 1].profit &&
                 jobs[j].priority < jobs[j + 1].priority))
            {
                Job temp = jobs[j];
                jobs[j] = jobs[j + 1];
                jobs[j + 1] = temp;
            }
        }
    }
}

void displayJobs(Job jobs[], int n)
{
    cout << "\nAvailable Jobs\n\n";

    cout << left
         << setw(8) << "ID"
         << setw(18) << "Name"
         << setw(12) << "Deadline"
         << setw(12) << "Profit"
         << setw(10) << "Priority" << endl;

    cout << "--------------------------------------------------\n";

    for (int i = 0; i < n; i++)
    {
        cout << left
             << setw(8) << jobs[i].id
             << setw(18) << jobs[i].name
             << setw(12) << jobs[i].deadline
             << setw(12) << jobs[i].profit
             << setw(10) << jobs[i].priority
             << endl;
    }
}

void scheduleJobs(Job jobs[], int n)
{
    sortJobs(jobs, n);

    int maxDeadline = 0;

    for (int i = 0; i < n; i++)
    {
        jobs[i].scheduled = false;

        if (jobs[i].deadline > maxDeadline)
            maxDeadline = jobs[i].deadline;
    }

    string schedule[100];

    for (int i = 0; i < 100; i++)
        schedule[i] = "";

    int totalProfit = 0;
    int scheduledCount = 0;

    for (int i = 0; i < n; i++)
    {
        for (int slot = jobs[i].deadline; slot >= 1; slot--)
        {
            if (schedule[slot - 1] == "")
            {
                schedule[slot - 1] = jobs[i].id;
                jobs[i].scheduled = true;
                totalProfit += jobs[i].profit;
                scheduledCount++;
                break;
            }
        }
    }

    cout << "\nSmart Job Schedule\n\n";

    for (int i = 0; i < maxDeadline; i++)
    {
        cout << "Time Slot " << i + 1 << " : ";

        if (schedule[i] == "")
            cout << "Idle";
        else
            cout << schedule[i];

        cout << endl;
    }

    double utilization = ((double)scheduledCount / maxDeadline) * 100;

    cout << "\nTotal Jobs       : " << n << endl;
    cout << "Scheduled Jobs   : " << scheduledCount << endl;
    cout << "Unscheduled Jobs : " << n - scheduledCount << endl;
    cout << "Total Profit     : " << totalProfit << endl;
    cout << fixed << setprecision(2);
    cout << "Utilization      : " << utilization << "%\n";

    cout << "\nUnscheduled Jobs\n\n";

    bool found = false;

    for (int i = 0; i < n; i++)
    {
        if (!jobs[i].scheduled)
        {
            cout << jobs[i].id << " - "
                 << jobs[i].name
                 << " | Profit: " << jobs[i].profit << endl;

            found = true;
        }
    }

    if (!found)
        cout << "All jobs were scheduled successfully.\n";
}

int main()
{
    int n;

    cout << "Smart Job Scheduling System\n";
    cout << "Using Greedy Algorithm\n\n";

    cout << "Enter number of jobs: ";
    cin >> n;

    if (n <= 0 || n > 20)
    {
        cout << "Invalid number of jobs.\n";
        return 0;
    }

    Job jobs[20];

    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter details for Job " << i + 1 << "\n";

        cout << "Job ID: ";
        cin >> jobs[i].id;

        cout << "Job Name: ";
        cin >> jobs[i].name;

        cout << "Deadline: ";
        cin >> jobs[i].deadline;

        cout << "Profit: ";
        cin >> jobs[i].profit;

        cout << "Priority (1-5): ";
        cin >> jobs[i].priority;
    }

    int choice;

    do
    {
        cout << "\nMenu\n";
        cout << "1. Display Jobs\n";
        cout << "2. Generate Schedule\n";
        cout << "3. Exit\n";

        cout << "\nEnter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            displayJobs(jobs, n);
        }
        else if (choice == 2)
        {
            scheduleJobs(jobs, n);
        }
        else if (choice == 3)
        {
            cout << "\nProgram ended.\n";
        }
        else
        {
            cout << "\nInvalid choice.\n";
        }

    } while (choice != 3);

    return 0;
}
