#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::vector<std::string> input_dates, input_times;
  std::vector<int> input_vals;
  std::string input_date, input_time;
  int input_val;

  while (std::cin >> input_date >> input_time >> input_val) {
    input_dates.push_back(input_date);
    input_times.push_back(input_time);
    input_vals.push_back(input_val);
  }

  int count = input_vals.size();
  std::cout << "Total count: " << count << "\n";

  if (count == 0) {
    return 0;
  }

  auto max = std::max_element(input_vals.begin(), input_vals.end());
  int max_index = std::distance(input_vals.begin(), max);
  std::cout << "Maximum input value: " << *max << " on " << input_dates[max_index] << " at "
            << input_times[max_index] << "\n";

  auto min = std::min_element(input_vals.begin(), input_vals.end());
  int min_index = std::distance(input_vals.begin(), min);
  std::cout << "Minimum input value: " << *min << " on " << input_dates[min_index] << " at "
            << input_times[min_index] << "\n";

  double sum = 0;
  for (int i : input_vals) {
    sum += i;
  }
  std::cout << "Mean: " << (sum / count) << "\n";

  std::sort(input_vals.begin(), input_vals.end());
  double median = (count % 2 == 0) ? (input_vals[count / 2 - 1] + input_vals[count / 2]) / 2.0
                                   : input_vals[count / 2];
  std::cout << "Median: " << median << "\n";

  int mode = input_vals[0], max_freq = 0, current_freq = 0, current_val = input_vals[0];
  for (size_t i = 0; i < input_vals.size(); ++i) {
    if (i == 0 || input_vals[i] == input_vals[i - 1]) {
      ++current_freq;
    } else {
      if (current_freq > max_freq) {
        max_freq = current_freq;
        mode = current_val;
      }
      current_val = input_vals[i];
      current_freq = 1;
    }
  }
  if (current_freq > max_freq) {
    max_freq = current_freq;
    mode = current_val;
  }

  std::cout << "Mode: " << mode << " (" << max_freq << " instances)\n";

  return 0;
}
