void update_time(int **time_array, string line) {
  time_array[0] = parse_pair(0, 1, line);
  time_array[1] = parse_pair(3, 4, line);
  time_array[2] = parse_pair(6, 7, line);
}

int parse_pair(int tens, int ones, string line) {
  return atoi(line[tens]) * 10 + atoi(line[ones]);
}

double parse_angle(string line) {
  string phi;
  phi.append(line.begin() + 9, line.end());
  return atof(phi);
}

double check_time(int *current_time, int *file_time) {
  int hours_difference = current_time[0] - file_time[1];
  int minutes_difference = current_time[1] - file_time[1];
  return (hours_difference * 60 - minutes_difference > 15) ? 1 : 0;
}

// Get date from clock and return array
void clock_time(long val, int **current_time){  
  int hours = numberOfHours(val);
  int minutes = numberOfMinutes(val);
  int seconds = numberOfSeconds(val);

  // Update current_time
  current_time[0] = hours;
  current_time[1] = minutes;
  current_time[2] = seconds;
}

