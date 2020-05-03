#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];




// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

typedef struct
{
    int candidateNum;
    int wins;
}
store;
// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count=0;
int candidate_count;
// count number of locked edges in each row
int check[MAX];

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

   // pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0 )
        {
            ranks[rank] = i;
            return true;  // maybe true.ranks[i]
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count-1; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
             if (ranks[i]==ranks[j]){
                 preferences[i][j]=0;
                 continue;
             }
             preferences[ranks[i]][ranks[j]]++;
        }

    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
     int index = 0;
     for (int i = 0; i < candidate_count-1; i++)
     {
         for (int j = i + 1; j < candidate_count; j++)
         {
            if (preferences[i][j] == preferences[j][i])
            {
                continue;
            }
            if (preferences[i][j] > preferences[j][i])
            {
            pairs[index].winner = i;
            pairs[index].loser = j;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[index].winner = j;
                pairs[index].loser = i;
            }
            pair_count++;
            index++;
         }
    
         }
           return;

     }
  /*   for(int i = 0; i < candidate_count-1; i++)
     {
        if (preferences[0][i+1] > preferences[i+1][0])
        {
            pairs[i].winner = 0;
            pairs[i].loser = i+1;
        }
            else if (preferences[0][i + 1] < preferences[i + 1][0])
            {
                pairs[i].winner = i+1;
                pairs[i].loser = 0;
            }
            pair_count++;
     }*/

   /* for(int i = 0; i < 2; i++)
    {
        for (int j = i; j < 3; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[i].winner = i;
                pairs[i].loser = j;
            }
            else if (preferences[i][j + 1] < preferences[j + 1][i])
            {
                pairs[i].winner = j;
                pairs[i].loser = i;
            }
            pair_count++;
            if (preferences[i][j] == preferences[j][i])
            {
                pair_count--;
            }

        }
        printf("pair's winner is %i", pairs[i].winner);

    }*/



void swap(store *a, store *b)
{
    store tmp = *a;
    *a = *b;
    *b = tmp;
}

void swap2(pair *a, pair *b)
{
    pair tmp = *a;
    *a = *b;
    *b = tmp;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count-1; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j+1].winner][pairs[j+1].loser]) 
            {
                swap2(&pairs[j], &pairs[j+1]);
            }
        }
    }
 /*   store numOfWins[pair_count];
    int index =0;
    int test =0; 
    for (int i = 0; i < pair_count; i++)
    {
        index=pairs[i].winner;
        printf("index is %i\n", index);
        numOfWins[index].wins+=1;
        numOfWins[i].candidateNum=i;
        
        printf("num of wins: %i\n", numOfWins[i].wins);
    }
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count-i-1; j++)
        {
            if (numOfWins[j].wins < numOfWins[j + 1].wins)
            {
                printf("candidate number: %i \n candidate wins: %i", numOfWins[j].candidateNum, numOfWins[j].wins);
                swap(&numOfWins[j], &numOfWins[j+1]);
                printf("candidate number: %i \n candidate wins: %i", numOfWins[j].candidateNum, numOfWins[j].wins);
            }
        }
    }
    for (int i = 0; i < pair_count; i++)
    {
        pairs[i].winner=numOfWins[i].candidateNum;
    }*/

/*    for (int i = 0; i < pair_count; i++)
    {
        j=i;
        if (numOfWins[i].candidateNum != pairs[i].winner)
        {
            while (pairs[j].winner != numOfWins[i].candidateNum && j<pair_count)
            {
                j++;
            }
            swap2(&pairs[i], &pairs[j]);
        }
        if (numOfWins[i].wins==0){
            pairs[i].winner=pairs[i].loser;
        }
    }*/

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    bool loop = true;
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser]=true;
        check[pairs[i].winner]++;
        for (int j = 0; j < candidate_count; j++)
        {
            if (pairs[i].winner == pairs[j].loser)
            {
                if (locked[pairs[j].winner][pairs[j].loser]==true && locked[pairs[i].loser][pairs[j].winner] == true)
                {
                    locked[pairs[i].winner][pairs[i].loser] = false;
                }
                
            }
        }
       /* for (int j =0; j < candidate_count-1; j++)
        {
            if (check[j] == check[j+1])
            {
                loop = true;
            }
            else if (check[j] != check[j+1])
            {
                loop = false; 
                break;
            }
        }
        if (loop)
        {
            locked[pairs[i].winner][pairs[i].loser]=false;
        }*/
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    
    int max = 0; 
    for (int i = 0; i < candidate_count-1; i++)
    {
        if(check[i]>check[i+1])
        {
            max = i;
        }
        else 
        {
            max = i + 1;
        }
    }
    printf("%s", candidates[max]);
/* printf("pair count is %i\n", pair_count);
    for (int i=0; i< pair_count; i++){
        printf("%i\n", pairs[i].winner);
    }*/
  //  printf("%s", candidates[pairs[0].winner]);
    return;
}

