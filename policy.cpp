#include "policy.hpp"

#include <dbus-c++-1/dbus-c++/interface.h>
#include <dbus-c++-1/dbus-c++/message.h>

#include <string>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

using namespace std;
#include <limits.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <thread>

#include "/home/keti/KETI_BMC/KETI-APP/hj/app/include/rapidjson/include/rapidjson/document.h"
#include "/home/keti/KETI_BMC/KETI-APP/hj/app/include/rapidjson/include/rapidjson/stringbuffer.h"
#include "/home/keti/KETI_BMC/KETI-APP/hj/app/include/rapidjson/include/rapidjson/writer.h"

DBus::BusDispatcher dispatcher;

Policy_Adaptor::Policy_Adaptor(DBus::Connection &connection)
    : DBus::ObjectAdaptor(connection, POLICY_SERVER_PATH) {}
int32_t Policy_Adaptor::policy_feedback() {
  cout << "feedback에서 온 요청 수행" << endl;
  return 0;
}
int32_t Policy_Adaptor::policy_ibmc() {
  cout << "ibmc에서 온 요청 수행" << endl;
  return 0;
}
int32_t Policy_Adaptor::policy_monitor() {
  cout << "monitor에서 온 요청 수행" << endl;
  return 0;
}
int32_t Policy_Adaptor::policy_energy() {
  cout << "energy에서 온 요청 수행" << endl;
  return 0;
}
int32_t Policy_Adaptor::policy_ssp() {
  cout << "ssp에서 온 요청 수행" << endl;
  return 0;
}
//-----------------------------Policy_Adaptor클래스끝-----------------------------
Ibmc_Proxy::Ibmc_Proxy(DBus::Connection &connection, const char *path,
                       const char *name)
    : DBus::ObjectProxy(connection, path, name) {}
//-----------------------------Ibmc_Proxy클래스끝-----------------------------
Feedback_Proxy::Feedback_Proxy(DBus::Connection &connection, const char *path,
                       const char *name)
    : DBus::ObjectProxy(connection, path, name) {}
//-----------------------------Feedback_Proxy클래스끝-----------------------------
Monitor_Proxy::Monitor_Proxy(DBus::Connection &connection, const char *path,
                       const char *name)
    : DBus::ObjectProxy(connection, path, name) {}
//-----------------------------Monitor_Proxy클래스끝-----------------------------
Energy_Proxy::Energy_Proxy(DBus::Connection &connection, const char *path,
                       const char *name)
    : DBus::ObjectProxy(connection, path, name) {}
//-----------------------------Energy_Proxy클래스끝-----------------------------
Ssp_Proxy::Ssp_Proxy(DBus::Connection &connection, const char *path,
                       const char *name)
    : DBus::ObjectProxy(connection, path, name) {}
//-----------------------------Ssp_Proxy클래스끝-----------------------------
void connect_to_ibmc_server() {
  DBus::BusDispatcher dispatcher;
  DBus::default_dispatcher = &dispatcher;
  DBus::Connection conn_n = DBus::Connection::SystemBus();
  Ibmc_Proxy dbus_adap_test =
      Ibmc_Proxy(conn_n, IBMC_SERVER_PATH, IBMC_SERVER_NAME);
  cout << "ibmc 서버와 연결 완료" << endl;
  dbus_adap_test.ibmc_policy();
}
void connect_to_feedback_server() {
  DBus::BusDispatcher dispatcher;
  DBus::default_dispatcher = &dispatcher;
  DBus::Connection conn_n = DBus::Connection::SystemBus();
  Feedback_Proxy dbus_adap_test =
      Feedback_Proxy(conn_n, FEEDBACK_SERVER_PATH, FEEDBACK_SERVER_NAME);
  cout << "feedback 서버와 연결 완료" << endl;
  dbus_adap_test.feedback_policy();
}
void connect_to_monitor_server() {
  DBus::BusDispatcher dispatcher;
  DBus::default_dispatcher = &dispatcher;
  DBus::Connection conn_n = DBus::Connection::SystemBus();
  Monitor_Proxy dbus_adap_test =
      Monitor_Proxy(conn_n, MONITOR_SERVER_PATH, MONITOR_SERVER_NAME);
  cout << "monitor 서버와 연결 완료" << endl;
  dbus_adap_test.monitor_policy();
}
void connect_to_energy_server() {
  DBus::BusDispatcher dispatcher;
  DBus::default_dispatcher = &dispatcher;
  DBus::Connection conn_n = DBus::Connection::SystemBus();
  Energy_Proxy dbus_adap_test =
      Energy_Proxy(conn_n, ENERGY_SERVER_PATH, ENERGY_SERVER_NAME);
  cout << "energy 서버와 연결 완료" << endl;
  dbus_adap_test.energy_policy();
}
void connect_to_ssp_server() {
  DBus::BusDispatcher dispatcher;
  DBus::default_dispatcher = &dispatcher;
  DBus::Connection conn_n = DBus::Connection::SystemBus();
  Ssp_Proxy dbus_adap_test =
      Ssp_Proxy(conn_n, SSP_SERVER_PATH, SSP_SERVER_NAME);
  cout << "ssp 서버와 연결 완료" << endl;
  dbus_adap_test.ssp_policy();
}
void initialize_file(){
  ofstream file(POLICY_FILE_PATH);
  if (!file.is_open()) {
    std::cerr << "Failed to create file: " << POLICY_FILE_PATH << std::endl;
    return;
  }
  file << DEFAULT_POLICY_CONTENT;
  file.close();
}


