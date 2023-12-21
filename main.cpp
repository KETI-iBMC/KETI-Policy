#include <thread>
#include <iostream>
#include "policy.hpp"
using namespace std;
int main() {
  thread policy_server_thread(run_policy_server);
  thread policy_thread(policy);

  // feedback server connect
  policy_server_thread.join();
  policy_thread.join();

  return 0;
}
