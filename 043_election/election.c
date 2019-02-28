#include "election.h"

#include "ctype.h"
#include "stdio.h"
#include "stdlib.h"

state_t parseLine(const char * line) {
  state_t information;
  const char * temp = line;
  //fill in the name
  char * store = information.name;
  char * stop = store + 64;
  while (*temp != ':' && store != stop) {
    // check format
    if (isalpha(*temp) || *temp == ' ') {
      *store = *temp;
      store++;
      temp++;
    }
    else {
      printf("no name or no ':'\n");
      exit(EXIT_FAILURE);
    }
  }
  if (store != stop) {
    *store = '\0';
  }
  else {
    printf("too long name\n");
    exit(EXIT_FAILURE);
  }
  //fill in the population
  temp++;
  if (isdigit(*temp)) {
    information.population = atoi(temp);
  }
  else {
    printf("no population\n");
    exit(EXIT_FAILURE);
  }
  //fill in the votes
  while (*temp != ':') {
    temp++;
    if (*temp == '\0') {
      printf("no second ':'\n");
      exit(EXIT_FAILURE);
    }
  }
  temp++;
  if (isdigit(*temp)) {
    information.electoralVotes = atoi(temp);
  }
  else {
    printf("no electoral votes\n");
    exit(EXIT_FAILURE);
  }
  return information;
}

unsigned int countElectoralVotes(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  unsigned int votes = 0;
  for (size_t i = 0; i < nStates; i++) {
    if (voteCounts[i] > (stateData[i].population * 0.5)) {
      votes = votes + stateData[i].electoralVotes;
    }
  }
  return votes;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  double percentage;
  for (size_t i = 0; i < nStates; i++) {
    percentage = voteCounts[i] / (double)stateData[i].population;
    if (percentage >= 0.495 && percentage <= 0.505) {
      printf("%s reqires a recount (Candidate A has %.2f%% of the vote)\n",
             stateData[i].name,
             percentage * 100);
    }
  }
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  double max = 0;
  double percentage;
  size_t maxindex = 0;
  for (size_t i = 0; i < nStates; i++) {
    percentage = voteCounts[i] / (double)stateData[i].population;
    if (percentage > max) {
      max = percentage;
      maxindex = i;
    }
  }
  printf("Candidate A won %s with %.2f%% of the vote\n", stateData[maxindex].name, max * 100);
}