void read_file() {
  ifstream file(POLICY_FILE_PATH);

  if (!file.is_open()) {
    cerr << "Failed to open file: " << POLICY_FILE_PATH << endl;
    cout << "파일 초기화";
    initialize_file();
    
  }
  string line;
  while (getline(file, line)) {
    cout << line << endl;
  }
  file.close();
}

void modify_policy(const std::string &policy_name, const std::string &status) {
  // 파일 열기
  ifstream inputFile(POLICY_FILE_PATH);
  if (!inputFile.is_open()) {
    cerr << "Failed to open file: " << POLICY_FILE_PATH << endl;
  }

  // 파일 내용 읽기
  string jsonContent((istreambuf_iterator<char>(inputFile)),
                     istreambuf_iterator<char>());

  // JSON 파싱
  rapidjson::Document document;
  document.Parse(jsonContent.c_str());
  if (document.HasParseError()) {
    cerr << "Failed to parse JSON file: " << POLICY_FILE_PATH << endl;
  }

  // 값 변경
  if (document.HasMember(policy_name.c_str()) &&
      document[policy_name.c_str()].IsString()) {
    std::string isEnableValue = document[policy_name.c_str()].GetString();
    document[policy_name.c_str()].SetString(status.c_str(), status.size(),
                                            document.GetAllocator());
  } else {
    cerr << "Invalid key or value type in JSON file: " << POLICY_FILE_PATH
         << endl;
  }

  // 변경된 JSON을 문자열로 변환
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  document.Accept(writer);
  string updatedJson = buffer.GetString();

  // 변경된 내용을 파일에 씀
  ofstream outputFile(POLICY_FILE_PATH);
  if (!outputFile.is_open()) {
    cerr << "Failed to open file for writing: " << POLICY_FILE_PATH << endl;
  }
  outputFile << updatedJson;
  cout << "Policy Modification Completed" << endl;

  outputFile.close();
}
void run_policy_server() {
  std::cout << "  Policy Server Start " << std::endl;
  DBus::default_dispatcher = &dispatcher;

  DBus::Connection conn = DBus::Connection::SystemBus();
  conn.request_name(POLICY_SERVER_NAME);

  Policy_Adaptor server(conn);
  // 서버 유지
  dispatcher.enter();

}
void policy() {
  string option = "", policy_name = "", status = "";

  while (true) {
    cout << " [ 1 | 2 | ibmc | feedback | monitor | energy | ssp ] , 1 : 정책 확인 , 2 : 정책 수정 ";
    cin >> option;
    if (option == "1") {
      cout << "bmc 정책 " << endl;
      read_file();

    } else if (option == "2") {
      cout << "[ [policy name] [ enable | disable ] ] , 정책 번호 정책 설정: ";
      cin >> policy_name >> status;
      modify_policy(policy_name, status);
    } else if (option == "ibmc") {
      cout << "Ibmc 서버 연결 요청" << endl;
      connect_to_ibmc_server();
    }
    else if (option =="feedback") {
      cout << "feedback 서버 연결 요청 " << endl;
      connect_to_feedback_server();
    }
    else if (option =="monitor") {
      cout << "monitor 서버 연결 요청 " << endl;
      connect_to_monitor_server();
    }
    else if (option =="energy") {
      cout << "energy 서버 연결 요청 " << endl;
      connect_to_energy_server();
    }
    else if (option =="ssp") {
      cout << "ssp 서버 연결 요청 " << endl;
      connect_to_ssp_server();
    }
    else {
      cout << "다시 입력하세요" << endl;
    }
  }
}

void niam(int sig) { dispatcher.leave(); }

int main() {
  std::thread policy_server_thread(run_policy_server);
  std::thread policy_thread(policy);
  //feedback서버 연결 함수 
  policy_server_thread.join();
  policy_thread.join();
  return 0;
}